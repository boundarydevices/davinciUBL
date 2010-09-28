	.equiv	SOH, 1
	.equiv	STX, 2
	.equiv	EOT, 4
	.equiv	ACK, 6
	.equiv	NAK, 0x15
	.equiv	CAN, 0x18

	.equiv	CRC_POLY, 0x10210000


//In: rDestStart - where to start download
//Out: z-1 success, rDest - past last byte downloaded, rDestStart - first byte downloaded
.macro xmodemReceive rDest,rPacketLength,rDestHead,rBlockNum,rNak,rCRC,rRunningCRC,rPrevCRC,rDestStart,Transmit,Receive

	mov	\rDestHead,\rDestStart
	mov	\rDest,\rDestStart
	mov	\rPrevCRC,#0
	mov	\rRunningCRC,#0
	mov	\rNak,#CH_C		//current NAK character
	mov	\rBlockNum,#1		//block # to receive

#if DDEBUG
	b	47f
91:
	cmp	\rBlockNum,#1
	beq	47f
	mov	r2,#CH_1
	b	45f
92:
	mov	r2,#CH_2
	b	45f
93:
	mov	r2,#CH_3
	b	45f
94:
	mov	r2,#CH_4
	b	45f
95:
	mov	r2,#CH_5
45:
	BigMov	r0,(CAN)+(CAN<<8)+(CAN<<16)	//abort
	bl	\Transmit
46:	bl	\Receive
	bne	46b			//branch until timeout
	mov	r0,r2
	bl	\Transmit
	b	99f
#else
91:
92:
93:
94:
95:
#endif

47:

	mov	r0,\rNak
15:
	bl	\Transmit
2:	bl	\Receive
	beq	91b			//branch on timeout

	mov	\rPacketLength,#128-1
	cmp	r0,#SOH
	addne	\rPacketLength,\rPacketLength,#1024-1-(128-1)
	cmpne	r0,#STX
	beq	3f
	cmp	r0,#CAN
	bne	16f
81:	bl	\Receive
	beq	81b		//wait for reception of next character
	cmp	r0,#CAN
	bne	10f
	b	99f		//2 cans mean abort
16:	cmp	r0,#EOT
	bne	10f
	b	60f		//EOTFound

3:	bl	\Receive
	beq	92b
	mov	r2,r0
	bl	\Receive
	beq	93b
	eor	r0,r0,#0xff
	cmp	r0,r2			//check 1's complement blk #
	bne	10f
	cmp	r2,\rBlockNum		//check blk #
	bne	20f
80:
	mov	\rDestHead,\rDest		//\rDestHead - start of buffer, \rDest end of buffer
	mov	\rPrevCRC,\rRunningCRC
	mov	\rCRC,#0			//crc

//alternative CRC calculation routines
	.if 0
	BigMov	r2,CRC_POLY
4:	bl	\Receive
	beq	8f			//branch on timeout
	eor	\rCRC,\rCRC,r0,LSL #24
	mov	r1,#8
5:
	movs	\rCRC,\rCRC,LSL #1
	eorcs	\rCRC,\rCRC,r2
	subs	r1,r1,#1
	bne	5b
	strb	r0,[\rDest],#1
	subs	\rPacketLength,\rPacketLength,#1
	bge	4b
	mov	\rCRC,\rCRC,LSR #16	//CRC was only in the high half

	.endif



	.if 1
4:	bl	\Receive
	beq	8f			//branch on timeout
//
//calculate CRC
//unsigned int crc = 0;
//unsigned int c = 0;
//for (i=3; i<max; i++)
//{
//	c = crc ^ (buf[i]<<24);
//	c ^= (c >> 4);
//	c &= 0xff000000;
//	crc = (((crc<<8) ^ (c << 4)) |  (c>>8)) ^ (c >> 3);
//}
//crc >>= 16;
//
	eor	r1,\rCRC,r0,LSL #24
	eor	r1,r1,r1,LSR #4
	and	r1,r1,#0xff000000

	mov	\rCRC,\rCRC,LSL #8
	eor	\rCRC,\rCRC,r1,LSL #4
	orr	\rCRC,\rCRC,r1,LSR #8
	eor	\rCRC,\rCRC,r1,LSR #3

//also save a running total CRC to use to verify RAM after download is complete
//
	eor	r1,\rRunningCRC,r0,LSL #24
	eor	r1,r1,r1,LSR #4		//c is in high byte of r1
	and	r1,r1,#0xff000000

	mov	\rRunningCRC,\rRunningCRC,LSL #8
	eor	\rRunningCRC,\rRunningCRC,r1,LSL #4
	orr	\rRunningCRC,\rRunningCRC,r1,LSR #8

	eor	\rRunningCRC,\rRunningCRC,r1,LSR #3
