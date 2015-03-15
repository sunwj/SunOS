;
;	Print register content to the screen
;

; use DX as the parameter register

print_reg:
	pusha

	mov ah, 0x0E					; BIOS teletype interrupt mode to teletype output
	mov bx, .hexstring				; put hexstring address into BX
	
	; print '0x' before hexadecimal number
	mov al, '0'
	int 0x10
	mov al, 'x'
	int 0x10

	mov cx, 4						; loop count
.repeat:
	rol dx, 4						; acquire each 4 bit of DX from most significant bit
	mov al, dl
	and al, 0x0F
	push bx
	add bl, al						; calculate character address in hexstring table
	mov al, [bx]
	pop bx
	int 0x10						; trigger BIOS interrupt
	loop .repeat

	popa
	ret

.hexstring: db '0123456789ABCDEF'