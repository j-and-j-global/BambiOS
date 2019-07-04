default: all

kasm.o:
	nasm -f elf32 kernel.asm -o kasm.o

kc.o:
	gcc -m32 -c kernel.c -o kc.o

printer.o:
	gcc -m32 -c printer.c -o printer.o

kernel: kasm.o kc.o printer.o
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o printer.o

all: kernel

clean:
	-rm kasm.o kc.o printer.o kernel
