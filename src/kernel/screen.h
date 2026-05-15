// screen.h
#ifndef SCREEN_H
#define SCREEN_H
#define WHITE_TXT 0x07;

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line, unsigned int col);
unsigned int k_putchar(char c, unsigned int x, unsigned int y);
unsigned int k_printlogo(unsigned int line, unsigned int col);

#endif