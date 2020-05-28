#include <iostream>
#include <cstring>
#include <SDL.h>
#include <time.h>
#include <conio.h>
#include <sstream>
#include "pro2.h"

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const string WINDOW_TITLE = "Snake CODE BY QD";
const int dai=63;
const int rong=35;


int SIZE = 20;
int diChuyen = 3;
int soDot = 5;
int score = 0;
int gameLost;
int speed=150;
int check=0;
int n=0;

struct ToaDo
{
    int a;
    int b;
};

ToaDo fruit;
ToaDo snake[1500];
ToaDo tuong[1500];


void GameAction()
{
    for(int i = soDot ; i> 0 ; i--){
        snake[i].a = snake[i-1].a;
        snake[i].b = snake[i-1].b;
    }
    if (score % 50 == 0 && score /50 >0 ) {
     if(diChuyen == 0){
        snake[0].b++;
    }
    else
        if(diChuyen == 1){
        snake[0].b--;
    }
    else
        if(diChuyen == 2){
        snake[0].a++;
    }
    else
        if(diChuyen == 3){
        snake[0].a--;
    }
    }

    else
     {
    if(diChuyen == 0)
    {
        snake[0].a--;
    }
    else if(diChuyen == 1)
    {
        snake[0].a++;
    }
    else if(diChuyen == 2)
    {
        snake[0].b--;
    }
    else if(diChuyen == 3)
    {
        snake[0].b++;
    }}

    if(snake[0].a == fruit.a && snake[0].b == fruit.b)
    {
        soDot++;
        score += 10;
        check++;
        n++;
        if ((score % 50 == 0) && (speed >50)){
                speed = speed -50;

        }

        fruit.a = rand() % dai;
        fruit.b = rand() % rong;

    }

    if(snake[0].a > dai)
    {
        snake[0].a = 0;
    }
    if(snake[0].a < 0)
    {
        snake[0].a = dai;
    }
    if(snake[0].b > rong)
    {
        snake[0].b = 0;
    }
    if(snake[0].b < 0)
    {
        snake[0].b = rong;
    }
    for(int i = 1; i< soDot ; i++)
    {
        if(snake[0].a == snake[i].a && snake[0].b == snake[i].b)
        {
            gameLost = 1;
        }
    }
    for(int i = 1; i< soDot-4 ; i++)
    {
        if(snake[0].a == snake[i].a && snake[0].b == snake[i].b)
        {
            gameLost = 1;
        }
        if(snake[0].a == tuong[i-1].a && snake[0].b == tuong[i-1].b)
        {
            gameLost = 1;
        }
    }
}




SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect);

int main(int argc, char* argv[])
{
    srand(time(NULL));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer,  SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    SDL_Event e;

    SDL_Texture *background = loadTexture("image/back.bmp", renderer);
    SDL_Texture *head = loadTexture("image/head.bmp", renderer);
    SDL_Texture *body = loadTexture("image/body.bmp", renderer);
    SDL_Texture *gameover = loadTexture("image/over.bmp", renderer);
    SDL_Texture *tao = loadTexture("image/tao.bmp", renderer);
    SDL_Texture *tuong_ = loadTexture("image/tuong.bmp", renderer);

    if (background == nullptr || head == nullptr || body == nullptr || gameover == nullptr || tao == nullptr /*|| taoto == nullptr*/){
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(head);
        SDL_DestroyTexture(body);
        SDL_DestroyTexture(gameover);
        SDL_DestroyTexture(tao);
        //SDL_DestroyTexture(taoto);
        quitSDL(window, renderer);
    }

    SDL_RenderClear(renderer);
    fruit.a = 20;
    fruit.b = 20;
   while (true) {
         if (e.key.keysym.sym == SDLK_ESCAPE){
                gameLost=0;
                break;
            }
        SDL_Delay(speed);

        renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        while (SDL_PollEvent(&e)) {

         if (e.key.keysym.sym == SDLK_LEFT && diChuyen!=1) diChuyen=0;
         if (e.key.keysym.sym == SDLK_RIGHT && diChuyen!=0) diChuyen=1;
         if (e.key.keysym.sym == SDLK_UP && diChuyen!=3) diChuyen=2;
         if (e.key.keysym.sym == SDLK_DOWN && diChuyen!=2) diChuyen=3;

        }

        GameAction();
        if(gameLost == 1)
        {   cout << "Your Score : " << score << endl;
            renderTexture(gameover, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderPresent(renderer);
            SDL_Delay(2000);
            break;
        }
        else {
            if(check==1){
                check=0;
                do{
                    tuong[n].a = rand() % dai;
                    tuong[n].b = rand() % rong;
                }
                while ((tuong[n].a == snake[0].a) && (tuong[n].b == snake[0].b));



                //renderTexture(tuong_,renderer,tuong[n].a * SIZE, tuong[n].b * SIZE);
                //SDL_RenderPresent(renderer);
            }
             for(int i=0; i<n; i++){
                    renderTexture(tuong_,renderer,tuong[i].a * SIZE, tuong[i].b * SIZE);
                }
            renderTexture(head,renderer,snake[0].a*SIZE, snake[0].b*SIZE);
            renderTexture(tao,renderer,fruit.a * SIZE, fruit.b * SIZE);
            for(int i=1; i<soDot; i++){
                    renderTexture(body,renderer,snake[i].a*SIZE, snake[i].b*SIZE);
                }
        }
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(head);
    SDL_DestroyTexture(body);
    SDL_DestroyTexture(gameover);
    SDL_DestroyTexture(tao);

    quitSDL(window, renderer);
    return 0;
}


SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}


void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}




