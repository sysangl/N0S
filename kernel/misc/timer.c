#include <timer.h>
extern void irq0_stub();

#define PIT_FREQUENCY 1193182
#define TICKS_PER_MS  1          /* at 1000Hz */

unsigned int timer_ticks = 0;
/* write a byte to an I/O port */
void outb(unsigned short port, unsigned char value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}
void fpu_init()
{
    unsigned long cr0;
    __asm__ volatile ("mov %%cr0, %0" : "=r"(cr0));
    cr0 &= ~(1UL << 2);
    cr0 &= ~(1UL << 3);
    cr0 |=  (1UL << 1);
    __asm__ volatile ("mov %0, %%cr0" : : "r"(cr0));
    __asm__ volatile ("fninit");

    unsigned short cw = 0x037f;
    __asm__ volatile ("fldcw %0" : : "m"(cw));
}
void pic_remap()
{
    outb(0x20, 0x11); outb(0xA0, 0x11); /* init command */
    outb(0x21, 0x20); outb(0xA1, 0x28); /* vector offsets */
    outb(0x21, 0x04); outb(0xA1, 0x02); /* cascading */
    outb(0x21, 0x01); outb(0xA1, 0x01); /* 8086 mode */
    outb(0x21, 0x00); outb(0xA1, 0x00); /* unmask all */
}

struct idt_entry {
    unsigned short base_low;
    unsigned short selector;
    unsigned char  zero;
    unsigned char  flags;
    unsigned short base_high;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int   base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr   idtp;

void idt_set_gate(unsigned char num, unsigned int base)
{
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector  = 0x08;
    idt[num].zero      = 0;
    idt[num].flags     = 0x8E;
}

void idt_init()
{
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base  = (unsigned int) &idt;

    int i;
    for (i = 0; i < 256; i++)
        idt_set_gate(i, 0);

    idt_set_gate(0x20, (unsigned int) irq0_stub);  // real handler
    idt_set_gate(16,   (unsigned int) irq0_stub);

    __asm__ volatile ("lidt %0" : : "m"(idtp));
}


void pit_init(unsigned int frequency)
{
    unsigned int divisor = PIT_FREQUENCY / frequency;
    outb(0x43, 0x36);                    /* command: channel 0, square wave */
    outb(0x40, divisor & 0xFF);          /* low byte of divisor */
    outb(0x40, (divisor >> 8) & 0xFF);   /* high byte */
}

void irq0_handler()
{
    timer_ticks++;
    outb(0x20, 0x20);
}
void timer_init(void)
{
    fpu_init();

    pic_remap();
    idt_init();
    pit_init(1000);
}

void k_sleep_ms(unsigned int ms)
{
    unsigned int start = timer_ticks;
    while (timer_ticks - start < ms)
    {
        __asm__ volatile ("hlt");
    }
}
