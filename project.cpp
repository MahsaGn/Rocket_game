#include<iostream>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_gfxPrimitives.h>
#include <string>
#include<vector>
using namespace std;
struct rckt
{
	int xp=225+10;
	int yp=700;
	int ymax=600;
	float vx=2;
	float vy=4;
	int health=3;
	int shotnum=1;
	SDL_Surface * surface;
};
struct oppRocket
{
	int xp;
	int yp;
	int ymax;
	float vx;
	float vy;
	int health;
	int state;
	int height;
	int width;
	SDL_Surface * surface;
};
struct gft
{
	int xp;
	int yp;
	int r;
	float vy;
	int state;
	int time;
	SDL_Surface * surface;
};
struct meteor
{
	int xp;
	int yp;
	int r;
	float vy;
	SDL_Surface * surface;
};
struct coin
{
	int xp;
	int yp;
	int r;
	float vx;
	float vy;
	SDL_Surface * surface;
};
struct ammo
{
	int xp;
	int yp;
	int r;
	float vy;
	SDL_Surface * surface;
};
SDL_Surface * load_image (std::string file);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
void gift_motion (gft * gift ,int n,SDL_Surface * screen);
void gifte(gft *gift,int n, SDL_Surface *screen);
int main()
{
	SDL_Event event;	
	SDL_Surface * screen=NULL;
	int bgX = 0, bgy = 0;
	screen=SDL_SetVideoMode( 450, 700, 32, 0 );
	SDL_Surface * picture;
	gft gift[5]		;
	for(int i=0;i<5;i++)
	{
		gift[i].yp=0;
		gift[i].xp=10+(10*i);
		gift[i].vy=i+1;
		gift[i].state=2;
		gift[i].surface=load_image("gift0.png");
	}
	picture=load_image("stars1.jpg");
	vector <ammo> shot;
	rckt rocket;
	rocket.surface=;
	while(1)
	{
		bgy+=2;
		if(bgy>=picture->h)
		{
			bgy=0;
		}
	  	apply_surface( bgX, bgy, picture, screen ); 
      	apply_surface( bgX , bgy-picture->h, picture, screen );
    	gifte(&gift[0],5, screen);
		SDL_Flip(screen);
		SDL_Delay(20);
	}
	return 0;
}

SDL_Surface * load_image (std::string file)
{

	SDL_Surface * image=NULL;
	image=IMG_Load( file.c_str() );
	return image;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}
//void gift_motion (gft * gift,int n,SDL_Surface * screen )
void gift(gft * gift,int n,SDL_Surface * screen )
{
	for(int i=0 ; i<n ; i++)
	{
		if(gift[i].state == 2)
		{
			gift[i].yp +=gift[i].vy;
			if(gift[i].yp >= 700)
			{
				gift[i].state = 0;
				return;
			}
			apply_surface(gift[i].xp , gift[i].yp , gift[i].surface,screen);	
		}
		else 
		{
			if(gift[i].state==1)
			{
				gift[i].time--;
				if(gift[i].time==0)
					gift[i].state=0;
			}
			else
			{
				if(rand()%10>6)
				{
					gift[i].xp=rand()%450;
					gift[i].yp=0;
					gift[i].state=2;
					gift[i].vy=rand()%3+1;

				} 
			}

		}
	}
	
}