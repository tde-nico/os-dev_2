NAME = image.iso

AC = nasm
CC = x86_64-elf-gcc
CFLAGS = -ffreestanding -mno-red-zone -m64
LD = x86_64-elf-ld
RM = rm -rf
EMU = qemu-system-x86_64
EFLAGS = -curses


all: $(NAME)

$(NAME):
	$(AC) -f bin bootloader.asm -o bootloader.bin
	$(AC) -f elf64 extended_program.asm -o extended_program.o
	$(AC) -f elf64 binaries.asm -o binaries.o
	$(CC) $(CFLAGS) -Ttext 0x8000 -c kernel.cpp -o kernel.o
	$(LD) -T"link.ld"
	cat bootloader.bin kernel.bin > $@


clean:
	$(RM) bootloader.bin kernel.bin kernel.o extended_program.o binaries.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	$(EMU) $(EFLAGS) $(NAME)

install:
	bash cross_compiler/toolchain.sh
