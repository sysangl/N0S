#include <screen.h>
#include <timer.h>
#include <kprintf.h>
#include <itoa.h>
#include <kshell.h>

void k_main(void) 
{
    char str[10];
    timer_init();
    //__asm__ volatile ("sti");
    k_clear_screen();
    kprintlogo(0,0);
    kprintf(itoa(10,str,2),10,0);
    kshell();
    //k_sleep_ms(1000);
    //k_clear_screen();
}


void __stack_chk_fail(void) {
	kprintf("Stack check failed!",0,0);
	while (1);
}