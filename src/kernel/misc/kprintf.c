#include <kprintf.h>
#include <screen.h>

unsigned int current_line = 0;

void k_clear_screen()
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		vidmem[i+1]=WHITE;
		i+=2;
	};
	current_line=0;
}


static int sgr_to_vga_colour(int sgr)
{
	switch (sgr)
	{
	case 30: return BLACK;
	case 31: return RED;
	case 32: return	GREEN;
	case 33: return BROWN;
	case 34: return BLUE;
	case 35: return MAGENTA;
	case 36: return CYAN;
	case 37: return GRAY;
	case 90: return DARK_GRAY;
	case 91: return LIGHT_RED;
	case 92: return LIGHT_GREEN;
	case 93: return YELLOW;
	case 94: return LIGHT_BLUE;
	case 95: return LIGHT_MAGENTA;
	case 96: return LIGHT_CYAN;
	case 97: return WHITE;
	default: return WHITE;
	}
}

unsigned int kprintcolourlocationf(const char *message, unsigned int line, unsigned int col, int colour)
{
	if (message == (void*)0) return 0;
	if (current_line > 25) {
        current_line = 0;
        k_clear_screen();
    }
    char *vidmem = (char *) 0xb8000;
    unsigned int i = (line*80+col)*2;
	int colour_override = colour;
	
	while(*message!=0)
	{
		if(*message=='\033' && *(message+1)=='[')
		{
			message+=2;
			int codes[4];
			int num_codes=0;
			while (*message != 'm' && *message != '\0' && num_codes < 4)
			{
				int val = 0;
				while (*message >= '0' && *message <= '9') {
					val = val * 10 + (*message-'0');
					message++;
				}
				codes[num_codes++]=val;
				if(*message ==';') message++;
			}
			if(*message == 'm') message++;

			int fg=-1, bg=-1;
			for (int c=0; c<num_codes; c++){
				if (codes[c]==0){
					colour_override = colour;
				} else if (codes[c]==1)
				{} else if ((codes[c] >= 30 && codes[c] <=37) || (codes[c]>=90 && codes[c] <=97))
				{
					fg = sgr_to_vga_colour(codes[c]);
				} else if (codes[c]>=40 && codes[c] <=47)
				{
					bg = codes[c]-40;
				}
			}
			if (fg != -1 && bg != -1) {
				colour_override = FG_BG(fg, bg);
			} else if (fg != -1)
			{
				colour_override = fg;
			} else if (bg != -1)
			{
				colour_override = BG(bg);
			}
		} else if(*message=='\n')
		{
			line++;
			i=(line*80*2); 
			message++;
			current_line++;
		} else {
			vidmem[i] = *message;
			vidmem[i+1] =colour_override;
			i += 2;
			message++;
		}
	}
	current_line++;
	return(1);
}


unsigned int (kprintf)(struct kprintargs *args)
{
    if (args == (void*)0) return 0;
    if (args->message == (void*)0) return 0;
    return kprintcolourlocationf(args->message,args->line,args->col, args->colour);
}


unsigned int kprintlogo(unsigned int line, unsigned int col)
{
	return kprintf(.message="\033[35m                     ,,                                 \n`7MMF'   `7MF'     `7MM            .g8\"\"8q.    .M\"\"\"bgd \n  `MA     ,V         MM          .dP'    `YM. ,MI    \"Y \n   VM:   ,V ,6\"Yb.   MM  .gP\"Ya  dM'      `MM `MMb.     \n    MM.  M'8)   MM   MM ,M'   Yb MM        MM   `YMMNq. \n    `MM A'  ,pm9MM   MM 8M\"\"\"\"\"\" MM.      ,MP .     `MM \n     :MM;  8M   MM   MM YM.    , `Mb.    ,dP' Mb     dM \n      VF   `Moo9^Yo.JMML.`Mbmmd'   `\"bmmd\"'   P\"Ybmmd\"  ");
}
