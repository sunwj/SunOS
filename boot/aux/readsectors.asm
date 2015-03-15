;
;	load sectors to ES : BX from disk driver
;

; DL, driver number
; CH, cylinder number
; DH, head number
; CL, base sector number
; AL, sectors to read

read_sectors:
	pusha
	
	mov [.SECTORS_TO_READ], al
	mov ah, 0x02				;BIOS read sector function
	int 0x13					;BIOS interrupt related to disk manipulation
	
	jc .disk_error				;jump if error (carry flag set)
	
	cmp al, [.SECTORS_TO_READ]
	jne .disk_error
	
	popa
	ret
	
.disk_error:
	lea bx, [.DISK_ERR_MSG]
	call print_string
	jmp $
	
.SECTORS_TO_READ: db 0
.DISK_ERR_MSG: db 'Disk read error!', 0