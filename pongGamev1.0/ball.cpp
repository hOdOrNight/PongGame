#include "ball.h"

ball::ball(SDL_Surface *img,int x,int y,int w,int h,int xvel,int yvel)
{
    image=img;
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;

    velx=xvel;
    vely=yvel;
}

ball::~ball()
{
    SDL_FreeSurface(image);
}

void ball::_show()
{
    SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}

void ball::_move(SDL_Rect* pl1,SDL_Rect* pl2)
{
    box.x+=velx;
    box.y+=vely;

    if(box.y<0)
        vely=-vely;
    if(box.y+box.h>=SDL_GetVideoSurface()->clip_rect.h)
        vely=-vely;
    if(collision(&box,pl1))
    {
        if(box.x+3<pl1->x+pl1->w)
            vely=-vely;
        else
            velx=-velx;
    }
    if(collision(&box,pl2))
    {
        if(box.x+box.w-3>pl2->x)
            vely=-vely;
        else
            velx=-velx;
    }



}

bool ball::collision(SDL_Rect* rect1,SDL_Rect* rect2)
{
	if(rect1->y >= rect2->y + rect2->h)
		return 0;
	if(rect1->x >= rect2->x + rect2->w)
		return 0;
	if(rect1->y + rect1->h <= rect2->y)
		return 0;
	if(rect1->x + rect1->w <= rect2->x)
		return 0;
	return 1;
}

int ball::isOut()
{
    if(box.x<=0)
        return 1;
    if(box.x>=SDL_GetVideoSurface()->clip_rect.w)
        return 2;

    return 0;
}
void ball::resetBall(int x,int y,int w,int h,int xvel,int yvel)
{
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;

    velx=xvel;
    vely=yvel;
}
