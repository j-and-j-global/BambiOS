bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002            ;magic
        dd 0x00                  ;flags
        dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

global start
global keyboard_handler
global load_idt
global byebye

extern kmain            ;kmain is defined in the c file
extern scroll_menu

start:
  cli                   ;block interrupts
  mov esp, stack_space	;set stack pointer
  call kmain
  hlt                     ;halt the CPU

load_idt:
  mov edx, [esp + 4]
  lidt [edx]
  sti                             ;turn on interrupts
  ret

keyboard_handler:
  call    scroll_menu
  iretd

byebye:
  mov ax, 5307h
  mov cx, 3
  mov bx, 1
  int 15h

section .bss
resb 8192		;8KB for stack
stack_space:
