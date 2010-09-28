#include "BigMacro.h"
#include "char.inc"
#include "xmodemReceive.inc"

//	.equiv  NAND_GPIO_READY, 18		//Comment out to use EM_WAIT instead
	.equiv  COLUMN_BITS, 11			//2048 byte pages
	.equiv  PAGE_BITS, 6				//64 pages/block
	.equiv  BLOCK_BITS, 10			//1024 blocks
	.equiv  TEXT_BASE, 0x80700000
	.equiv  BAUDRATE, 115200
	.equiv	NAND_BUS_WIDTH, 8	//Choices are 8 or 16
	.equiv	DDR_BANKS, 8		//Choices are 4(128MB) or 8(256MB)
	.equiv	DDR_SPEED, 162		//Choices are 148, 162 or 196
#include "davinci.inc"
///////////////////////////////////////////////////////////
	.global _start
ubl_header:
	.word	UBL_MAGIC_SAFE
	.word	0x100		//entry_point
	.word	(program_end - _start + ((1 << COLUMN_BITS) - 1)) >> COLUMN_BITS	//page_cnt
	.word	1		//start_block
	.word	1		//start_page
	.balignl 2048, 0xffffffff

_start:
	.rept ((0x100-0x20)/4)
	nop
	.endr
	DavinciInit
	BigMov	r0,DAVINCI_LPSC_UART0
	bl	lpsc_On
	BigMov	r0,DAVINCI_LPSC_GPIO
	bl	lpsc_On
#define rSequence r5
#define rEMIF	r6
#define rCSN	r7		//nand chip select
#define rGP		r8
#define rPage	r9
#define rECC	r10
#define rStart	fp
#define rMem	ip

	InitUART	r0,r1,UART_BASE,BAUDRATE
	bl	PrintStartMessage

	BigMov	rEMIF,EMIF_BASE
	BigMov	rCSN,NAND_BASE	//cs2 address space
	.ifdef NAND_GPIO_READY
	BigMov	rGP,((NAND_GPIO_READY>>5)*GP_BANK_LENGTH)+GPIO_BASE+GP_BANK0_OFFSET
	.endif
	NandInit rEMIF,rGP

	BigMov		rMem,TEXT_BASE
