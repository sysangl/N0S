#include <screen.h>
#include <timer.h>
#include <kprintf.h>
#include <itoa.h>
#include <kshell.h>
#include <klog.h>
#include <math.h>

void k_main(void) 
{
    char str[10];
    timer_init();
    //__asm__ volatile ("sti");
    k_clear_screen();
    kprintlogo(0,0);
    //int n = k_pow(5,2);
    kprintf(itoa(6213,str,2),10,0);
    kshell();
    klog("This is a log", str);
    kwarn("This is a warning", str);
    kerror("This is an error", str);
    //k_sleep_ms(1000);
    //k_clear_screen();
}


void __stack_chk_fail(void) {
	kprintf("Stack check failed!",0,0);
	while (1);
}