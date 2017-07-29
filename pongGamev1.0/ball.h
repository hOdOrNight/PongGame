#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED
#include<SDL/SDL.h>


class ball
{

    int velx,vely;
    SDL_Surface *image;
    SDL_Rect box;

    bool collision(SDL_Rect *rec1,SDL_Rect *rec2);

    public:
    ball(SDL_Surface *img,int x,int y,int w,int h,int xvel,int yvel);
    ~ball();
    void _show();
    void _move(SDL_Rect* pl1,SDL_Rect* pl2);
    void resetBall(int x,int y,int w,int h,int xvel,int yvel);
    int isOut();
};


#endif // BALL_H_INCLUDED
