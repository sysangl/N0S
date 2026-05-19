// kprintf.h
#ifndef KPRINTF_H
#define KPRINTF_H

#define BLACK 0x00
#define BLUE 0x01
#define GREEN 0x02
#define CYAN 0x03
#define RED 0x04
#define MAGENTA 0x05
#define BROWN 0x06
#define GRAY 0x07
#define DARK_GRAY 0x08
#define LIGHT_BLUE 0x09
#define LIGHT_GREEN 0x0A
#define LIGHT_CYAN 0x0B
#define LIGHT_RED 0x0C
#define LIGHT_MAGENTA 0x0D
#define YELLOW 0x0E
#define WHITE 0x0F
#define BG(bg_colour) (bg_colour*16)
#define FG_BG(fg, bg) (fg+bg*16)

extern unsigned int current_line;

struct kprintargs {
    const char *message;
    unsigned int line;
    unsigned int col;
    int colour;
};

unsigned int kprintlogo(unsigned int line, unsigned int col);
unsigned int (kprintf)(struct kprintargs *args);
void k_clear_screen();

#define kprintf(...) ({ \
    struct kprintargs _args = { \
        .message = "", \
        .line = current_line, \
        .col = 0, \
        .colour = WHITE, \
        __VA_ARGS__ \
    }; \
    (kprintf)(&_args); \
})

#endif