#include<iostream>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_gfxPrimitives.h>
#include <string>
#include<vector>
#include "sstream"
#include<cstdlib>
#include<fstream>
using namespace std;
struct rckt
{
	int xp=225+10;
	int yp=680;
	int ymax=550;
	float vx=6;
	float vy=-6;
	int health=3;
	int shotnum=10;
	SDL_Surface * surface;
};
struct oppRckt
{
	int xp=255+12;
	int yp=0;
	int ymin=50;
	float vx=4;
	float vy=4;
	int health=3;
	int state=0;
	int height=24;
	int width=120;
	SDL_Surface * surface;
};
struct gft
{
	int xp;
	int yp=0;
	int r=10;
	float vy;
	int state=0;
	int time=600;
	SDL_Surface * surface;
};
struct meteor
{
	int xp;
	int yp;
	int r;
	int kind;
	float vy;
	SDL_Surface * surface;
};
struct cn
{
	int xp;
	int yp=0;
	int r=5;
	int valu=1;
	float vx=0;
	int vy=5	;
	int zarib=1;
	SDL_Surface * surface;
};
struct ammo
{
	int xp;
	int yp;
	int r=100;
	int state;
	float vy;
	SDL_Surface * surface;
};
SDL_Surface * load_image (std::string file);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
//void gift_motion (gft * gift ,int n,SDL_Surface * screen,);
void Gift(gft *gift,int n, SDL_Surface *screen,int roundNum,int level);
bool Rocket(rckt &rocket,vector <ammo> &shot,SDL_Event &event,SDL_Surface * screen,int level);//menu in mixed with this
void OppRocket(oppRckt &oppRocket,vector <ammo> &shot, SDL_Surface *screen,int level);
bool Shot(vector <ammo>& shot,SDL_Surface *screen,oppRckt & oppRocket,gft gift2);//if true the opp is killed
void Meteor(vector <meteor> & meteorite,SDL_Surface *screen,int roundNum,int level);
void Coin(vector <cn> &coin,SDL_Surface * screen,gft gift5,gft gift3,int xrocket,int yrocket,int roundNum,int level);
bool colliosion (rckt &rocket, gft *gift,std::vector<meteor> &meteorite,std::vector<cn> &coin,
	std::vector<ammo> &shot,int * score,SDL_Surface * screen,bool* protecter);
