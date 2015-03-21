; A boot sector that enters 32 - bit protected mode
[org 0x7c00]
KERNEL_OFFSET equ 0x2000

	mov [BOOT_DRIVER], dl

	mov bp, 0x9000						; set the stack
	mov sp, bp

	mov bx, MSG_REAL_MODE
	call print_string
	
	call load_kernel					; load our kernel
	lidt [idt]							; load idt
	
	call switch_to_pm					; we never return from here

	jmp $

[bits 16]
; load kernel

load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print_string
	
	mov bx, 0x1000
	mov ah, 0x02			; floppy read sector command
	mov al, 0x1f			; number of sectors to read
	mov ch, 0x00			; cylinder
	mov cl, 0x02			; base sector
	mov dh, 0x00			; head
	int 0x13
	or ah, ah
	jnz .diskerror
	
	ret
	
.diskerror:
	mov bx, MSG_DISK_ERROR
	call print_string
	cli
    hlt

	%include './aux/printstring.asm'
	%include './aux/gdt.asm'
	%include './aux/switch2protected.asm'

[bits 32]
BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm
	
	call KERNEL_OFFSET
	
	jmp $
	
BOOT_DRIVER db 0
MSG_REAL_MODE db 'Started in 16 - bits real mode', 0
MSG_PROT_MODE db 'Successfully landed in 32 - bit protected mode', 0
MSG_LOAD_KERNEL db 'Loading kernel into memory...', 0
MSG_DISK_ERROR db 'Disk read error', 0

	times 510 - ($ - $$) db 0
	dw 0xaa55
	
	%include './aux/idt.asm'