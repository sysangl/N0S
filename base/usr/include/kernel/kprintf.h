// kprintf.h
#ifndef KPRINTF_H
#define KPRINTF_H
#define WHITE_TXT 0x07;
#define BLUE_TXT 0x09;

unsigned int kprintf(const char *message, unsigned int line, unsigned int col);
unsigned int kputchar(char c, unsigned int x, unsigned int y);
unsigned int kprintlogo(unsigned int line, unsigned int col);

#endif