void set_text( int x, int y, SDL_Surface* source, SDL_Surface* destination );
void write_menu_score (SDL_Surface *screen,int score);
void write_menu_health (SDL_Surface *screen,int score);
void write_menu_shot(SDL_Surface *screen,int score);
void write_menu_level(SDL_Surface *screen,int score);
void write_menu_OPP_HEALTH(SDL_Surface *screen,int score);
int main()
{
	int bgX = 0, bgy = 0;
	int roundNum=0;
	int score;
	int BGvelocity=4;
	int level=1;
	int coinNum=0;
	bool protecter=false;
	bool checkcolision=true;
	SDL_Event event;	
	SDL_Surface * screen=NULL;
	SDL_Surface * picture;
	gft gift[5];
	rckt rocket;
	oppRckt oppRocket;
	vector <ammo> shot=std::vector<ammo>(0);
	vector <meteor> meteorite;
	vector <cn> coin;
	screen=SDL_SetVideoMode( 650, 700, 32, 0 );
	thickLineRGBA(screen,451,0,451,700,3,200,0,200,100);
	oppRocket.surface=load_image("spacecraft.png");
	rocket.surface=load_image("rocket-r.png");
	picture=load_image("stars1.jpg");
	bool meniu=true;
	bool checkLevel=false;
	for(int i=0;i<5;i++)
	{
		gift[i].xp=10+(10*i);
		gift[i].vy=i+1;
	}
	gift[0].surface=load_image("gift0.png");//x2
	gift[1].surface=load_image("gift1.png");//protecter
	gift[2].surface=load_image("gift2.png");//speed plus
	gift[3].surface=load_image("gift3.png");//magnet
	gift[4].surface=load_image("gift4.png");//slwer
	gift[5].surface=load_image("gift5.png");//more coin
	gift[6].surface=load_image("gift6.png");//ammo
	cout<<"A\n";
	do

	{
	// write_menu_score(screen,score);
		// cout<<"1\n";
		// write_menu_health(screen,rocket.health);
		// cout<<"2\n";
		//write_menu_level(screen,level);
		// cout<<"3\n";
		int sh;
		// cout<<"4\n";
		sh=0;
		if(shot.size()!=0)
			for(int j=0;j<shot.size();j++)
			{
				// cout<<"5\n";
				if(shot[j].vy<0)
				{
					// cout<<"6\n";
					sh++;
				}
				// cout<<"7\n";
			}
		// cout<<"8\n";
		write_menu_shot(screen,sh);
		// cout<<"9\n";
		roundNum++;
		// cout<<"10\n";
		bgy+=BGvelocity;
		// cout<<"10\n";
		if(bgy>=picture->h)
		{
			// cout<<"11\n";
			bgy=0;
		}
		cout<<"12\n";
	  	apply_surface( bgX, bgy, picture, screen ); 
      	apply_surface( bgX , bgy-picture->h, picture, screen );
      	cout<<"13\n";
    	Gift(&gift[0],7, screen,roundNum,level);
    	cout<<"14\n";
    	meniu=Rocket(rocket,shot,event,screen,level);
    	cout<<"15\n";
    	Meteor(meteorite,screen,roundNum,level);
    	cout<<"16\n";
    	Coin(coin,screen,gift[5],gift[3],rocket.xp,rocket.yp,roundNum,level);
    	cout<<"17\n";
    	score=(int)(roundNum/20)+coinNum;
    	cout<<"18\n";
		checkcolision=colliosion (rocket,&gift[0],meteorite,coin,shot,&score, screen,&protecter);
		cout<<"p\n";
    	if((score%100==0 && score!=0) || oppRocket.state==1)
		{
			cout<<"w\n";
    		OppRocket(oppRocket,shot,screen,level);
		}
		// cout<<"G\n";
    	checkLevel=Shot(shot,screen,oppRocket,gift[2]);
    	// cout<<"h\n";
		if(checkLevel==true)// b marhale bad raftim pas soraat ha bishtar mishe
			level++;
		//cout<<score<<endl<<level<<endl<<endl;
		
		SDL_Flip(screen);
		SDL_Delay(10);
		boxRGBA(screen,530,100,700	, 600 ,0,0,0,255);
		// cout<<"e\n";
	}while(meniu==true && checkcolision==false);
	  SDL_Delay(1000);
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
void Gift(gft * gift,int n,SDL_Surface * screen ,int roundNum ,int level)//1.come more distanced    2.timi k assar mikonn kam mishe
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

		}
	}	
			
			
	if(rand()%(100*level+50)==4)
	{
		int i=1;
		
		 do
		{
		//	cout<<"do while\n";
			i=rand()%n;
		}while(gift[i].state!=0);

		//cout<<"after\n";
		gift[i].time=600 ;
		gift[i].xp=rand()%(450-2*gift[i].r);
		gift[i].yp=0;
		gift[i].state=2;
		gift[i].vy=rand()%3+3;

	} 
			
}
bool Rocket(rckt &rocket,vector <ammo> &shot,SDL_Event &event,SDL_Surface * screen,int level) //1.velocity inhanced
{ 
    if(rocket.vy!=0)//in tike baraye avale bazie k safine amoodi harekat mikone 
    { 
    	rocket.yp+=rocket.vy;
    	if(rocket.yp<=rocket.ymax) 
       		rocket.vy=0; 
    } 
    else//harekate ofoghi 
    { 
  		Uint8 *keystates = SDL_GetKeyState( NULL );
    	 if( SDL_PollEvent( &event ) )//do halat ro barresi mikone k :
   		{ 
        	if( event.type == SDL_KEYDOWN ) //1.jahate safine avaz beshe
        	{ 
            	if( keystates[ SDLK_SPACE ]) 
    			{ 
                	rocket.vx*= (-1); 
          			if(rocket.vx>0)
          				rocket.surface=load_image("rocket-r.png");
      				else
      					rocket.surface=load_image("rocket-l.png");

        		} 
        		else if(keystates[ SDLK_UP ] && rocket.shotnum>0)//2.tir shelik kone
        		{ 
        			
         			rocket.shotnum--;
        			ammo sht; 
        			sht.xp=rocket.xp; 
        			sht.yp=rocket.yp; 
        			sht.vy=-8;
        			sht.state=1;
        			sht.surface=load_image("shot-up.png"); 
        			shot.push_back(sht); 
       			}
       			else if( event.key.keysym.sym==SDLK_p) 
    			{
    				int check=false;
    				do
    				{
    				SDL_Delay(500);
    					if(SDL_PollEvent( &event ) && event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_s)
    						check=true;
    				}while( check==false);
    			}
    			else if(event.key.keysym.sym==SDLK_q)
    				return false;
        	} 

    	}
    	if(rocket.vx>0)
    		rocket.xp+=(rocket.vx+level);
    	else
    		rocket.xp+=(rocket.vx-level);
    }  
    /*if(rocket_strike()==true) 
    { 
       rocket.health--;
    }*/ 
    apply_surface( rocket.xp, rocket.yp, rocket.surface, screen ); 
    return true; 
} 
void OppRocket(oppRckt &oppRocket,vector <ammo> &shot, SDL_Surface *screen,int level)//1. healt will increas 2.shots through in shorter time
{
	if(oppRocket.state==0)
	{
		{
			oppRocket.state=1;
			oppRocket.vy=2;
			oppRocket.health=3+level;
		}
	}
	else
	{
		// cout<<"A\n";
		//write_menu_OPP_HEALTH(screen,oppRocket.health);
	// cout<<"BB\n";
		if(oppRocket.vy!=0)//hengame vared shodan b safhe
		{
		// cout<<"CC\n";
			oppRocket.yp+=oppRocket.vy	;
			// cout<<"D\n";
			if(oppRocket.yp>oppRocket.ymin)
				oppRocket.vy=0;
			// cout<<"E\n";
		}
		else//bad az mostaghar shodan
		{
			if(oppRocket.xp<=0 || oppRocket.xp>=(450-oppRocket.width))	
			{
				oppRocket.vx*=-1;
			}
			oppRocket.xp+=oppRocket.vx;
		}
		if(rand()%(300-20*level)==4)
		{
			ammo sht;
			sht.xp=oppRocket.xp-oppRocket.vx+(oppRocket.width/2)-2;
			sht.yp=oppRocket.yp+oppRocket.height;
			sht.vy=8;
			sht.state=0;
			sht.surface=load_image("shot-down.png");
			shot.push_back(sht);
		}
	}
	apply_surface(oppRocket.xp,oppRocket.yp,oppRocket.surface,screen);
}
bool Shot(vector <ammo>& shot,SDL_Surface *screen,oppRckt &oppRocket,gft gift2) 	
{
   	if(shot.size()!=0)
		for(int i=0;i<shot.size();i++)
		{	
			if(gift2.state==0)
				shot[i].vy=-8;
			shot[i].yp+=shot[i].vy;
			apply_surface(shot[i].xp,shot[i].yp,shot[i].surface,screen);
			if((shot[i].vy>0 && shot[i].yp>=700-40) || (shot[i].vy<0 && shot[i].yp<=0))
				shot.erase(shot.begin()+i);
			if(shot[i].vy<0)
			{
				if(oppRocket.state==1 && shot[i].yp<=oppRocket.ymin && shot[i].xp+2 >oppRocket.xp 
					&& shot[i].xp+2<oppRocket.xp+oppRocket.width)
				{
					shot.erase(shot.begin()+i);
					oppRocket.health--;
					if(oppRocket.health==0)
					{
						oppRocket.state=0;
						return true;

					}
				}
			}
			else
				if(shot[i].yp>=700)
					shot.erase(shot.begin()+i);
		}
		return false;
}
void Meteor(vector <meteor> & meteorite,SDL_Surface *screen,int roundNum,int level)//1.come down more
{
	if(roundNum%(60-(int)(roundNum/1500))==0 && rand()%2==0)
	{
		meteor mtr;
		mtr.r=40;
		mtr.xp=rand()%(450-2*mtr.r);
		mtr.yp=0;
		mtr.vy=8;
		mtr.surface=load_image("meteorite-s.png");
		mtr.kind=1;
		meteorite.push_back(mtr);
	}
	if((roundNum%(60-(int)(roundNum/1500))==0 && rand()%2==0) || meteorite.size()==0)
	{
		meteor mtr;
		mtr.r=50;
		mtr.xp=rand()%(450-2*mtr.r);
		mtr.yp=0;
		mtr.vy=5;
		mtr.kind=2;
		mtr.surface=load_image("meteorite-b.png");
		meteorite.push_back(mtr);
	}
	if(meteorite.size()!=0)
	{
		for(int i=0;i<meteorite.size();i++)
		{
			meteorite[i].yp+=meteorite[i].vy;
			apply_surface(meteorite[i].xp,meteorite[i].yp,meteorite[i].surface,screen);
			if(meteorite[i].yp>=700)
				meteorite.erase(meteorite.begin()+i);
		}
	}
}
void Coin(vector <cn> &coin,SDL_Surface * screen,gft gift5,gft gift3,int xrocket,int yrocket,int roundNum,int level)//Done
{
	int zarib =1;
	if(gift5.time!=0)
		zarib=3;
	if(rand()%(int)(200/zarib)==4 || coin.size()==0)
	{
		int center=rand()%390+30;
		cn con;
		con.surface=load_image("coin.png");
		if(rand()%2==0)
		{
			con.xp=center-20;
			con.yp=-20;
			coin.push_back(con);
			con.xp=center+20;
			con.yp=-20;
			coin.push_back(con);
			con.xp=center+20;
			con.yp=20;
			coin.push_back(con);
			con.xp=center-20;
			con.yp=20;
			coin.push_back(con);
			//SDL_Delay(5000);
		}
		else
		{
			con.xp=center;
			con.yp=-30;
			coin.push_back(con);
			con.xp=center;
			con.yp=30;
			coin.push_back(con);
			con.xp=center+20;
			con.yp=0;
			coin.push_back(con);
			con.xp=center-20;
			con.yp=0;
			coin.push_back(con);

		}
	}
	if(coin.size()!=0)
	{
		for(int i=0;i<coin.size();i++)
		{
			if(gift3.state==0)
				coin[i].valu=1;
			coin[i].xp+=coin[i].vx; 
			coin[i].yp+=coin[i].vy;
			apply_surface(coin[i].xp,coin[i].yp,coin[i].surface,screen);
			if(coin[i].yp==700)
			{
				coin.erase(coin.begin()+i);
			}
		}
	}
}
bool colliosion (rckt &rocket, gft *gift,std::vector<meteor> &meteorite,std::vector<cn> &coin,std::vector<ammo> &shot
	,int * score,SDL_Surface * screen,bool * protecter)
{
	int x,y,r;
	int Xbcircle,Ybcircle,Xscircle,Yscircle;
	const int Rbcircle=23;
	const int Rscircle=16;
	if(rocket.vx > 0)
	{
		Xbcircle=rocket.xp+20;
		Ybcircle=rocket.yp+60;
		Xscircle=rocket.xp+25;
		Yscircle=rocket.yp+17;	
	}
	else
	{
		Xbcircle=rocket.xp+20;
		Ybcircle=rocket.yp+58;
		Xscircle=rocket.xp+14;
		Yscircle=rocket.yp+15;
	}
	
	r=30.30/2;//gift
	for(int i=0 ; i<6 ; i++)
	{	
		if(gift[i].state == 2)
		{
			x=gift[i].xp+r;
			y=gift[i].yp+r;
		
			if(sqrt(pow((Xscircle-x),2) + pow((Yscircle-y),2)) <= Rscircle+r
			 || sqrt(pow((Xbcircle-x),2) + pow((Ybcircle-y),2)) <= Rbcircle+r)
			{
				gift[i].state=1;
				switch (i)
				{
					case 0:
						if(coin.size()!=0)
							for (int j = 0; j < coin.size(); j++)
							{
								coin[j].valu=2;
							}
						break;
					case 1:
						*protecter=true;
						break;
					case 2:
						if(shot.size()!=0)
							for (int j = 0; j < shot.size(); j++)
							{
								if(shot[j].vy<=0)
									shot[j].vy=-12;
							}
						break;	
					case 4:
						if(rocket.vx>0)
							rocket.vx=4;
						else
							rocket.vx=-4;
						break;
					
				}	
					
				
			//	cout<<"distance....."<<sqrt(pow((Xscircle-x),2) + pow((Yscircle-y),2))<<"...............r ="
			//	<<Rscircle+r<<"\n";
			//	cout<<"distance....."<<sqrt(pow((Xbcircle-x),2) + pow((Ybcircle-y),2))<<"...............r ="
			//	<<Rbcircle+r<<"\n";
			//	cout<<"Rbcircle....."<<Rbcircle<<endl;
			//	cout<<"tessssssssssssssssssssss\n";
			//	SDL_Delay(5000);
			}
		}
		else if(i==4 && gift[i].state==0)
		{
			if(rocket.vx>0)
				rocket.vx=6;
			else
				rocket.vx=-6;
		}
	}
	r=20.20/2;//coin
	int distancecoin=0;
	for(int i=0 ; i<coin.size() ; i++)
	{
		x=coin[i].xp+r;
		y=coin[i].yp+r;
	if(gift[3].state==1)
	{
		distancecoin=100;
		if(sqrt(pow((Xscircle-x),2) + pow((Yscircle-y),2)) <= Rscircle+r+distancecoin
			 || sqrt(pow((Xbcircle-x),2) + pow((Ybcircle-y),2)) <= Rbcircle+r+distancecoin)
		{
			if(0<rocket.yp-y)
				coin[i].vy=15;
			else
				coin[i].vy=-15;
			coin[i].vx=coin[i].vy*(rocket.xp-x)/(float)(rocket.yp-y);
		}
	}
		if(sqrt(pow((Xscircle-x),2) + pow((Yscircle-y),2)) <= Rscircle+r
			 || sqrt(pow((Xbcircle-x),2) + pow((Ybcircle-y),2)) <= Rbcircle+r)
		{
			(*score)+=coin[i].valu;
			coin.erase(coin.begin()+i);
			//cout<<"tessssssssssssssssssssss\n";
			//SDL_Delay(1000);
		}

	}
	//meteor
	for(int i=0 ; i<meteorite.size() ; i++)
	{
		r=meteorite[i].r-4;
		if(meteorite[i].kind ==1)
		{
			x=meteorite[i].xp+38;
			y=meteorite[i].yp+82;
		}
		else
		{
			x=meteorite[i].xp+51;
			y=meteorite[i].yp+47;

		}
		if(sqrt(pow((Xscircle-x),2) + pow((Yscircle-y),2)) <= Rscircle+r
			 || sqrt(pow((Xbcircle-x),2) + pow((Ybcircle-y),2)) <= Rbcircle+r)
		{
			if(*protecter!=true)
			{
				//return true;
			}
		}
	}
	//edge
	if(rocket.xp >= 411 || rocket.xp<0)
		return true;
	//tir
	for(int i=0 ; i<shot.size() ; i++)
	{
		if(shot[i].state==0)
		{
			SDL_Rect DShot;
			DShot.w=7;
			DShot.h=56;
			bool BCircle,SCircle;
			//for(int i=0 ; i<shot.size() ; i++)
			{
				bool BCircle=false,SCircle=false;
				DShot.x=shot[i].xp;
				DShot.y=shot[i].yp;
				int cx,cy;
				if(Xbcircle < DShot.x)
					cx=DShot.x;
				else if (Xbcircle >DShot.x +DShot.w)
					cx=DShot.x +DShot.w;
				else
					cx=Xbcircle;

				if(Ybcircle < DShot.y)
					cy=DShot.y;
				else if (Ybcircle >DShot.y +DShot.h)
					cy=DShot.y +DShot.h;
				else
					cy=Ybcircle;
				if(sqrt(pow((Xbcircle-cx),2) + pow((Ybcircle-cy),2)) < Rbcircle)
					BCircle=true;
		////////////////////////////////////////////////////////////////////////////smalller circle
				if(Xscircle < DShot.x)
					cx=DShot.x;
				else if (Xscircle >DShot.x +DShot.w)
					cx=DShot.x +DShot.w;
				else
					cx=Xscircle;

				if(Yscircle < DShot.y)
					cy=DShot.y;
				else if (Yscircle >DShot.y +DShot.h)
					cy=DShot.y +DShot.h;
				else
					cy=Yscircle;
				if(sqrt(pow((Xscircle-cx),2) + pow((Yscircle-cy),2)) < Rbcircle)
					SCircle=true;
				if(SCircle==true ||BCircle==true)
				{

					shot.erase(shot.begin()+i);
					rocket.health--;
				}	
			}
		}
	}
	
	return false;
}
void set_text( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}
void write_menu_score (SDL_Surface *screen,int score)
{
	TTF_Init();
	TTF_Font* font;
	font = TTF_OpenFont("ARIAL.ttf",20);
	SDL_Surface* text;
	SDL_Color text_color={100,0,200};
	stringstream score2;
    score2 <<" SCORE : "<<score;
	text = TTF_RenderText_Solid(font,score2.str().c_str(), text_color);
	set_text(460,100,text,screen);	
	SDL_Flip(screen);

}
void write_menu_health (SDL_Surface *screen,int score)
{
	TTF_Init();
	TTF_Font* font;
	font = TTF_OpenFont("ARIAL.ttf",20);
	SDL_Surface* text;
	SDL_Color text_color={100,0,200};
	stringstream score2;
    score2 <<" HEALTH : "<<score;
	text = TTF_RenderText_Solid(font,score2.str().c_str(), text_color);
	set_text(460,150,text,screen);	
	SDL_Flip(screen);	
}
void write_menu_shot (SDL_Surface *screen,int score)
{
	TTF_Init();
	// cout<<"1.1\n";
	TTF_Font* font;
	// cout<<"1.2\n";
	font = TTF_OpenFont("ARIAL.ttf",20);
	// cout<<"1.3\n";
	SDL_Surface* text;
	// cout<<"1.4\n";
	SDL_Color text_color={100,0,200};
	// cout<<"1.5\n";
	stringstream score2;
	// cout<<"1.6\n";
    score2 <<" SHOT : "<<score;
    // cout<<"1.7\n";
	text = TTF_RenderText_Solid(font,"hi", text_color);
	cout<<score2.str().c_str();
	// cout<<"1.8\n";
	set_text(460,200,text,screen);	
	// cout<<"1.9\n";
	SDL_Flip(screen);	
	// cout<<"1.10\n";
}
void write_menu_level (SDL_Surface *screen,int score)
{
	TTF_Init();
	TTF_Font* font;
	font = TTF_OpenFont("ARIAL.ttf",20);
	SDL_Surface* text;
	SDL_Color text_color={100,0,200};
	stringstream score2;
    score2 <<" LEVEL : "<<score;
	text = TTF_RenderText_Solid(font,score2.str().c_str(), text_color);
	set_text(460,50,text,screen);	
	SDL_Flip(screen);	
}
void write_menu_OPP_HEALTH (SDL_Surface *screen,int score)
{
	TTF_Init();
	TTF_Font* font;
	font = TTF_OpenFont("ARIAL.ttf",20);
	SDL_Surface* text;
	SDL_Color text_color={255,0,0};
	stringstream score2;
    score2 <<" HEALTH : "<<score;
	text = TTF_RenderText_Solid(font,score2.str().c_str(), text_color);
	set_text(460,300,text,screen);	
	SDL_Flip(screen);	
}
//////////////////////////////
/*
=>rocket strike:
	1.shahab
	2.shot ba rocket
	3.gift

=>getting old image free

=>graphic:
	1.coin
	2.score
	3.heart
	4.shot
	5.sound
*/