//
#if BIG_ENDIAN
	orr	r2,r0,r2,LSL #8		//this assumes a big endian memory system
#else
	mov	r0,r0,LSL #24
	orr	r2,r0,r2,LSR #8		//this assumes a little endian memory system
#endif

	tst	\rPacketLength,#3
	streq	r2,[\rDest],#4
	subs	\rPacketLength,\rPacketLength,#1
	bge	4b
	mov	\rCRC,\rCRC,LSR #16	//CRC was only in the high half
	.endif




	bl	\Receive
	beq	8f			//branch on timeout
	mov	r2,r0
	bl	\Receive
	beq	8f			//branch on timeout
	add	r2,r0,r2,LSL #8
	cmp	\rCRC,r2
	bne	9f			//branch on crc mismatch
//packet is good
	add	\rBlockNum,\rBlockNum,#1
	and	\rBlockNum,\rBlockNum,#0xff
	mov	\rNak,#NAK
	mov	r0,#ACK
	b	15b
20:
	sub	r1,\rBlockNum,#1
	and	r1,r1,#0xff
	cmp	r1,r2
	bne	21f			//br if not trying to transmit the packet I just ACKed
	mov	\rDest,\rDestHead		//reset pointer to previous packet
	mov	\rRunningCRC,\rPrevCRC
	mov	\rBlockNum,r1		//correct blk #
	b	80b

21:	BigMov	r0,(CAN)+(CAN<<8)+(CAN<<16)	//abort code
	bl	\Transmit
48:	bl	\Receive
	bne	48b			//branch until timeout

#if DDEBUG
	mov	r0,r2
	bl	PrintHex
	bl	50f		//Transmit SPACE
	mov	r0,\rBlockNum
	bl	PrintHex
#endif

	b	99f			//give up


8:	mov	\rDest,\rDestHead		//reset register
	mov	\rRunningCRC,\rPrevCRC
	b	94b			//send NAK
9:
#if DDEBUG				//debug code
	BigMov	r0,(CAN)+(CAN<<8)+(CAN<<16)	//abort code
	bl	\Transmit
44:	bl	\Receive
	bne	44b			//branch until timeout
	mov	r0,r2
	bl	PrintHex
	bl	50f		//Transmit SPACE
	mov	r0,\rCRC
	bl	PrintHex
	b	99f
#endif

	mov	\rDest,\rDestHead
	mov	\rRunningCRC,\rPrevCRC


10:	bl	\Receive
	bne	10b			//branch until timeout
	b	95b			//send NAK and wait for packet

99:
	movs r0,#1
	b	63f			//ExitX
//////////////////////////////////////////////////////////////
#if DDEBUG				//debug code
//Transmit SPACE
50:
	mov	r0,#CH_SPACE
	b	\Transmit
#endif

//////////////////////////////////////////////////////////////
//EOTFound
60:
	mov	r0,#ACK
	bl	\Transmit

#if DDEBUG
	mov	\rDestHead,\rDest
	mov	r0,\rDest
	bl	PrintHex
	bl	50b		//Transmit SPACE
	mov	r0,\rBlockNum
	bl	PrintHex

	bl	50b		//Transmit SPACE
	mov	r0,\rRunningCRC
	bl	PrintHex
	mov	\rDest,\rDestHead
#endif

// now verify that ram is STILL valid by recomputing the CRC
	mov	\rCRC,#0
	mov	r1,\rDestStart
	b	62f
61:
	ldr	r2,[r1]
66:
#if BIG_ENDIAN
	mov	r0,r2,LSR #24		//Big
#else
	and	r0,r2,#0xff			//Little
#endif
//
	eor	r0,\rCRC,r0,LSL #24
	eor	r0,r0,r0,LSR #4		//c is in high byte of r0
	and	r0,r0,#0xff000000

	mov	\rCRC,\rCRC,LSL #8
	eor	\rCRC,\rCRC,r0,LSL #4
	orr	\rCRC,\rCRC,r0,LSR #8

	eor	\rCRC,\rCRC,r0,LSR #3
#if BIG_ENDIAN
	mov	r2,r2,LSL #8	//Big
#else
	mov	r2,r2,LSR #8	//Little
#endif
	add	r1,r1,#1
	tst	r1,#3
	bne	66b
//
62:	cmp	r1,\rDest
	bne	61b
#if DDEBUG
	bl	50b		//Transmit SPACE
	mov	r0,\rCRC
	bl	PrintHex
#endif

	cmp	\rCRC,\rRunningCRC
63:
.endm
