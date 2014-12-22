#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <stdbool.h>

typedef struct {char red;char green;char blue;}rgbcolor;

int main(int argc, char *argv[]){
	
	
	rgbcolor palColors[256];
	
	int scale;
	if (argc>2)//DRAWING SCALE
	{scale=strtol(argv[2],NULL,10);}
	else
	{scale=16;}
	
	FILE *palfile = fopen( argv[1], "r" );//READ FILE
	if ( palfile == 0 )
	{
			printf("Error: no readable file!\n");
	}
	else 
	{
		char red,green,blue;
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
		bool Run=true;
		while (Run)
		{
			while (SDL_PollEvent(&Events))
			{
				if (Events.type == SDL_QUIT)
					Run = false;
			}
			SDL_Init( SDL_INIT_EVERYTHING );
			SDL_Surface* screen = NULL;
			screen = SDL_SetVideoMode( 16*scale, 16*scale, 32, SDL_SWSURFACE );
			SDL_WM_SetCaption(argv[1],0);
			int x,y,z=0;
			for (y=0;y<16;y+=1)
			{
				for (x=0;x<16;x+=1)
				{
					if (argc>3)
					{printf("X:%d-%d Y:%d-%d RGB:%d %d %d\n",x*scale,(x+1)*scale,y*scale,(y+1)*scale,2*(int)palColors[z].red,2*(int)palColors[z].green,2*(int)palColors[z].blue);}
						z+=1;
						SDL_Rect bigpix={x*scale,y*scale,(x+1)*scale,(y+1)*scale};
						SDL_FillRect(screen,&bigpix, SDL_MapRGB(screen->format,(int)palColors[z].red*2,(int)palColors[z].green*2,(int)palColors[z].blue*2));
				}
			}
			SDL_Flip(screen);
			SDL_Delay(1000);
		}
	}
	return 1;
}
