#include "text_print.cpp"
#include "idt.cpp"
#include "keyboard_handler.cpp"

extern const char Test[];

extern "C" void _start()
{
	set_cursor(pos_from_coords(0, 0));
	initialize_idt();

	main_keyboard_handler = keyboard_handler;

	float f = -672.938f;
	print_string(float_to_str(f, 10));

	return ;
}
