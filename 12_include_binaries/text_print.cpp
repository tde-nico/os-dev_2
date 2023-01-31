#pragma once
#include "io.cpp"
#include "typedefs.cpp"
#include "text_mode_color_codes.cpp"
#define VGA_MEMORY (uint_8 *)0xb8000
#define VGA_WIDTH 80

uint_16	g_cursor_position;

void	set_cursor(uint_16 position)
{
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint_8)(position & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint_8)((position >> 8) & 0xFF));
	g_cursor_position = position;
}

uint_16	pos_from_coords(uint_8 x, uint_8 y)
{
	return (y * VGA_WIDTH + x);
}

void	print_string(const char *str, uint_8 color = BACKGROUND_BLACK | FOREGROUND_WHITE)
{
	uint_8	*ptr = (uint_8 *)str;
	uint_16	index = g_cursor_position;
	while (*ptr != 0)
	{
		if (*ptr == 10)
			index += VGA_WIDTH - index % VGA_WIDTH;
		else
		{
			*(VGA_MEMORY + index * 2) = *ptr;
			*(VGA_MEMORY + index * 2 + 1) = color;
			++index;
		}
		++ptr;
	}
	set_cursor(index);
}

char g_hex_string[128];
template<typename T>
const char	*hex_to_string(T value){
	T		*val_ptr = &value;
	uint_8	*ptr;
	uint_8	temp;
	uint_8	size = (sizeof(T)) * 2 - 1;
	uint_8	i;

	i = -1;
	while (++i < size)
	{
		ptr = ((uint_8 *)val_ptr + i);
		temp = ((*ptr & 0xF0) >> 4);
		g_hex_string[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
		temp = ((*ptr & 0x0F));
		g_hex_string[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
	}
	g_hex_string[size + 1] = 0;
	return (g_hex_string);
}

void	clear_screen(uint_64 color = BACKGROUND_BLACK | FOREGROUND_WHITE)
{
	uint_64	value;

	value = 0;
	value += color << 8;
	value += color << 24;
	value += color << 40;
	value += color << 56;
	for (uint_64 *i = (uint_64 *)VGA_MEMORY; i < (uint_64 *)(VGA_MEMORY + 4000); i++)
	{
		*i = value;
	}
}
