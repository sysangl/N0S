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
    __asm__ volatile ("sti");
    k_clear_screen();
    kprintlogo(0,0);
    k_sleep_ms(1000);
    kshell();
    k_sleep_ms(1000);
    klog("This is a log");
    kwarn("This is a warning");
    kerror("This is an error");
    ksuccess("This is a success");
    k_sleep_ms(1000);
    k_clear_screen();
    int i =0;
    while (i<50){
        klog(itoa(i,str,10));
        k_sleep_ms(100);
        i++;
    }
}


void __stack_chk_fail(void) {
    char str[10];
	kerror("Stack check failed!");
	while (1);
}