[org 0x7e00]

mov bx, ExtendedSpaceSuccess
call PrintString

jmp $

%include 'sector_1/print.asm'

ExtendedSpaceSuccess:
	db 'Entered in extended space', 0

times 2048-($-$$) db 0
