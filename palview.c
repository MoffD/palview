/*
    Palette file viewer
    Copyright (C) 2015  Daniel L

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL/SDL.h>

typedef struct {unsigned char red;unsigned char green;unsigned char blue;}rgbcolor;

int main(int argc, char *argv[]){
	char* usage="Usage: palview [OPTIONS] [FILE]\n\t-s [SCALE]\t:Pixel size for each color (Default 16)\n\t-d\t:Turn debugging output on\n\t-h\t:Display this help message\nEx:\tpalview -ds 32 ./myfile.pal\n";
	if (argc==1){printf(usage);exit(0);}
	int scale=16,i,j,debug=0,dbgout=0;
	
	for (i=1;i<argc;i++){//argument handler
		if (argv[i][0]=='-'){
			for (j=1;j<strlen(argv[i]);j++){
				switch (argv[i][j])
				{
				case 's':
					if (i<argc-1){
					scale=strtol(argv[i+1],NULL,10);
					printf("scale set to %d\n",scale);
					fflush(stdout);
					}
				break;
				case 'd':
					debug=1;
					printf("Debugging Enabled\n");
					fflush(stdout);
				break;
				case 'h':
					printf(usage);
					exit(0);
				break;
				default:
					printf("Ignoring unknown option %c, use -h for a list of options\n",argv[i][j]);
				break;
				}
			}
		}
	}
	
	rgbcolor palColors[256];
	
	FILE *palfile = fopen( argv[argc-1], "r" );//READ FILE
	if ( palfile == 0 )
	{
			printf("Error: no readable file!\n");
	}
	else 
	{
		unsigned char red,green,blue;
		int i=0;
		while  (!feof(palfile))
		{
			red=fgetc(palfile);
			green=fgetc(palfile);
			blue=fgetc(palfile);
			if (red!=-1)
			{
			palColors[i].red=red;
			palColors[i].green=green;
			palColors[i].blue=blue;
			i+=1;
			}
		}
		SDL_Event Events;
		int Run=1;
		while (Run==1)
		{
			while (SDL_PollEvent(&Events))
			{
				if (Events.type == SDL_QUIT)
					Run = 0;
			}
			SDL_Init( SDL_INIT_EVERYTHING );
			SDL_Surface* screen = NULL;
			screen = SDL_SetVideoMode( 16*scale, 16*scale, 32, SDL_SWSURFACE );
			SDL_WM_SetCaption(argv[argc-1],0);
			int x,y,z=0;
			for (y=0;y<16;y+=1)
			{
				for (x=0;x<16;x+=1)
				{
					
					if (debug==1 && dbgout==0)//debug prints out current palette file colors
						{printf("X:%d-%d Y:%d-%d RGB:%d %d %d\n",
							x*scale,
							(x+1)*scale,
							y*scale,
							(y+1)*scale,
							palColors[z].red,
							palColors[z].green,
							palColors[z].blue);
							fflush(stdout);
						}
					SDL_Rect bigpix={x*scale,y*scale,(x+1)*scale,(y+1)*scale};
					SDL_FillRect(screen,&bigpix, SDL_MapRGB(screen->format,
					palColors[z].red,
					palColors[z].green,
					palColors[z].blue));
					z+=1;
				}
			}
			dbgout=1;
			SDL_Flip(screen);
			SDL_Delay(100);
		}
	}
	return 1;
}
