#include "screen.h"

/* k_clear_screen : clear the entire text screen */
void k_clear_screen()
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
};

/* k_printf : takes in the message and line # */
unsigned int k_printf(char *message, unsigned int line)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(line*80*2);

	while(*message!=0)
	{
		if(*message=='\n') // check for a new line
		{
			line++;
			i=(line*80*2);
			message++;
		} else {
			vidmem[i]=*message;
			message++;
			i++;
			vidmem[i]=WHITE_TXT;
			i++;
		};
	};

	return(1);
}

/* k_putchar : places a char at the given location */
unsigned int k_putchar(char c, unsigned int x, unsigned int y)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(y*80+x)*2;

	vidmem[i]=c;
	i++;
	vidmem[i]=WHITE_TXT;
	i++;


	return(1);
}

unsigned int k_printlogo(unsigned int line)
{
	k_printf(":::::::::::::::::::::::::::::::::\n:::    $$$$$$$$$$$    $$$$$$$$:::\n:::    $$$$$$$$$$    $$$$$$$$$:::\n:::    $$$$$$$$$    $$$$$$$$$$:::\n:::    $$$$$$$$    $$$$   $$$$:::\n:::    $$$$$$$    $$$$    $$$$:::\n:::    $$$$$$    $$$$     $$$$:::\n:::    $$$$$    $$$$$$$$$$$$$$:::\n:::    $$$$    $$$$$$$$$$$$$$$:::\n:::    $$$    $$$$        $$$$:::\n:::    $$    $$$$         $$$$:::\n:::         $$$$          $$$$:::\n:::        $$$$           $$$$:::\n:::       $$$$            $$$$:::\n:::::::::::::::::::::::::::::::::\n",line);
}
