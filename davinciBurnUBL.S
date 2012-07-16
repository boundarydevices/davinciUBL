#include "BigMacro.h"
#include "char.inc"
#include "xmodemReceive.inc"

//	.equiv  NAND_GPIO_READY, 18		//Comment out to use EM_WAIT instead
	.equiv  COLUMN_BITS, 11			//2048 byte pages
	.equiv  PAGE_BITS, 6				//64 pages/block
	.equiv  BLOCK_BITS, 10			//1024 blocks
	.equiv  TEXT_BASE, 0x80600000
	.equiv  BAUDRATE, 115200
	.equiv	NAND_BUS_WIDTH, 8	//Choices are 8 or 16
	.equiv	DDR_BANKS, 4		//Choices are 4(128MB) or 8(256MB)
	.equiv	DDR_SPEED, 189		//Choices are 135, 162 or 189
#include "davinci.inc"
///////////////////////////////////////////////////////////
	.global _start
_start:
	.rept ((0x100-0x20)/4)
	nop
	.endr

	DavinciInit
	BigMov	r0,DAVINCI_LPSC_UART0
	bl	lpsc_On
	BigMov	r0,DAVINCI_LPSC_GPIO
	bl	lpsc_On

1:	BigMov	ip,TEXT_BASE	//ip is only input to macro, unchanged on output
	xmodemReceive r3,r4,r5,r6,r7,r9,sl,fp,ip,TransmitX,ReceiveX
	beq	2f
	adr	r2,XmodemError
	bl	PrintStr
	b	1b
XmodemError:
	.asciz	"Xmodem error\r\n"
	.align 2
2:
#define rPage	r4
#define rEMIF	r6
#define rCSN	r7		//nand chip select
#define rGP		r8
#define rMem	r9
#define rECC	r10
#define rMemEnd fp
#define rMemStart ip

DownloadDone:
	mov	rMemEnd,r3
	BigMov	rEMIF,EMIF_BASE
	BigMov	rCSN,NAND_BASE	//cs2 address space
	.ifdef NAND_GPIO_READY
	BigMov	rGP,((NAND_GPIO_READY>>5)*GP_BANK_LENGTH)+GPIO_BASE+GP_BANK0_OFFSET
	.endif

	NandInit rEMIF,rGP

//rMemStart- 1st byte, rMemEnd - past last byte
//Now Burn file to nand flash blocks 1-5
	sub	r0,rMemEnd,rMemStart
	cmp	r0,#0x4000
	bhi	22f
	sub	r2,rMemStart,#SPARE_BYTES_PER_PAGE
	BigMov	r0,0xffffffff
1:	str	r0,[r2],#4
	cmp	r2,rMemStart
	bne	1b

	tst	rMemEnd,#1
	strneb	r0,[rMemEnd],#1
	tst	rMemEnd,#2
	strneh	r0,[rMemEnd],#2
	tst	rMemEnd,#4
	strne	r0,[rMemEnd],#4
	tst	rMemEnd,#8
	strne	r0,[rMemEnd],#4
	strne	r0,[rMemEnd],#4
2:	tst	rMemEnd,#(1<<COLUMN_BITS)-16
	strne	r0,[rMemEnd],#4
	strne	r0,[rMemEnd],#4
	strne	r0,[rMemEnd],#4
	strne	r0,[rMemEnd],#4
	bne	2b
