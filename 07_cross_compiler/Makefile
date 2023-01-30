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
	$(CC) $(CFLAGS) -c kernel.cpp -o kernel.o
	$(LD) -o kernel.tmp -Ttext 0x7e00 extended_program.o kernel.o
	objcopy -O binary kernel.tmp kernel.bin
	cat bootloader.bin kernel.bin > $@


clean:
	$(RM) bootloader.bin kernel.bin kernel.tmp kernel.o extended_program.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	$(EMU) $(EFLAGS) $(NAME)

install:
	bash cross_compiler/toolchain.sh
