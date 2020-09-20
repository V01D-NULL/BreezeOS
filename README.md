# BreezeOS
Breeze OS is an experimental 32 bit operating system under active development

# Bug tracker:
    1. ISR's do not correctly catch `int` interrupts. (Cause the errror without the int opcode and the kernel returns the correct message. Use the `int` opcode and the kernel returns interrupt 15 - Unknown interrupt)
    2. IRQ's do not fire off. -- Status: [ INCOMPLETE ]
