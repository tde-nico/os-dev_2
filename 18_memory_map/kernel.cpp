#include "text_print.cpp"
#include "idt.cpp"
#include "keyboard_handler.cpp"
#include "memory_map.cpp"

extern const char Test[];

extern "C" void _start()
{
	set_cursor(pos_from_coords(0, 0));
	initialize_idt();

	main_keyboard_handler = keyboard_handler;

	float f = -672.938f;
	print_string(float_to_str(f, 10));

	set_cursor(pos_from_coords(0, 3));
	print_string(int_to_str(MemoryRegionCount));

	return ;
}
