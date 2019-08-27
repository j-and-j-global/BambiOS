#include "keyboard.h"
#include "../hardware/io.h"

struct IDT_entry{
  unsigned short int offset_lowerbits;
  unsigned short int selector;
  unsigned char zero;
  unsigned char type_attr;
  unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void) {
  unsigned long keyboard_address;
  unsigned long idt_address;
  unsigned long idt_ptr[2];

  /* populate IDT entry of keyboard's interrupt */
  keyboard_address = (unsigned long)keyboard_handler;
  IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
  IDT[0x21].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[0x21].zero = 0;
  IDT[0x21].type_attr = 0x8e; /* INTERRUPT_GATE */
  IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;


  /*     Ports
   *        PIC1	PIC2
   *Command 0x20	0xA0
   *Data    0x21	0xA1
   */

  /* ICW1 - begin initialization */
  //write_port(0x20 , 0x11);
  //write_port(0xA0 , 0x11);

  outb_p(0x11, 0x20);
  outb_p(0x11, 0xA0);


  /* ICW2 - remap offset address of IDT */
  /*
   * In x86 protected mode, we have to remap the PICs beyond 0x20 because
   * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
   */
  //write_port(0x21 , 0x20);
  //write_port(0xA1 , 0x28);
  outb_p(0x20, 0x21);
  outb_p(0x28, 0xA1);

  /* ICW3 - setup cascading */
  //write_port(0x21 , 0x00);
  //write_port(0xA1 , 0x00);
  outb_p(0x00, 0x21);
  outb_p(0x00, 0xA1);

  /* ICW4 - environment info */
  //write_port(0x21 , 0x01);
  //write_port(0xA1 , 0x01);
  outb_p(0x01, 0x21);
  outb_p(0x01, 0xA1);

  /* Initialization finished */

  /* mask interrupts */
  //write_port(0x21 , 0xff);
  //write_port(0xA1 , 0xff);
  outb_p(0xFF, 0x21);
  outb_p(0xFF, 0xA1);

  /* fill the IDT descriptor */
  idt_address = (unsigned long)IDT ;
  idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
  idt_ptr[1] = idt_address >> 16 ;

  load_idt(idt_ptr);
}

void kb_init(void) {
  /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
  //   write_port(0x21 , 0xFD);
  outb_p(0xFD, 0x21);
}
