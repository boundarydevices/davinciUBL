	.equiv	UBL_MAGIC_SAFE,			0xA1ACED00
	.equiv	UBL_MAGIC_DMA_IC_FAST,	0xA1ACED55
	.equiv	PAGE_INC, (1<<COLUMN_BITS)
	.equiv	BLOCK_INC, (1<<(COLUMN_BITS+PAGE_BITS))

	.equiv	ECC_GROUP_BITS, 9
	.equiv	ECC_GROUP_INC, (1<<ECC_GROUP_BITS)
	.equiv	ECC_GROUPS_PER_PAGE, (1<<(COLUMN_BITS-ECC_GROUP_BITS))
	.equiv	SPARE_BYTES_PER_PAGE, (ECC_GROUPS_PER_PAGE<<4)
	.equiv	SPARE_BYTES_PER_ECC_GROUP, 0x10	//Used for hardware ordering of ECC data
	.equiv	UBOOT_AdvanceToNextECC, 3			//Used for UBoot ordering of ECC data
	.if (SPARE_BYTES_PER_PAGE==64)
	.equiv	ECC_OFFSET_IN_SPARE, 8
	.equiv	UBOOT_ECC_OFFSET_IN_SPARE, 52	//Used for UBoot ordering of ECC data
	.equiv	UBOOT_SEQ_OFFSET_IN_SPARE,2
	.else
	.equiv	ECC_OFFSET_IN_SPARE, 0
	.equiv	UBOOT_ECC_OFFSET_IN_SPARE, 0
	.equiv	UBOOT_SEQ_OFFSET_IN_SPARE,6
	.endif

	.equiv	NAND_READ_START,	0x00
	.equiv	NAND_READ_END,		0x30
	.equiv	NAND_STATUS,		0x70

	.equiv	NAND_BASE, 0x02000000
	.equiv	NAND_CLE,	0x10
	.equiv	NAND_ALE,	0x08

	.equiv	UART_BASE, 0x01c20000
	.equiv	UART_RBR, 0x00
	.equiv	UART_THR, 0x00
	.equiv	UART_IER, 0x04
	.equiv	UART_IIR, 0x08
	.equiv	UART_FCR, 0x08
	.equiv	UART_LCR, 0x0c
	.equiv	UART_MCR, 0x10
	.equiv	UART_LSR, 0x14
	.equiv	UART_DLL, 0x20
	.equiv	UART_DLH, 0x24
	.equiv	UART_PID1, 0x28
	.equiv	UART_PID2, 0x2c
	.equiv	UART_PWREMU_MGMT, 0x30

	.equiv	UART_LSR_THRE,	0x20	//Transmit empty
	.equiv	UART_LSR_DR,	0x01	//Receiver data ready

	.equiv	IT_BASE,		0X01C21000	//I2c & timer0,timer1 base
	.equiv	IT_TIM0,		0x400
	.equiv	IT_TIM1,		0x800
	.equiv	TIM_EMUMGT_CLKSPD, 0x04
	.equiv	TIM_TIM12,		0x10
	.equiv	TIM_TIM34,		0x14
	.equiv	TIM_PRD12,		0x18
	.equiv	TIM_PRD34,		0x1c
	.equiv	TIM_TCR,		0x20
	.equiv	TIM_TGCR,		0x24

	.equiv	EMIF_BASE,		0x01e00000		//DAVINCI_ASYNC_EMIF_CNTRL_BASE
	.equiv	EMIF_A1CR,		0x10
	.equiv	EMIF_NANDFCR,	0x60
	.equiv	EMIF_NANDFSR,	0x64
	.equiv	EMIF_NANDF_ECC,	0x70	//array of 4 ints


	.equiv	GPIO_BASE,		0x01c67000		//DAVINCI_GPIO_BASE
	.equiv	GP_BANK0_OFFSET,	0x10
	.equiv	GP_BANK_LENGTH,	0x28
	.equiv	GP_DIR, 0x00
	.equiv	GP_OUT, 0x04
	.equiv	GP_SET, 0x08
	.equiv	GP_CLR, 0x0C
	.equiv	GP_IN,  0x10


	.equiv	PLL_BASE,		0x01c40000
	.equiv	__PINMUX0,		0x0000		// Device Configuration Registers
	.equiv	__PINMUX1,		0x0004		// Device Configuration Registers
	.equiv	_BOOTCFG,		0x0014
	.equiv	_DFT_ENABLE,	0x004c
