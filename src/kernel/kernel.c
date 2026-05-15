#include <screen.h>
#include <timer.h>
//#include "misc/math.h"
#include <kprintf.h>


void k_main(void) 
{
    timer_init();
    //__asm__ volatile ("sti");
    k_clear_screen();
    kprintlogo(0,0);
    //k_sleep_ms(1000);
    //k_clear_screen();
    //k_donut();
}


void __stack_chk_fail(void) {
	kprintf("Stack check failed!",0,0);
	while (1);
}