////////////////
	mov	rPage,#1<<PAGE_BITS	//start on block 1 page 0, this is a page counter

	BigMov	r0,UBL_MAGIC_SAFE
	ldr	r2,[rMemStart,#0]			//** loader magic number
	cmp	r2,r0
	bne	not_magic

	mov	r0,#0xFF
	strb	r0,[rCSN,#NAND_CLE]		//reset
//	WaitForReady  r0,rEMIF,rGP
	mov	r0,#NAND_STATUS
	strb	r0,[rCSN,#NAND_CLE]		//Status
//	WaitForReady  r0,rEMIF,rGP
31:	ldrb	r0,[rCSN]					//reset
	tst	r0,#0x40
	beq	31b
//	bl	TransmitHexByte

//Main Loop ***************************************
//Now erase blocks1-5, and program blocks 1-5
//erase block
7:
	mov	rMem,rMemStart
	sub	rECC,rMemStart,#SPARE_BYTES_PER_PAGE-ECC_OFFSET_IN_SPARE
	mov	r0,#0x60
	strb	r0,[rCSN,#NAND_CLE]
	mov	r1,rPage,LSR #8
	strb	rPage,[rCSN,#NAND_ALE]
	strb	r1,[rCSN,#NAND_ALE]
	mov	r0,#0xd0
	strb	r0,[rCSN,#NAND_CLE]
	mov	r0,#NAND_STATUS
	strb	r0,[rCSN,#NAND_CLE]		//Status
	ldrb	r0,[rCSN]					//reset
	WaitForReady  r0,rEMIF,rGP

//program the page
8:	mov	r0,#0x80
	strb	r0,[rCSN,#NAND_CLE]
	mov	r0,#0
	mov	r1,rPage,LSR #8
	strb	r0,[rCSN,#NAND_ALE]
	strb	r0,[rCSN,#NAND_ALE]
	strb	rPage,[rCSN,#NAND_ALE]
	strb	r1,[rCSN,#NAND_ALE]
	ldr	r0,[rEMIF,#EMIF_NANDF_ECC]
	mov	r5,#ECC_GROUPS_PER_PAGE
9:	BigMov	r0,(1<<8)+1
	str	r0,[rEMIF,#EMIF_NANDFCR]		//start ecc calc
	mov	r1,#512
	StoreLoop r0,r1,rMem,rCSN

	ldr	r1,[rEMIF,#EMIF_NANDF_ECC]
	strb	r1,[rECC,#3]
	mov	r1,r1,LSR #8
	strb	r1,[rECC,#2]
	mov	r1,r1,LSR #8
	strb	r1,[rECC,#1]
	mov	r1,r1,LSR #8
	strb	r1,[rECC],#0x10
	subs	r5,r5,#1
	bne	9b
	mov	r1,#SPARE_BYTES_PER_PAGE
	sub	rECC,rECC,#SPARE_BYTES_PER_PAGE
	sub	r3,rECC,#ECC_OFFSET_IN_SPARE
	StoreLoop r0,r1,r3,rCSN
	mov	r0,#0x10
	strb	r0,[rCSN,#NAND_CLE]		//Start Programming page
	WaitForReady  r0,rEMIF,rGP

	add	rPage,rPage,#1
	cmp	rMem,rMemEnd
	blo	8b
	add	rPage,rPage,#(1<<PAGE_BITS)-1
	bic	rPage,rPage,#(1<<PAGE_BITS)-1
	cmp	rPage,#5<<PAGE_BITS
	ldrls	r0,[rMem,#12]
	addls	r0,r0,#1
	strls	r0,[rMem,#12]
	bls	7b			//Block 5 is last to program
	adr	r2,Success
	b	24f
//File too big
22:
	adr	r2,TooBig
	b	24f
23:	bl	TransmitX
24:	ldrb	r0,[r2],#1
	movs	r0,r0
	bne	23b
	mov	pc,#0x4000		//davinci ROM address
not_magic:
	adr	r2,missing_header
	b	24b
PrintStr:
	mov	r3,lr
	b	2f
1:	bl	TransmitX
2:	ldrb	r0,[r2],#1
	movs	r0,r0
	bne	1b
	mov	pc,r3

TransmitHexByte:
	and	r1,r0,#0x0f
	mov	r0,r0,LSR #4
	and	r0,r0,#0x0f
	cmp	r0,#10
	addlo	r0,r0,#'0'
	addhs	r0,r0,#'A'-10
	cmp	r1,#10
	addlo	r1,r1,#'0'
	addhs	r1,r1,#'A'-10
	add	r0,r0,r1,LSL #8

//IN: r0 - character to transmit
TransmitX:
1:	BigMov	r1,UART_BASE
	ldr	r1,[r1,#UART_LSR]
	tst	r1,#UART_LSR_THRE
	beq	1b

	BigMov	r1,UART_BASE
	str	r0,[r1,#UART_THR]
	movs	r0,r0,LSR #8
	bne	1b
	mov	pc,lr			//return

//OUT:
//z-0 good data in r0
//z-1 timeout, r0 is 0
//r1 - loop cnt time remaining
ReceiveX:
	mov	r1,#0x80000
1:
	BigMov	r0,UART_BASE
	ldr	r0,[r0,#UART_LSR]
	tst	r0,#UART_LSR_DR
	BigMovNe r0,UART_BASE
	ldrne	r0,[r0,#UART_RBR]
	andne	r0,r0,#0xff
	movne	pc,lr			//return
	subs	r1,r1,#1
	bne	1b
	mov	r0,#0
	mov	pc,lr			//return

TooBig:
	.asciz	"File too big, must be <=0x3800 bytes\r\n"
Success:
	.asciz	"Successful burn\r\n"
missing_header:
	.asciz	"missing header\r\n"
