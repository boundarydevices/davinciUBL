.PHONY : clean

CROSS_COMPILE   := arm-v5t-linux-gnueabi-
AS		:= ${CROSS_COMPILE}gcc
OBJCOPY		:= ${CROSS_COMPILE}objcopy
LD		:= ${CROSS_COMPILE}g++
ASFLAGS		:= -nostdlib -fno-strict-aliasing -fno-common -Os 

EXES		:= camera_to_fb2 devregs

%.o : %.S
	echo "=== assembling:" $@ ${ASFLAGS} 
	@${AS} -c ${ASFLAGS} ${INCS} ${DEFS} $< -Wa,-a >`basename $@ .o`.lst -o $@

%.o2: %.o
	@echo "=== linking:" $@
	@${LD} --no-warn-mismatch -nostdlib -T 80008000.lds $< -o $@

%.bin: %.o2
	@echo "=== converting to binary:" $@
	@${OBJCOPY} -O binary --gap-fill 0xff $< $@

BINARIES=davinciUBL.bin

all: ${BINARIES}

clean:
	rm -f ${BINARIES} *.o *.lst *.o2









