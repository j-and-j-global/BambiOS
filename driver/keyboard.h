/**
   keyboard.h, James Condron 2019

   Provide access to and from keyboard events
 **/

#ifndef KEYBOARD_DATA_PORT
#define KEYBOARD_DATA_PORT 0x60
#endif

#ifndef KEYBOARD_STATUS_PORT
#define KEYBOARD_STATUS_PORT 0x64
#endif

#ifndef IDT_SIZE
#define IDT_SIZE 256
#endif

#ifndef INTERRUPT_GATE
#define INTERRUPT_GATE 0x8E
#endif

#ifndef KERNEL_CODE_SEGMENT_OFFSET
#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#endif

/**
   Access to stuff in our asm files
 **/
extern void keyboard_handler(void);
extern void load_idt(unsigned long *idt_ptr);

/**
   Initialise IDT Table
 **/
void idt_init(void);

/**
   Initialise keyboard stuff
 **/
void kb_init(void);

/**
   Adjusted and tweaked map of indices to key value.

   Since we're only fussed about directions, we're going
   to map arrows to wasd too, which will do our paging/ scrolling
 **/

#ifndef KBM_INITIALISED
#define KBM_INITIALISED 1
#endif
