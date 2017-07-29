#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED
#include<SDL/SDL.h>

class paddle
{

    int vely;
    int points;
    SDL_Surface *image;
    SDL_Rect box;

    bool collision(SDL_Rect *rec1,SDL_Rect *rec2);

    public:
    paddle(SDL_Surface *img,int x,int y,int w,int h,int yvel);
    ~paddle();
    SDL_Rect* getRect();
    void moveUp();
    void moveDown();
    void _show();
    void score();
    void resetPaddle(int x,int y,int w,int h,int yvel);
    int getPoints();
};

#endif // PADDLE_H_INCLUDED
