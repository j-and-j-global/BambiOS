default: all

build:
	mkdir -p build/

dist:
	mkdir -p dist/

test:
	mkdir -p test/

build/kasm.o: build
	nasm -f elf32 kernel.asm -o build/kasm.o

build/kc.o: build
	gcc -m32 -c kernel.c -o build/kc.o

build/printer.o: build
	gcc -m32 -c std/printer.c -o build/printer.o

build/cmos.o: build
	gcc -m32 -c hardware/cmos.c -o build/cmos.o

build/rtc.o: build
	gcc -m32 -c driver/rtc.c -o build/rtc.o

dist/kernel: dist build/kasm.o build/kc.o build/printer.o build/cmos.o build/rtc.o
	ld -m elf_i386 -T link.ld -o dist/kernel build/kasm.o build/kc.o build/printer.o build/cmos.o build/rtc.o

tests:
	gcc -v -da -Q -g -Wall -Wextra -pedantic hardware/test_cmos.c driver/rtc.c test.c -o test/test
	./test/test

all: dist/kernel _buildfile

clean:
	-rm -rf build/ dist/ test/

.PHONY: _buildfile

_buildfile:
	uname -a > .build_machine
