#define WHITE_TXT 0x07 /* light gray on black text */

void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line);
unsigned int k_printlogo(unsigned int line);

void k_main() 
{
	k_clear_screen();
	k_printlogo(0);
	//k_printf("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31", 0);
};

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

unsigned int k_printlogo(unsigned int line)
{
	k_printf(":::::::::::::::::::::::::::::::::\n:::    $$$$$$$$$$$    $$$$$$$$:::\n:::    $$$$$$$$$$    $$$$$$$$$:::\n:::    $$$$$$$$$    $$$$$$$$$$:::\n:::    $$$$$$$$    $$$$   $$$$:::\n:::    $$$$$$$    $$$$    $$$$:::\n:::    $$$$$$    $$$$     $$$$:::\n:::    $$$$$    $$$$$$$$$$$$$$:::\n:::    $$$$    $$$$$$$$$$$$$$$:::\n:::    $$$    $$$$        $$$$:::\n:::    $$    $$$$         $$$$:::\n:::         $$$$          $$$$:::\n:::        $$$$           $$$$:::\n:::       $$$$            $$$$:::\n:::::::::::::::::::::::::::::::::\n",line);
}