//load blocks starting with block 6, page 0
//skip pages with uncorrectable ecc errors

	mov		rSequence,#0
	mov		rPage,#6<<PAGE_BITS	//start on block 6 page 0, this is a page counter
	bl		LoadPage
	bne		40f
	sub		r3,rMem,#PAGE_INC
	ldr		r0,[r3,#32]
	BigMov	r1,UBL_MAGIC_SAFE
	cmp		r1,r0
	bne		NotHeader
	ldr		rStart,[r3,#36]
	mov		r2,rStart
	cmp		r2,r3
	beq		5f
2:	ldr		r0,[r3],#4
	str		r0,[r2],#4
	cmp		r3,rMem
	bne		2b
5:	sub		r3,rMem,r3
	add		rMem,r2,r3
	b		7f

6:	bl		LoadPage
	bne		40f
7:	ldr		r2,[rStart,#40]
	cmp		rMem,r2
	blo		6b
	b		Success

40:
	bl		PrintSequenceError
xagain:
	BigMov		ip,TEXT_BASE
	xmodemReceive r3,r4,r5,r6,r7,r9,sl,fp,ip,TransmitX,ReceiveX
	moveq	pc,ip		//start app if no error
	adr		r2,XmodemError
1:	bl		PrintStr
	b		xagain

Success:
	adr		r2,SuccessMsg
	bl		PrintStr
	mov		pc,rStart

NotHeader:
	adr		r2,MagicError
	b		1b

PrintStartMessage:
	adr		r2,UBL_Starting
	b		PrintStr

PrintSequenceError:
	adr		r2,SequenceError
PrintStr:
	mov		r3,lr
	b		2f
1:	bl		TransmitX
2:	ldrb	r0,[r2],#1
	movs	r0,r0
	bne		1b
	mov		pc,r3

UBL_Starting:
	.asciz	"\r\nUBL starting\r\n"
SuccessMsg:
	.asciz	"\r\nStarting app\r\n"
SequenceError:
	.asciz	"Sequence # Error\r\n"
MagicError:
	.asciz	"Descriptor header not found\r\n"
XmodemError:
	.asciz	"Xmodem error\r\n"
	.align 2
//rEMIF - EMIF_BASE
//rCSN - CS2 space
//rGP - GPio bank
//rPage - page #
//rMem - memory
//rSequence - sequence #
//Out: rPage, rMem, rSequence updated
//	z-1 success
LoadPage:
//Read the page
	mov		r4,#0
30:	add		rECC,rMem,#PAGE_INC+SPARE_BYTES_PER_PAGE	//calculated ecc storage area
	mov		r0,#NAND_READ_START
	strb	r0,[rCSN,#NAND_CLE]
	mov		r0,#0
	mov		r1,rPage,LSR #8
	strb	r0,[rCSN,#NAND_ALE]
	strb	r0,[rCSN,#NAND_ALE]
	strb	rPage,[rCSN,#NAND_ALE]
	add		rPage,rPage,#1			//next page
	strb	r1,[rCSN,#NAND_ALE]
	mov		r0,#NAND_READ_END
	strb	r0,[rCSN,#NAND_CLE]
	WaitForReady  r0,rEMIF,rGP

	ldr		r0,[rEMIF,#EMIF_NANDF_ECC]
	mov		r2,#ECC_GROUPS_PER_PAGE
1:	BigMov	r0,(1<<8)+1
	str		r0,[rEMIF,#EMIF_NANDFCR]		//start ecc calc
	mov		r1,#ECC_GROUP_INC
	LoadLoop r0,r1,rMem,rCSN				//r1 # of bytes to load

	ldr		r0,[rEMIF,#EMIF_NANDF_ECC]
	str		r0,[rECC],#4
	subs	r2,r2,#1
	bne		1b

	mov		r1,#SPARE_BYTES_PER_PAGE
	LoadLoop r0,r1,rMem,rCSN				//r1 # of bytes to load

//Verify ecc
	sub		r3,rMem,#SPARE_BYTES_PER_PAGE-UBOOT_ECC_OFFSET_IN_SPARE
	sub		rMem,rMem,#PAGE_INC+SPARE_BYTES_PER_PAGE
	sub		rECC,rECC,#ECC_GROUPS_PER_PAGE<<2
2:	ldr		r1,[rECC],#4
	mov		r0,r1,LSL #32-12
	mov		r1,r1,LSR #16
	mov		r0,r0,LSR #32-12
	orr		r0,r0,r1,LSL #12
	mvn		r0,r0
	.if 1
	//not guaranteed to be 32 bit aligned
	ldrb	r1,[r3],#1
	ldrb	r2,[r3],#1
	orr		r1,r1,r2,LSL #8
	ldr		r2,[r3],#UBOOT_AdvanceToNextECC-2
	orr		r1,r1,r2,LSL #16
	.else
	//guaranteed to be 32 bit aligned
	ldr		r1,[r3],#UBOOT_AdvanceToNextECC
	.endif
	eor		r0,r0,r1
	bics	r0,r0,#0xff000000
	beq		3f				//br if no ecc error
	mov		r1,r0,LSR #12
	mov		r2,r0,LSL #32-12
	eor		r2,r1,r2,LSR #32-12
	add		r2,r2,#1
	cmp		r2,#0x1000
	bne		4f				//br if not correctable
//z-1 Single bit ecc error
	and		r0,r1,#7
	mov		r2,#1
	mov		r2,r2,LSL r0
	ldrb	r0,[rMem,r1,LSR #3]
	eor		r0,r0,r2
	strb	r0,[rMem,r1,LSR #3]
	mov		r0,#'c'			//print a 'c' to denote a corrected ecc error
5:	mov		r2,lr
	bl		TransmitX
	mov		lr,r2
3:	mov		r4,r4,LSR #1
	add		rMem,rMem,#ECC_GROUP_INC
	add		r0,rMem,#ECC_GROUP_INC
	cmp		r0,r3
	blo		2b

//r4 - bit mask of uncorrectable error ecc groups, bit 0 - 1st ecc group, bit 1 - 2nd ecc group
	mov		r0,#'E'
	mov		r2,lr
	tst		r4,#(1<<ECC_GROUPS_PER_PAGE)-1
	blne	TransmitX		//print a E to denote a page had uncorrectable errors
	mov		lr,r2

	ldrb	r0,[r3,#-(UBOOT_AdvanceToNextECC*ECC_GROUPS_PER_PAGE)-UBOOT_ECC_OFFSET_IN_SPARE+UBOOT_SEQ_OFFSET_IN_SPARE]
	mov		r1,r0,LSR #4
	and		r0,r0,#0xf
	cmp		r0,r1
	bicne	r4,r4,#(1<<ECC_GROUPS_PER_PAGE)-1
	movne	r4,r4,LSL #ECC_GROUPS_PER_PAGE
	subne	rMem,rMem,#PAGE_INC
	bne		30b			//ignore page if sequence number nibbles don't match
	and		r1,rSequence,#0xf
	cmp		r0,r1
	beq		10f			//br if expected sequence #
	cmp		rSequence,#0
	subne	rSequence,rSequence,#1	//Can't backup from 0
	and		r1,rSequence,#0xff
	cmp		r0,r1
	beq		11f			//page was repeated, copy good parts to previous page
	mvns	r0,#0
	mov		pc,lr		//return error

4:	rsb		r2,r0,#0
	and		r2,r2,r0
	cmp		r2,r0
	mov		r0,#'_'		//this denote an ignored ecc error
	beq		5b			//br if Single bit ecc error in the ecc itself, ignore error
	orr		r4,r4,#1<<ECC_GROUPS_PER_PAGE	//mark if uncorrectable ecc error
	b		3b

10:	movs	r4,r4
	beq		20f
	cmp		r4,#1<<ECC_GROUPS_PER_PAGE
	movlo	r4,r4,LSL #(ECC_GROUPS_PER_PAGE<<1)
	blo		30b			//br if previous page contained no errors
11:	sub		rMem,rMem,#PAGE_INC<<1

	mov		r2,#ECC_GROUPS_PER_PAGE
12:	tst		r4,#1
	addne	rMem,rMem,#ECC_GROUP_INC
	bne		14f
	mov		r1,#ECC_GROUP_INC>>2
13:	ldr		r0,[rMem,#PAGE_INC]
	str		r0,[rMem],#4
	subs	r1,r1,#1
	bne		13b
	bic		r4,r4,#1<<ECC_GROUPS_PER_PAGE	//this group has been corrected
14:	mov		r4,r4,LSR #1
	subs	r2,r2,#1
	bne		12b
	movs	r4,r4,LSL #(ECC_GROUPS_PER_PAGE<<1)
	bne		30b			//br if errors remain

20:	add		rSequence,rSequence,#1
	movs	r0,#0
	mov		pc,lr

/////
//IN: r0 - character to transmit
TransmitX:
1:	BigMov	r1,UART_BASE
	ldr		r1,[r1,#UART_LSR]
	tst		r1,#UART_LSR_THRE
	beq		1b

	BigMov	r1,UART_BASE
	str		r0,[r1,#UART_THR]
	movs	r0,r0,LSR #8
	bne		1b
	mov	pc,lr			//return

//OUT:
//z-0 good data in r0
//z-1 timeout, r0 is 0
//r1 - loop cnt time remaining
ReceiveX:
	mov	r1,#0x80000
1:
	BigMov	r0,UART_BASE
	ldr		r0,[r0,#UART_LSR]
	tst		r0,#UART_LSR_DR
	BigMovNe r0,UART_BASE
	ldrne	r0,[r0,#UART_RBR]
	andne	r0,r0,#0xff
	movne	pc,lr			//return
	subs	r1,r1,#1
	bne		1b
	mov		r0,#0
	mov		pc,lr			//return

program_end:
	.balignl 2048, 0xffffffff
