#include <klog.h>
#include <kprintf.h>
#include <string.h>

unsigned int klog(const char *err, char *outputBuffer)
{
	kprintf("[ LOG ] ",12,0);
	kprintf(err, 12,8);
	return 1;
}
unsigned int kwarn(const char *err, char *outputBuffer)
{
	kprintf("[      ] ",13,0);
	kprintcolourf("WARN",13,2, YELLOW);
	kprintf(err, 13,9);
	return 1;
}

unsigned int kerror(const char *err, char *outputBuffer)
{
	kprintf("[       ] ",14,0);
	kprintcolourf("ERROR",14,2, LIGHT_RED);
	kprintf(err, 14,10);
	return 1;
}
unsigned int ksuccess(const char *err, char *outputBuffer)
{
	kprintf("[         ] ",15,0);
	kprintcolourf("SUCCESS",15,2, LIGHT_GREEN);
	kprintf(err, 15,12);
	return 1;
}