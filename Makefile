SHELL = /bin/sh
CFLAGS = -m32 -fno-stack-protector -da -Q -g -Wall -Wextra -pedantic -O2 -pipe

default: all

build:
	mkdir -p build/

dist:
	mkdir -p dist/

test:
	mkdir -p test/

app/app_gen.h:
	go get -u github.com/j-and-j-global/records-c-generator
	records-c-generator -i config/records.csv > app/app_gen.h

build/kasm.o: build
	nasm -f elf32 kernel.asm -o build/kasm.o

build/kc.o: build
	$(CC) $(CFLAGS) -c kernel.c -o build/kc.o

build/printer.o: build
	$(CC) $(CFLAGS) -c std/printer.c -o build/printer.o

build/cmos.o: build
	$(CC) $(CFLAGS) -c hardware/cmos.c -o build/cmos.o

build/rtc.o: build
	$(CC) $(CFLAGS) -c driver/rtc.c -o build/rtc.o

build/time.o: build
	$(CC) $(CFLAGS) -c std/time.c -o build/time.o

build/strings.o: build
	$(CC) $(CFLAGS) -c std/strings.c -o build/strings.o

build/buffer.o: build
	$(CC) $(CFLAGS) -c buffer.c -o build/buffer.o

build/menu.o: build app/app_gen.h
	$(CC) $(CFLAGS) -c app/menu.c -o build/menu.o

build/io.o: build
	$(CC) $(CFLAGS) -c hardware/io.c -o build/io.o

build/keyboard.o: build
	$(CC) $(CFLAGS) -c driver/keyboard.c -o build/keyboard.o

dist/kernel: dist build/kasm.o app/app_gen.h build/kc.o build/printer.o build/cmos.o build/rtc.o build/time.o build/strings.o build/buffer.o build/menu.o build/io.o build/keyboard.o
	ld -m elf_i386 -T link.ld -o dist/kernel build/kasm.o build/kc.o build/printer.o build/cmos.o build/rtc.o build/time.o build/strings.o build/buffer.o build/menu.o build/io.o build/keyboard.o

tests: test
	$(CC) -fno-stack-protector -da -Q -g -Wall -Wextra -pedantic -pipe std/strings.c std/time.c std/printer.c hardware/test_cmos.c driver/rtc.c test.c -o test/test
	./test/test

all: dist/kernel _buildfile

clean:
	-rm -rf build/ dist/ test/ *.c.*

.PHONY: _buildfile

_buildfile:
	uname -a > .build_machine
