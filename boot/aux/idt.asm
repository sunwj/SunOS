; IDT
[bits 16]
idt:
	times 2048 dw 0x0
idt_end: