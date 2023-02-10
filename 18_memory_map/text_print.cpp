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

void	print_char(char chr, uint_8 color = BACKGROUND_BLACK | FOREGROUND_WHITE)
{
	*(VGA_MEMORY + g_cursor_position * 2) = chr;
	*(VGA_MEMORY + g_cursor_position * 2 + 1) = color;
	set_cursor(g_cursor_position + 1);
}

char	int_to_str_out[128];
template<typename T>
const char	*int_to_str(T value)
{
	uint_8	size;
	uint_8	index;
	uint_8	remainder;
	uint_8	is_negative;
	uint_64	size_tester;
	uint_64	new_value;

	size = 0;
	index = 0;
	is_negative = 0;
	if (value < 0)
	{
		is_negative = 1;
		value *= -1;
		int_to_str_out[0] = '-';
	}
	size_tester = (uint_64)value;
	new_value = (uint_64)value;
	while (size_tester / 10 > 0)
	{
		size_tester /= 10;
		++size;
	}
	while (new_value / 10 > 0)
	{
		remainder = new_value % 10;
		new_value /= 10;
		int_to_str_out[is_negative + size - index] = remainder + 48;
		++index;
	}
	remainder = new_value % 10;
	int_to_str_out[is_negative + size - index] = remainder + 48;
	int_to_str_out[is_negative + size + 1] = 0;
	return (int_to_str_out);
}

char float_to_str_out[128];
const char* float_to_str(float value, uint_8 decimals)
{
	char	*int_ptr;
	char	*float_ptr;
	float	new_value;
	uint_8	i;

	int_ptr = (char*)int_to_str((int)value);
	float_ptr = float_to_str_out;
	if (value < 0)
		value *= -1;
	while (*int_ptr)
	{
		*float_ptr = *int_ptr;
		int_ptr++;
		float_ptr++;
	}
	*float_ptr = '.';
	float_ptr++;
	new_value = value - (int)value;
	i = -1;
	while (++i < decimals)
	{
		new_value *= 10;
		*float_ptr = (int)new_value + 48;
		new_value -= (int)new_value;
		float_ptr++;
	}
	*float_ptr = 0;
	return (float_to_str_out);
}
