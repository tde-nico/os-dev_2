#include "text_print.cpp"


extern "C" void _start()
{
	set_cursor(pos_from_coords(0, 0));
	print_string("Hello World!\nNew Line\n", BACKGROUND_BLINKINGRED | FOREGROUND_CYAN);
	print_string(hex_to_string(0x1234aabc));
	clear_screen();
	set_cursor(pos_from_coords(0, 0));
	print_string("Cleared");
	return ;
}
