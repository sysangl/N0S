// klog.h
#ifndef KLOG_H
#define KLOG_H

unsigned int klog(const char *err, char *outputBuffer);
unsigned int kwarn(const char *err, char *outputBuffer);
unsigned int kerror(const char *err, char *outputBuffer);

#endif