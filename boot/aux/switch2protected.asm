[bits 16]
; switch to protected mode
switch_to_pm:
	cli						; we must switch of interrupts until we have setup the protected
							; mode interrupt vector otherwise interrupts will run riot.
	lgdt [gdt_descriptor]	; load our global descriptor table
	
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	
	jmp CODE_SEG:init_pm	; make a far jump (i.e. to a new segment) to our 32 - bit code
							; this also forces the CPU to flush its cache of prefetched
							; and real mode decoded instructions, witch can cause problems
	
[bits 32]
; initialize registers and the stack in protected mode
init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0x90000
	mov esp, ebp
	
	call BEGIN_PM