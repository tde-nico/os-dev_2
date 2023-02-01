#include "text_print.cpp"
#include "idt.cpp"

extern const char Test[];

bool	left_shift_pressed = false;
bool	right_shift_pressed = false;
uint_8	last_scan_code;

void	standard_keyboard_handler(uint_8 scan_code, uint_8 chr)
{
	if (chr)
	{
		switch (left_shift_pressed | right_shift_pressed)
		{
		case true:
			print_char(chr - 32);
			break;
		case false:
			print_char(chr);
			break;
		}
	}
	else
	{
		switch (scan_code)
		{
		case 0x8E: // Backspace
			set_cursor(g_cursor_position - 1);
			print_char(' ');
			set_cursor(g_cursor_position - 1);
			break;
		case 0x2A: // Left Shift
			left_shift_pressed = true;
			break ;
		case 0xAA: // Left Shift Released
			left_shift_pressed = false;
			break ;
		case 0x36: // Right Shift
			right_shift_pressed = true;
			break ;
		case 0xB6: // Right Shift Released
			right_shift_pressed = false;
			break ;
		case 0x9C: // Enter
			print_string("\n");
			break;
		}
	}
}

void keyboard_handler_0xE0(uint_8 scan_code)
{
	switch (scan_code)
	{
	case 0x50:
		set_cursor(g_cursor_position + VGA_WIDTH);
		break ;
	case 0x48:
		set_cursor(g_cursor_position - VGA_WIDTH);
		break ;
	default:
		break ;
	}
}

void	keyboard_handler(uint_8 scan_code, uint_8 chr)
{
	switch (last_scan_code)
	{
	case 0xE0:
		keyboard_handler_0xE0(scan_code);
		break ;
	default:
		standard_keyboard_handler(scan_code, chr);
		break ;
	}
	last_scan_code = scan_code;
}

extern "C" void _start()
{
	set_cursor(pos_from_coords(0, 0));
	initialize_idt();

	main_keyboard_handler = keyboard_handler;

	return ;
}