/* PLL1-SYSTEM PLL MMRs */
	.equiv	_PLL1_CTL,		0x0900
	.equiv	_PLL1_PLLM,		0x0910

/* PLL2-SYSTEM PLL MMRs */
	.equiv	_PLL2_CTL,		0x0d00
	.equiv	_PLL2_PLLM,		0x0d10
	.equiv	_PLL2_DIV1,		0x0d18
	.equiv	_PLL2_DIV2,		0x0d1c
	.equiv	_PLL2_PLLCMD,	0x0d38
	.equiv	_PLL2_PLLSTAT,	0x0d3c

	.equiv	M2_BASE,		0x01c41000
	.equiv	M2_PTCMD,		0x120
	.equiv	M2_PTSTAT,		0x128
	.equiv	M2_MDSTAT_,		0x800
	.equiv	M2_MDSTAT_DDR2,	0x834		//13
	.equiv	M2_MDSTAT_GEM,	0x89c		//39
	.equiv	M2_MDCTL_,		0xa00
	.equiv	M2_P1394,		0xa20		// For WDT reset chip bug
	.equiv	M2_MDCTL_DDR2,	0xa34		//13
	.equiv	M2_MDCTL_GEM,	0xa9c		//39 GEM Power Up & LPSC Control Register

	.equiv	M3_BASE,		0x01c42000
	.equiv	M3_MMARG_BRF0,	0x010		// BRF margin mode 0 (R/W)
	.equiv	M3_DDRVTPR,		0x030		// DDR VPTR MMR

	.equiv	EINT_BASE,		0x01c48000
	.equiv	EINT_ENABLE0,	0x18
	.equiv	EINT_ENABLE1,	0x1c


	.equiv	ACFG_BASE,		0x01e00000
	.equiv	A_WAITCFG,		0x0004
	.equiv	A_ACFG3,		0x0014
	.equiv	A_ACFG4,		0x0018
	.equiv	A_ACFG5,		0x001c

	.equiv	MM_BASE,		0x20000000
	.equiv	MM_SDRSTAT,		0x0004
	.equiv	MM_SDBCR,		0x0008
	.equiv	MM_SDRCR,		0x000c
	.equiv	MM_SDTIMR,		0x0010
	.equiv	MM_SDTIMR2,		0x0014
	.equiv	MM_DDRPHYCR,		0x00e4
	.equiv	MM_VTPIOCR,		0x00f0	// VTP IO Control register
	.equiv	SDRCR_SR,		(1 << 31)
	.equiv	SDRCR_MCLKSTOPEN,	(1 << 30)
	.equiv	SDRSTAT_PHYRDY,		(1 << 2)
	.equiv	DDRPHYCR_DLLPWRDN,	(1 << 4)


	.equiv	DDR2_MEM_BASE,	0x80000000
	.equiv	CFGTEST_OFFSET,	0x10000

//non address related constants
	.equiv	DAVINCI_LPSC_DDR2,	13
	.equiv	DAVINCI_LPSC_UART0,	19
	.equiv	DAVINCI_LPSC_GPIO,	26
	.equiv	DAVINCI_LPSC_GEM,	39

	.equiv	DDR_COLUMN_BITS, 10		//max 11 column address bits
	.equiv	DDR_CAS_LATENCY,3
	.equiv	DDR_DRIVE_STRENGTH,1	//1 - weak, 0 - normal
	.if (DDR_BANKS==4)
	//DDR2 always has 13 row address bits, 13+10+2+2=27 bits = 128 Meg
	.equiv	DDR_BANK_BITS,2
	.else
	.if (DDR_BANKS==8)
	//DDR2 always has 13 row address bits, 13+10+3+2=28 bits = 256 Meg
	.equiv	DDR_BANK_BITS,3
	.else
	.err	//"Unknown DDR configuration!!!"
	.endif
	.endif
	.equiv	C_SDCFG_VAL,(DDR_DRIVE_STRENGTH<<18)|(DDR_CAS_LATENCY<<9)|(DDR_BANK_BITS<<4)|(DDR_COLUMN_BITS-8)

	.equiv	_PLL_LOCK_COUNT,	0x2000

	.equiv	C_PSC_FLAG_MASK,	0x1f
	.equiv	C_VTP_LOCK_COUNT,	0x05b0
	.equiv	C_WAITCFG_VAL,	0
	.equiv	C_ACFG3_VAL,			0x3ffffffd
	.equiv	C_ACFG4_VAL,			0x3ffffffd
	.equiv	C_ACFG5_VAL,			0x3ffffffd
	.equiv	C_MMARG_BRF0_VAL,		0x00444400
	.equiv	C_DDRCTL_VAL,			0x50006405
	.equiv	C_SDREF_VAL,			0x000005c3

