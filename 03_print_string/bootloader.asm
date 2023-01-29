[org 0x7c00]

mov bp, 0x7c00
mov sp, bp

mov bx, TestString
call PrintString


jmp $


TestString:
	db 'Hello World!', 0


PrintString:
	mov ah, 0x0e
	.loop:
		cmp [bx], byte 0
		je .exit
			mov al, [bx]
			int 0x10
			inc bx
			jmp .loop
	.exit:
	ret


times 510-($-$$) db 0
dw 0xaa55
