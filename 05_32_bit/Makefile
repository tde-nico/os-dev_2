AC = nasm
AFLAGS = -f bin
RM = rm -rf
EMU = qemu-system-x86_64
EFLAGS = -curses

SRCS = sector_1/bootloader.asm sector_2/extended_program.asm
OBJS = $(SRCS:%.asm=%.bin)

NAME = image.iso

%.bin: %.asm
	$(AC) $(AFLAGS) $^ -o $@

all: $(NAME)

$(NAME): $(OBJS)
	cat $^ > $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	$(EMU) $(EFLAGS) $(NAME)
