#pragma once
#include "io.cpp"
#include "typedefs.cpp"
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
