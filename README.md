# BreezeOS
Breeze OS is an experimental 32 bit operating system - not under development anymore.

### UPDATE:
	- Oktober 15th ~ I just could not quit this kernel. It will be totally refreshed by redoing the IDT, ISR, IRQ's etc AND GRUB will be REPLACED with a custom bootloader.
	- BreezeOS will be a 64 bit operating system.

# Bug tracker:
    1. ISR's do not correctly catch `int` interrupts. (Cause the errror without the int opcode and the kernel returns the correct message. Use the `int` opcode and the kernel returns interrupt 15 - Unknown interrupt) -- Status: [ INCOMPLETE ]
    2. IRQ's do not fire off. -- Status: [ INCOMPLETE ]
