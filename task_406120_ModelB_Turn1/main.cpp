#include <iostream>
#include "isr.h"

extern "C" {
    /* We need to provide prototypes for the x86 IDT entry structure and its declarations */
    typedef struct {
        unsigned short offset_low;    /* Lower 16 bits of the code offset */
        unsigned short selector;      /* Segment selector for the code */
        unsigned char zero;           /* Always zero */
        unsigned char flags;         /* Descriptor Type, Privilege Level, Present */
        unsigned short offset_high;   /* Upper 8 bits of the code offset */
    } idt_entry_t;

    typedef struct {
        idt_entry_t entries[256]; /* 32-bit systems only have 256 interrupts/exceptions */
        unsigned int base;
        unsigned int limit;
        unsigned char zero1;
        unsigned char access;       /* Interrupt Gate always has type 0xE */
        unsigned char zero2;
    } idtr_t;
}

/*  x86 IDT starts at address 0x0 */
idt_entry_t idt[256];
idtr_t idtr = {0};

void install_idt() {
    idtr.limit = (sizeof(idt_entry_t) * 256) - 1;
    idtr.base = (unsigned int)&idt[0];
    
    _asm(
        "lidt %0"
        :: "m" (idtr)
    );
}

int main() {
    // Set up Interrupt Service Routine
    isr_setup();
    install_idt();
    
    // Run your embedded C++ code here
    std::cout << "Welcome to Embedded System C++ Project! Press any key to return." << std::endl;

    // We will temporarily disable interrupts to handle the sensor and then enable them back on
    return 0;
}
