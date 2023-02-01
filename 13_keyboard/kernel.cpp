#include "text_print.cpp"
#include "idt.cpp"

extern const char Test[];

extern "C" void _start()
{
	set_cursor(pos_from_coords(0, 0));
	initialize_idt();
	return ;
}
