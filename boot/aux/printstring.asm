;
;	Print text message onto screen
;

; BX stores the address of the string to be printed

[bits 16]

print_string:
	pusha
	
	mov ah, 0x0E						; set teletype mode to output
	
.repeat:
	mov al, [bx]
	int 0x10							; trigger teletype interrupt
	inc bx
	cmp al, 0							; test string terminate symbol
	jne .repeat
	
	popa
	ret

[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x02

; print a null-terminated string pointed to by EDX
; EBX stores the address of the string to be printed
print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY				; set EDX to the start of video memory
	
.repeat:
	mov al, [ebx]						; store the char at EBX in AL
	mov ah, WHITE_ON_BLACK				; store the attribute in AH
	
	cmp al, 0
	je .done
	
	mov [edx], ax
	inc ebx
	add edx, 2
	jmp .repeat
	
.done:
	popa
	ret