#include "paddle.h"

paddle::paddle(SDL_Surface *img,int x,int y,int w,int h,int yvel)
{
    image=img;

    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    points=0;
    vely=yvel;
}

paddle::~paddle()
{
    SDL_FreeSurface(image);
}

void paddle::_show()
{
    SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&box);
}

void paddle::moveUp()
{

    if(box.y>0)
    box.y-=vely;

}

void paddle::moveDown()
{
    if(box.y+box.h<SDL_GetVideoSurface()->clip_rect.h)
        box.y+=vely;

}
SDL_Rect* paddle::getRect()
{
    return &box;
}
bool paddle::collision(SDL_Rect* rect1,SDL_Rect* rect2)
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
void paddle::score()
{
    points++;
}
void paddle::resetPaddle(int x,int y,int w,int h,int yvel)
{
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    vely=yvel;
}
int paddle::getPoints()
{
    return points;
}
