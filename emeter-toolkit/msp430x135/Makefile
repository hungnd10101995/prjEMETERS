#
# $Id: Makefile,v 1.4 2004/03/01 09:12:20 A0754793 Exp $
#
TARGET_MCU=msp430x135
LIBNAME=libemeter-toolkit.a
MSP430INC=

CC=msp430-gcc
AR=msp430-ar
CFLAGS=-O2 -g -Wall -mmcu=$(TARGET_MCU) $(MSP430INC) -I..

objects=host_decu16.o \
        host_decu32.o \
        host_dec16.o \
        host_dec32.o \
        host_hex16.o \
        host_hex32.o \
        host_str.o \
        host_char.o \
        LCDdecu16.o \
        LCDdecu32.o \
        LCDdec16.o \
        LCDdec32.o \
        LCD-module.o \
        LCD-internal.o \
        hex2ASCII.o \
        bin2bcd16.o \
        bin2bcd32.o \
        flash_clr.o \
        flash_secure.o \
        flash_memcpy.o \
        flash_write_int8.o \
        flash_write_int16.o \
        flash_write_int32.o \
        flash_replace16.o \
        flash_replace32.o \
        iiceeprom.o \
        rtc.o \
		rtc_data.o \
        dds.o \
        rand16.o \
        dc_filter.o \
        imul16.o \
        isqrt32.o \
        isqrt32i.o \
        q1_15_mul.o \
        q1_15_mulr.o \
        q1_15_mulq.o \
		accum48.o \
		div48.o \
		mul48.o \
		shift48.o \
        debounce.o

all: $(LIBNAME)

clean:
	rm -f *.obj *.asm *.map *.lst *.lib *.tmp *.exe *.o *.a *.hex *.qer *~

$(LIBNAME): ${objects}
	$(AR) -r $(LIBNAME) ${objects}

$(objects): %.o: ../%.c
	$(CC) -c $(CFLAGS) $< -o $@

#automatic collection of dependencies in the source files.
#it's only updated the first time, after that it must be done maually
#with "make depend"
#the dependecies are included from a separate file:
-include dependencies.in
#target to update the file, it's removed first
depend: rmdepend dependencies.in
#remove the file
rmdepend:
	rm -f dependencies.in
#build the file that contains the dependencies. no deps in this rule.
#if there were deps it would be rebuilt every chnage, which is unneded:
dependencies.in:
	$(CC) -MM ${CFLAGS} $(patsubst %.o,../%.c,$(objects)) >$@
