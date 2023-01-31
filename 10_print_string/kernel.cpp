#include "text_print.cpp"


extern "C" void _start()
{
	set_cursor(pos_from_coords(0, 0));
	print_string("Hello World!\nNew Line\n");
	print_string(hex_to_string(0x1234aabc));
	return ;
}
