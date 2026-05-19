#include <klog.h>
#include <kprintf.h>
#include <string.h>

unsigned int klog(const char *err)
{
	char buf[50];
	kstrcpy(buf, "[ LOG ] ");
	kstrcat(buf, err);
	kprintf(.message=buf);
	return 1;
}
unsigned int kwarn(const char *err)
{
	char buf[50];
	kstrcpy(buf, "[ \033[93mWARN\033[0m ] ");
	kstrcat(buf, err);
	kprintf(.message=buf);
	return 1;
}

unsigned int kerror(const char *err)
{
	char buf[50];
	kstrcpy(buf, "[ \033[91mERROR\033[0m ] ");
	kstrcat(buf, err);
	kprintf(.message=buf);
	return 1;
}
unsigned int ksuccess(const char *err)
{
	char buf[50];
	kstrcpy(buf, "[ \033[92mSUCCESS\033[0m ] ");
	kstrcat(buf, err);
	kprintf(.message=buf);
	return 1;
}