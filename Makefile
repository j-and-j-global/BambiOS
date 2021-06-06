SHELL = /bin/sh
CFLAGS = -m32 -fno-stack-protector -da -Q -g -Wall -Wextra -pedantic -O2 -pipe

OBJS := build/kasm.o       \
	build/kc.o         \
	build/printer.o    \
	build/cmos.o       \
	build/rtc.o        \
	build/time.o       \
	build/strings.o    \
	build/buffer.o     \
	build/menu.o       \
	build/io.o         \
	build/keyboard.o

all: build dist/kernel .build_machine

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

build/kc.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

build/printer.o: std/printer.c
	$(CC) $(CFLAGS) -c $< -o $@

build/cmos.o: hardware/cmos.c
	$(CC) $(CFLAGS) -c $< -o $@

build/rtc.o: driver/rtc.c
	$(CC) $(CFLAGS) -c $< -o $@

build/time.o: std/time.c
	$(CC) $(CFLAGS) -c $< -o $@

build/strings.o: std/strings.c
	$(CC) $(CFLAGS) -c $< -o $@

build/buffer.o: buffer.c
	$(CC) $(CFLAGS) -c $< -o $@

build/menu.o: app/menu.c  app/app_gen.h
	$(CC) $(CFLAGS) -c $< -o $@

build/io.o: hardware/io.c
	$(CC) $(CFLAGS) -c $< -o $@

build/keyboard.o: driver/keyboard.c
	$(CC) $(CFLAGS) -c $< -o $@

dist/kernel: $(OBJS) dist
	ld -m elf_i386 -T link.ld -o $@ $(OBJS)

tests: test
	$(CC) -fno-stack-protector -da -Q -g -Wall -Wextra -pedantic -pipe std/strings.c std/time.c std/printer.c hardware/test_cmos.c driver/rtc.c test.c -o test/test
	./test/test

clean:
	-rm -rf build/ dist/ test/ *.c.*

.build_machine: dist/kernel
	uname -a > .build_machine

.PHONY: boot
boot: dist/kernel
	qemu-system-i386 -kernel dist/kernel
