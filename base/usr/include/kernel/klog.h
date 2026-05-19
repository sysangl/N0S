// klog.h
#ifndef KLOG_H
#define KLOG_H

unsigned int klog(const char *err);
unsigned int kwarn(const char *err);
unsigned int kerror(const char *err);
unsigned int ksuccess(const char *err);

#endif