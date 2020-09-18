;
;   port_io.asm by V01D
;       Declares outb & inb function.

global outb
global inb
global outw

;   Stack setup:
;       [esp+8] =  data byte
;       [esp+4] = I/O port
;       [esp  ] = return value
;
;   C wrapper:
;      void outb(unsigned int port, unsigned int data);
;
;   Possible registers to be used for outb:
;      EAX, AX, AH, AL
;      EDX, DX, DH, DL

outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al ; send data (al) to port (dx)
    ret

inb:
    mov dx, [esp + 4]
    in al, dx
    ret
outw:
    mov ax, [esp + 8]
    mov dx, [esp + 4]
    out dx, ax ; send data (al) to port (dx)
    ret
