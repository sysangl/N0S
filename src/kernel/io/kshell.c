#include <kprintf.h>
#include <kshell.h>
#include <io.h>

void print_prompt()
{
    kprintf("$ ValeOS > ",11,0);
}

unsigned int kshell()
{
    while (1)
    {
        print_prompt();
        read_input();
        break;
    }

    return 1;
}