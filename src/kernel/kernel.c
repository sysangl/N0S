#include "screen.h"
#include "timer.h"
#include "math.h"
#include "donut.h"

void k_main() 
{
    //timer_init();
    //__asm__ volatile ("sti");
    k_printlogo(0,0);
    //k_clear_screen();
    //while (1)
    //    k_donut();
}


void __stack_chk_fail() {
	k_printf("Stack check failed!",0,0);
	while (1);
}