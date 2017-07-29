#include "paddle.h"
#include "ball.h"
#include<bits/stdc++.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>

#define resX 640
#define resY 480
#define bpp 32
#define FPS 30

using namespace std;

SDL_Surface* loadImage(const char *c,Uint32 colorkey=0)
{
    SDL_Surface *img=SDL_LoadBMP(c);
    if(img==NULL)
        exit(1);

    SDL_SetColorKey(img,SDL_SRCCOLORKEY,colorkey);
    return img;
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *screen;
	screen = SDL_SetVideoMode(resX, resY, bpp, SDL_SWSURFACE);

	paddle player1(loadImage("paddle.bmp"),0,240,10,50,3);
	paddle player2(loadImage("paddle.bmp"),resY-10,240,10,50,3);
	ball _ball(loadImage("ball.bmp",SDL_MapRGB(screen->format,0,255,255)),resX/2,resY/2,20,20,3,3);


	TTF_Font *font;
	TTF_Init();
	font=TTF_OpenFont("Pacifico.ttf",50);
	SDL_Color color={0,0,0};


	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	Mix_Music *music;
	Mix_Chunk* effect;
	music=Mix_LoadMUS("chill.wav");
	effect=Mix_LoadWAV("drum.wav");
	Mix_PlayMusic(music,-1);

	bool running = true;

	Uint32 start;
	bool b[4] = {0,0,0,0};


	while(running) {
		start = SDL_GetTicks();
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_UP:
							b[0] = 1;
							break;
						case SDLK_DOWN:
							b[1] = 1;
							break;
						case SDLK_w:
							b[2] = 1;
							break;
						case SDLK_s:
							b[3] = 1;
							break;
						default:
                        break;

					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym) {
						case SDLK_UP:
							b[0] = 0;
							break;
						case SDLK_DOWN:
							b[1] = 0;
							break;
						case SDLK_w:
							b[2] = 0;
							break;
						case SDLK_s:
							b[3] = 0;
							break;
						default:
                        break;

					}
					break;
                    default:
                        break;
			}
		}

		//logic
		if(b[0])
			player2.moveUp();
		if(b[1])
			player2.moveDown();
		if(b[2])
			player1.moveUp();
		if(b[3])
			player1.moveDown();

		_ball._move(player1.getRect(),player2.getRect());

        switch(_ball.isOut())
        {
            case 1:
                    player2.score();
                    player1.resetPaddle(0,240,10,50,3);
                    player2.resetPaddle(resY-10,240,10,50,3);
                    _ball.resetBall(resX/2,resY/2,20,20,3,3);
                    break;
            case 2:
                    player1.score();
                    player1.resetPaddle(0,240,10,50,3);
                    player2.resetPaddle(resY-10,240,10,50,3);
                    _ball.resetBall(resX/2,resY/2,20,20,3,3);
                    break;
            default:
                    break;


        }
		//render
        SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,255,255,255));

		player1._show();
		player2._show();
		_ball._show();


        char c[5];
        SDL_Rect txtrect={10,0};

        sprintf(c,"%d",player1.getPoints());
        SDL_Surface *text=TTF_RenderText_Solid(font,c,color);
        SDL_BlitSurface(text,NULL,screen,&txtrect);

        txtrect.x=resY-40;
        sprintf(c,"%d",player2.getPoints());
        text=TTF_RenderText_Solid(font,c,color);
        SDL_BlitSurface(text,NULL,screen,&txtrect);

        SDL_FreeSurface(text);

		SDL_Flip(screen);

		if(1000/FPS > SDL_GetTicks()-start) {
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
		}
	}

	//deinit to free up resources;avoid memory leaks

    Mix_FreeMusic(music);
    Mix_FreeChunk(effect);
    Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