.macro InitUART rBase,rTemp,uartaddr,baudrate
	BigMov	\rBase,\uartaddr

	mov	\rTemp,#0x03			// 8-bit characters
	str	\rTemp,[\rBase,#UART_LCR]
	mov	\rTemp,#(((27000000/\baudrate)+8)>>4)&0xff
	str	\rTemp,[\rBase,#UART_DLL]
	mov	\rTemp,#(((27000000/\baudrate)+8)>>12)&0xff
	str	\rTemp,[\rBase,#UART_DLH]

	mov	\rTemp,#0xc1			//enable fifo, 32 byte level
	str	\rTemp,[\rBase,#UART_FCR]

	mov	\rTemp,#0x0
	str	\rTemp,[\rBase,#UART_IER]
	str	\rTemp,[\rBase,#UART_MCR]

	BigMov	\rTemp,0x6001			//enable tx & rx & free running
	str	\rTemp,[\rBase,#UART_PWREMU_MGMT]
.endm

.macro InitTimer0 rBase,rTemp
	BigMov	\rBase,IT_BASE
	mov	\rTemp,#0x0
	str	\rTemp,[\rBase,#IT_TIM0+TIM_TCR]

	mov	\rTemp,#0x3					//Default is GPTIM mode
	str	\rTemp,[\rBase,#IT_TIM0+TIM_TGCR]	//TIM34RS_ and TIM12RS_ = 1

	mov	\rTemp,#0x0
	str	\rTemp,[\rBase,#IT_TIM0+TIM_TIM34]
	str	\rTemp,[\rBase,#IT_TIM0+TIM_TIM12]
	str	\rTemp,[\rBase,#IT_TIM0+TIM_PRD34]

	BigMov	\rTemp,0x00cdfe60
	str	\rTemp,[\rBase,#IT_TIM0+TIM_PRD12]		//27Mhz * 500 / 1000
.endm

.macro TransmitChar rChar,rUART,rTmp
111:
	ldr		\rTmp,[\rUART,#UART_LSR]
	tst		\rTmp,#UART_LSR_THRE
	beq		111b
	and		\rTmp,\rChar,#0xff
	str		\rTmp,[\rUART,#UART_THR]
.endm

//Out: z-0 if good char
.macro ReceiveChar rChar,rUART
	ldr		\rChar,[\rUART,#UART_LSR]
	ands	\rChar,\rChar,#UART_LSR_DR
	ldrne	\rChar,[\rUART,#UART_RBR]
.endm
	.macro DEBUG char
	.if 1
		BigMov	r0,\char
		bl		TransmitX
	.endif
	.endm


	.macro	WaitForReady rTmp,rEMIF,rGP
	mov		\rTmp,#80
98:	subs	\rTmp,\rTmp,#1
	bne		98b
	.ifdef NAND_GPIO_READY
99:	ldr		\rTmp,[\rGP,#GP_IN]
	tst		\rTmp,#1<<(NAND_GPIO_READY&0x1f)
	beq		99b
	.else
99:	ldr		\rTmp,[\rEMIF,#EMIF_NANDFSR]
	tst		\rTmp,#1
	beq		99b
	.endif
	.endm

	.macro LoadLoop rTmp,rCnt,rMem,rNand
	.if	(NAND_BUS_WIDTH==8)
99:	ldrb	\rTmp,[\rNand]
	strb	\rTmp,[\rMem],#1
	subs	\rCnt,\rCnt,#1
	bne		99b
	.else
	.if	(NAND_BUS_WIDTH==16)
99:	ldrh	\rTmp,[\rNand]
	strh	\rTmp,[\rMem],#2
	subs	\rCnt,\rCnt,#2
	bne		99b
	.else
	.err	//Unknown bus width
	.endif
	.endif
	.endm

	.macro StoreLoop rTmp,rCnt,rMem,rNand
	.if	(NAND_BUS_WIDTH==8)
99:	ldrb	\rTmp,[\rMem],#1
	strb	\rTmp,[\rNand]
	subs	\rCnt,\rCnt,#1
	bne		99b
	.else
	.if	(NAND_BUS_WIDTH==16)
99:	ldrh	\rTmp,[\rMem],#2
	strh	\rTmp,[\rNand]
	subs	\rCnt,\rCnt,#2
	bne		99b
	.else
	.err	//Unknown bus width
	.endif
	.endif
	.endm

	.macro	DelayLoop rCnt,val
	BigMov	\rCnt,\val
99:	subs	\rCnt,\rCnt,#1
	bne		99b
	.endm

	.macro WaitForBitLow	rTmp,rBase,offset,mask
99:	ldr		\rTmp,[\rBase,#\offset]
	tst		\rTmp,#\mask
	bne		99b
	.endm

	.macro WaitForValue		rTmp,rBase,offset,mask,val
99:	ldr		\rTmp,[\rBase,#\offset]
	and		\rTmp,\rTmp,#\mask
	cmp		\rTmp,#\val
	bne		99b
	.endm

	.macro DavinciInit
	BigMov	r4,ACFG_BASE
	BigMov	r5, MM_BASE
	BigMov	r6,PLL_BASE
	BigMov	r7,M2_BASE
#if 1
	mov		r0,pc
	sub		r0,r0,#0x80000000
	cmp		r0,#0x10000000	//256Meg
	blo		90f
	/*-------------------------------------------------------*
	 * Mask all IRQs by setting all bits in the EINT default *
	 *-------------------------------------------------------*/
	mov	r1, $0
	BigMov	r0,EINT_BASE
	str	r1, [r0,#EINT_ENABLE0]
	str	r1, [r0,#EINT_ENABLE1]

	/*------------------------------------------------------*
	 * Put the GEM in reset					*
	 *------------------------------------------------------*/

	/* Put the GEM in reset */
	ldr	r0, [r7,#M2_MDCTL_GEM]
	bic	r0, r0, #0x100
	str	r0, [r7,#M2_MDCTL_GEM]

	/* Enable the Power Domain Transition Command */
	ldr	r0, [r7,#M2_PTCMD]
	orr	r0, r0, $0x02
	str	r0, [r7,#M2_PTCMD]


	WaitForBitLow r0,r7,M2_PTSTAT,0x02		// Wait for Transition Complete(PTSTAT)
	WaitForBitLow r0,r7,M2_MDSTAT_GEM,0x100	// Wait for GEM Reset Completion

	/* Do this for enabling a WDT initiated reset this is a workaround
	   for a chip bug.  Not required under normal situations */
	mov	r0, $0
	str	r0, [r7,#M2_P1394]

	/*------------------------------------------------------*
	 * Enable L1 & L2 Memories in Fast mode                 *
	 *------------------------------------------------------*/
	mov	r0, $0x01
	str	r0, [r6,#_DFT_ENABLE]

	BigMov	r0, C_MMARG_BRF0_VAL
	BigMov	r1,M3_BASE
	str	r0, [r1,#M3_MMARG_BRF0]

	mov	r0, $0
	str	r0, [r6,#_DFT_ENABLE]
#endif


	.if (DDR_SPEED==196)
	mov	r2, $29-1		// 27*29 =  783 MHz (r2 has 5 bit number)
	mov	r1, $(14-1)|((2-1)<<4)	// 783/14 = 55.9 MHz (r1 has 4 bit number)
					// 783/2 = 391.5 Mhz, 391.5/2 = 195.75 Mhz (r2 has 4 bit number)
	.else
	.if (DDR_SPEED==162)
	mov     r2, $24-1		// 27*24 = 648 MHz
	mov     r1, $(12-1)|((2-1)<<4)	// 648/12 = 54 MHz
					// 648/2 = 324 Mhz, 324/2 = 162 Mhz
	.else
	.if (DDR_SPEED==148)
	mov     r2, $21-1		// 27*21 = 567 MHz
	mov     r1, $(11-1)|((2-1)<<4)	// 594/11 = 54 MHz
					// 594/2 = 297 Mhz, 297/2 = 148.5 Mhz
	.else
	.err            //Unknown DDR_SPEED
	.endif
	.endif
	.endif
#if 0	//ddr2 is already stopped
//;stop ddr2
	ldr	ip, [r5,#MM_SDBCR]	//save 128MB/256MB setting

	ldr	r0, [r5,#MM_SDRCR]
	orr	r0,r0,$SDRCR_SR
	str	r0, [r5,#MM_SDRCR]
	orr	r0,r0,$SDRCR_MCLKSTOPEN
	str	r0, [r5,#MM_SDRCR]

	ldr	r0, [r5,#MM_DDRPHYCR]
	orr	r0,r0,$DDRPHYCR_DLLPWRDN
	str	r0, [r5,#MM_DDRPHYCR]

1:	ldr	r0, [r5,#MM_SDRSTAT]
	tst	r0,$SDRSTAT_PHYRDY
	bne	1b
#endif
	/*------------------------------------------------------*
	 * DDR2 PLL Initialization			  	*
	 *------------------------------------------------------*/

	/* Select the Clock Mode Depending on the Value written in the Boot Table by the run script */
	ldr	r3, [r6,#_PLL2_CTL]
	/* Mask the Clock Mode bit 0x0100 */
	/* Select the PLLEN source 0x0020 */
	/* Bypass the PLL  0x0001 */
	BigBic2	r3, 0x121
	str	r3, [r6,#_PLL2_CTL]

	/* Wait for few cycles to allow PLLEN Mux switch properly to bypass Clock */
	DelayLoop r0,0x20

	/* Reset the PLL */
	bic	r3, r3, #8
	str	r3, [r6,#_PLL2_CTL]

	/* Power up the PLL */
	bic	r3, r3, #2
	str	r3, [r6,#_PLL2_CTL]

	/* Enable the PLL from Disable Mode */
	bic	r3, r3, #0x10
	str	r3, [r6,#_PLL2_CTL]

	/* Program the PLL Multiplier */
	mov	r0, r1, LSR #4
	and	r1, r1, #0x0f
	orr	r1, r1, #1<<15		//enable divider
	orr	r0, r0, #1<<15		//enable divider

	str	r2, [r6,#_PLL2_PLLM]
	str	r1, [r6,#_PLL2_DIV1]
	str	r0, [r6,#_PLL2_DIV2]


	/* Program the GOSET bit to take new divider values */
	mov	r0, $0x01
	str	r0, [r6,#_PLL2_PLLCMD]

	WaitForBitLow r0,r6,_PLL2_PLLSTAT,0x01	// Wait for Done

	/* Wait for PLL to Reset Properly */
	DelayLoop r0,0x218

	/* Bring PLL out of Reset */
	orr	r3, r3, $0x08
	str	r3, [r6,#_PLL2_CTL]

	/* Wait for PLL to Lock */
	DelayLoop r0,_PLL_LOCK_COUNT

	/* Enable the PLL */
	orr	r3, r3, $0x01
	str	r3, [r6,#_PLL2_CTL]

	/*------------------------------------------------------*
	 * Issue Soft Reset to DDR Module			*
	 *------------------------------------------------------*/

	/* Shut down the DDR2 LPSC Module */
	ldr	r0, [r7,#M2_MDCTL_DDR2]
	bic	r0, r0, #C_PSC_FLAG_MASK
	orr	r0, r0, $0x03
	str	r0, [r7,#M2_MDCTL_DDR2]

	/* Enable the Power Domain Transition Command */
	ldr	r0, [r7,#M2_PTCMD]
	orr	r0, r0, $0x01
	str	r0, [r7,#M2_PTCMD]

	WaitForBitLow r0,r7,M2_PTSTAT,0x01	//Wait for Transition Complete(PTSTAT)
	WaitForValue r0,r7,M2_MDSTAT_DDR2,0x1f,0x03		//Wait for DDR2 Controller Enable Completion

	/*------------------------------------------------------*
	 * Program DDR2 MMRs for 162MHz Setting			*
	 *------------------------------------------------------*/

	/* Program PHY Control Register */
	BigMov	r0,C_DDRCTL_VAL
	str	r0, [r5,#MM_DDRPHYCR]

	/* Program SDRAM Bank Config Register */
	ldr	r1, [r5,#MM_SDBCR]
	BigAnd2	r1,((0xf<<19)|(3<<16))	//these reserved fields must not change value
	BigOrr2	r1, C_SDCFG_VAL|(1<<15)	//Unlock timing registers
	str	r1, [r5,#MM_SDBCR]

	/* Program SDRAM TIM-0 Config Register */
	ldr	r0, SDTIM0_VAL_162MHz
	str	r0, [r5,#MM_SDTIMR]

	/* Program SDRAM TIM-1 Config Register */
	ldr	r0, SDTIM1_VAL_162MHz
	str	r0, [r5,#MM_SDTIMR2]

	/* Program the SDRAM Bank Config Control Register */
	bic	r0,r1,#1<<15		//Lock timing registers
	str	r0, [r5,#MM_SDBCR]

	/* Program SDRAM SDREF Config Register */
	BigMov	r0,C_SDREF_VAL
	str	r0, [r5,#MM_SDRCR]

	/*------------------------------------------------------*
	 * Issue Soft Reset to DDR Module			*
	 *------------------------------------------------------*/

	/* Issue a Dummy DDR2 read/write */
	BigMov	r1, DDR2_MEM_BASE
	ldr	r0, DUMMY_VAL
	str	r0, [r1]
	ldr	r0, [r1]

	/* Shut down the DDR2 LPSC Module */
	ldr	r0, [r7,#M2_MDCTL_DDR2]
	bic	r0, r0, #C_PSC_FLAG_MASK
	orr	r0, r0, $0x01
	str	r0, [r7,#M2_MDCTL_DDR2]

	/* Enable the Power Domain Transition Command */
	ldr	r0, [r7,#M2_PTCMD]
	orr	r0, r0, $0x01
	str	r0, [r7,#M2_PTCMD]

	WaitForBitLow r0,r7,M2_PTSTAT,0x01		//Wait for Transition Complete(PTSTAT)
	WaitForValue r0,r7,M2_MDSTAT_DDR2,0x1f,0x01	//Wait for DDR2 Controller Enable Completion

	/*------------------------------------------------------*
	 * Turn DDR2 Controller Clocks On			*
	 *------------------------------------------------------*/
	.if	1
	mov	r0,#DAVINCI_LPSC_DDR2
	bl	lpsc_On
	.else
	/* Enable the DDR2 LPSC Module */
	ldr	r0, [r7,#M2_MDCTL_DDR2]
	orr	r0, r0, $0x03
	str	r0, [r7,#M2_MDCTL_DDR2]

	/* Enable the Power Domain Transition Command */
	ldr	r0, [r7,#M2_PTCMD]
	orr	r0, r0, $0x01
	str	r0, [r7,#M2_PTCMD]

	WaitForBitLow r0,r7,M2_PTSTAT,0x01		//Wait for Transition Complete(PTSTAT)
	WaitForValue r0,r7,M2_MDSTAT_DDR2,0x1f,0x03		//Wait for DDR2 Controller Enable Completion
	.endif

	/*  DDR Writes and Reads */
	BigMov	r2, DDR2_MEM_BASE+CFGTEST_OFFSET
	mov	r0, $0x01
	str	r0, [r2]

	/*------------------------------------------------------*
	 * System PLL Initialization				*
	 *------------------------------------------------------*/

	/* Select the Clock Mode Depending on the Value written in the Boot Table by the run script */
	ldr	r0, [r6,#_PLL1_CTL]
	bic	r0, r0, #0x100			/* Mask the Clock Mode bit */
	BigOrr2	r0,(0<<8)			//doesn't generate any instructions
	str	r0, [r6,#_PLL1_CTL]

	/* Select the PLLEN source */
	bic	r0, r0, #0x20
	str	r0, [r6,#_PLL1_CTL]

	/* Bypass the PLL */
	bic	r0, r0, #1
	str	r0, [r6,#_PLL1_CTL]

	/* Wait for few cycles to allow PLLEN Mux switch properly to bypass Clock */
	DelayLoop r1,0x20

	/* Reset the PLL */
	bic	r0, r0, #8
	str	r0, [r6,#_PLL1_CTL]

	/* Disable the PLL */
	orr	r0, r0, $0x10
	str	r0, [r6,#_PLL1_CTL]

	/* Power up the PLL */
	bic	r0, r0, #2
	str	r0, [r6,#_PLL1_CTL]

	/* Enable the PLL from Disable Mode */
	bic	r0, r0, #0x10
	str	r0, [r6,#_PLL1_CTL]

	/* Program the PLL Multiplier */
	mov	r1, $(21-1)	/* 27*21 = 567MHz */
	str	r1, [r6,#_PLL1_PLLM]

	/* Wait for PLL to Reset Properly */
	DelayLoop r1,0xff

	/* Bring PLL out of Reset */
	orr	r0, r0, $0x08
	str	r0, [r6,#_PLL1_CTL]

	/* Wait for PLL to Lock */
	DelayLoop r1,_PLL_LOCK_COUNT

	/* Enable the PLL */
	orr	r0, r0, $0x01
	str	r0, [r6,#_PLL1_CTL]

	nop
	nop
	nop
	nop

	/*------------------------------------------------------*
	 * AEMIF configuration for NOR Flash (double check)     *
	 *------------------------------------------------------*/
	.if 1
	ldr	r1, [r6,#__PINMUX0]
	and	r1,r1,#0x1f		//keep default emif
	BigOrr2	r1,0x80000c00	//enable emac&mdio, CS4&5 on gpio9 & 8
	.else
	BigMov	r1,0x80000c00	//enable emac&mdio, CS4&5 on gpio9 & 8
	.endif
	str	r1, [r6,#__PINMUX0]

	ldr	r1, [r6,#__PINMUX1]
	orr	r1,r1,#0x81		//enable UART 0, I2C
	str	r1, [r6,#__PINMUX1]

	BigMov	r1, C_WAITCFG_VAL
	ldr	r2, [r4,#A_WAITCFG]
	orr	r2, r2, r1
	str	r2, [r4,#A_WAITCFG]

	BigMov	r1, C_ACFG3_VAL
	ldr	r2, [r4,#A_ACFG3]
	and	r1, r2, r1
	str	r1, [r4,#A_ACFG3]

	BigMov	r1, C_ACFG4_VAL
	ldr	r2, [r4,#A_ACFG4]
	and	r1, r2, r1
	str	r1, [r4,#A_ACFG4]

	BigMov	r1, C_ACFG5_VAL
	ldr	r2, [r4,#A_ACFG5]
	and	r1, r2, r1
	str	r1, [r4,#A_ACFG5]

	/*--------------------------------------*
	 * VTP manual Calibration               *
	 *--------------------------------------*/
	BigMov	r1, (0x1f+(1<<13))	//enable
	str		r1, [r5,#MM_VTPIOCR]
	orr		r1,r1,#(1<<15)		//start recalibration
	str		r1, [r5,#MM_VTPIOCR]

	/* Wait for 33 VTP CLK cycles.  VRP operates at 27 MHz */
	DelayLoop r0,C_VTP_LOCK_COUNT

	mov	r0, $0x01
	str	r0, [r6,#_DFT_ENABLE]

	BigMov	r1,M3_BASE
	ldr	r0, [r1,#M3_DDRVTPR]
	.if 0
	//This original is Buggy??????
	and	r0, r0, $0x1f
	and	r1, r0, $0x3e0	//r1 is now 0, wtf???
	orr	r1, r0, r1
	orr	r1, r1, #(1<<18)|(1<<13)	//bit 15 is recal, not 18
	.else
	mov	r1,r0,LSL #32-10
	mov	r1,r1,LSR #32-10	//grab low 10 bits
	orr	r1,r1,#(1<<15)|(1<<13)
	.endif
	str	r1, [r5,#MM_VTPIOCR]


	/* Wait for 33 VTP CLK cycles.  VRP operates at 27 MHz */
	DelayLoop r0,C_VTP_LOCK_COUNT

	ldr	r1, [r5,#MM_VTPIOCR]
	bic	r2, r1, #(1<<13)		//disable calibration
	str	r2, [r5,#MM_VTPIOCR]

	mov	r0, $0
	str	r0, [r6,#_DFT_ENABLE]
	b	90f

	.ltorg
/*
 DDR2 MMR & CONFIGURATION VALUES, 162 MHZ clock
For Micron MT47H64M16BT-37E @ 162 MHz
 */
#define DDR2_NM		0
#define DDR2_CL		5
#define DDR2_IBANK	3
#define DDR2_PAGESIZE	2
#define DDR2_RR		2317
#define DDR2_READ_Latency	6
#if 0
//flash_utils/DM646x/Common/src/device.c settings
#define DDR2_T_RFC	37
#define DDR2_T_RP	4
#define DDR2_T_RCD	4
#define DDR2_T_WR	4
#define DDR2_T_RAS	11
#define DDR2_T_RC	16
#define DDR2_T_RRD	2
#define DDR2_T_WTR	2

#define DDR2_T_RASMAX	7
#define DDR2_T_XP	1
#define DDR2_T_XSNR	40
#define DDR2_T_XSRD	199
#define DDR2_T_RTP	2
#define DDR2_T_CKE	2

#else
//u-boot settings
#define DDR2_T_RFC	20
#define DDR2_T_RP	2
#define DDR2_T_RCD	2
#define DDR2_T_WR	2
#define DDR2_T_RAS	6
#define DDR2_T_RC	8
#define DDR2_T_RRD	2
#define DDR2_T_WTR	1

#define DDR2_T_RASMAX	0
#define DDR2_T_XP	0
#define DDR2_T_XSNR	22
#define DDR2_T_XSRD	199
#define DDR2_T_RTP	1
#define DDR2_T_CKE	2
#endif

#define DDR2_SDTIMR_VAL_162	(DDR2_T_RFC << 25) | \
		                (DDR2_T_RP << 22)  | \
		                (DDR2_T_RCD << 19) | \
		                (DDR2_T_WR << 16)  | \
		                (DDR2_T_RAS << 11) | \
		                (DDR2_T_RC << 6)   | \
		                (DDR2_T_RRD << 3)  | \
		                (DDR2_T_WTR << 0)
#define DDR2_SDTIMR2_VAL_162	(DDR2_T_RASMAX << 27) | \
		                (DDR2_T_XP << 25 )    | \
		                (DDR2_T_XSNR << 16)   | \
		                (DDR2_T_XSRD << 8)    | \
                		(DDR2_T_RTP << 5)     | \
		                (DDR2_T_CKE << 0)

SDTIM0_VAL_162MHz:
	.word	DDR2_SDTIMR_VAL_162		//0x4b245c12(flash_utils), 0x28923211(uboot)
SDTIM1_VAL_162MHz:
	.word	DDR2_SDTIMR2_VAL_162		//0x3a28c742(flash_utils), 0x0016c722(uboot)
DUMMY_VAL:
	.word	0xa55aa55a
/* Works on Always On power domain only (no PD argument) */
//In: r0 - (unsigned int id)
//	r7 - M2_BASE
lpsc_On:
	WaitForBitLow r1,r7,M2_PTSTAT,0x01	//Wait for Transition Complete(PTSTAT)
	add		r2,r7,#M2_MDSTAT_
	ldr		r1,[r2,r0,LSL #2]	//mdstat
	and		r1,r1,#0x1f
	cmp		r1,#3
	moveq	pc,lr		//return if already on and enabled

	add		r2,r7,#M2_MDCTL_
	ldr		r1,[r2,r0,LSL #2]	//mdctl
	orr		r1,r1,#3
	str		r1,[r2,r0,LSL #2]	//mdctl

	cmp		r0,#DAVINCI_LPSC_GPIO
// Special treatment for some modules as for sprue14 p.7.4.2
	ldreq	r1,[r2,r0,LSL #2]	//mdctl
	orreq	r1,r1,#0x200
	streq	r1,[r2,r0,LSL #2]	//mdctl

	mov		r1,#1
	str		r1,[r7,#M2_PTCMD]

	WaitForBitLow r1,r7,M2_PTSTAT,0x03	//Wait for Transition Complete(PTSTAT)
	add		r2,r7,#M2_MDSTAT_
99:	ldr		r1,[r2,r0,LSL #2]	//mdstat
	and		r1,r1,#0x1f
	cmp		r1,#3
	bne		99b
	mov		pc,lr
90:
	.endm

	.macro	NandInit	rEMIF,rGP
//Initialize nand cs2
			//selectStrobe,extWait,writeSetup(10ns),writeStrobe(40ns),writeHold(10ns),readSetup(10ns),readStrobe(60ns),readHold(10ns),turnAround(??ns),dataSize(8-bit bus)
	.equiv	acfg, ((0<<31)|(0<<30)|(1<<26)         |(3<<20)          |(1<<17)        |(1<<13)        |(5<<7)          |(1<<4)        |(3<<2)          |(0<<0))
	BigMov	r0,PLL_BASE
	ldr		r1,[r0,#_BOOTCFG]
	BigMov	r0,acfg
	mov		r1,r1,LSR #5
	and		r1,r1,#1
	orr		r0,r0,r1
	str		r0,[\rEMIF,#EMIF_A1CR]
	mov		r0,#1
	str		r0,[\rEMIF,#EMIF_NANDFCR]

	.ifdef NAND_GPIO_READY
	ldr		r0,[\rGP,#GP_DIR]
	orr		r0,r0,#1<<(NAND_GPIO_READY&0x1f)
	str		r0,[\rGP,#GP_DIR]		//make sure it's an input
	.endif
	.endm
