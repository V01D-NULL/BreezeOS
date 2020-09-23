# BreezeOS
Breeze OS is an experimental 32 bit operating system under active development
(This is the second branch, in which I hope to fix the bugs below by rewriting everything in the src/cpu/idt/ folder)

# Bug tracker:
    1. ISR's do not correctly catch `int` interrupts. (Cause the errror without the int opcode and the kernel returns the correct message. Use the `int` opcode and the kernel returns interrupt 15 - Unknown interrupt) -- Status: [ INCOMPLETE ]
    2. IRQ's do not fire off. -- Status: [ INCOMPLETE ]
