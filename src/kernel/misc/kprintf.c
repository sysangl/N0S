#include <kprintf.h>

/* kprintf : takes in the message and line # */
unsigned int kprintcolourf(const char *message, unsigned int line, unsigned int col, int colour)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(line*80+col)*2;

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
			vidmem[i]=colour;
			i++;
		};
	};
	return(1);
}
unsigned int kprintf(const char *message, unsigned int line, unsigned int col)
{
	return kprintcolourf(message,line,col,WHITE);
}


unsigned int kprintlogo(unsigned int line, unsigned int col)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	const char *message = "                     ,,                                 \n`7MMF'   `7MF'     `7MM            .g8\"\"8q.    .M\"\"\"bgd \n  `MA     ,V         MM          .dP'    `YM. ,MI    \"Y \n   VM:   ,V ,6\"Yb.   MM  .gP\"Ya  dM'      `MM `MMb.     \n    MM.  M'8)   MM   MM ,M'   Yb MM        MM   `YMMNq. \n    `MM A'  ,pm9MM   MM 8M\"\"\"\"\"\" MM.      ,MP .     `MM \n     :MM;  8M   MM   MM YM.    , `Mb.    ,dP' Mb     dM \n      VF   `Moo9^Yo.JMML.`Mbmmd'   `\"bmmd\"'   P\"Ybmmd\"  ";

	i=(line*80+col)*2;

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
			vidmem[i]=MAGENTA;
			i++;
		};
	};
	return(1);

}
