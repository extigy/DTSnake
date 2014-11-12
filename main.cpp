#include <iostream>
#include <cmath>
#include <SDL/SDL.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "const.h"
#include "graphics.h"
#include "snake.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif



SDL_Surface *screen;
Snake* mainSnake;
SDL_Surface *bgimage = IMG_Load("n3310a.jpg");

void web_frame(){
  SDL_Event event;
  int flag = 0;
  while( SDL_PollEvent( &event ) ){
    if(flag == 0)
    switch( event.type ){
      case SDL_KEYDOWN:
        switch( event.key.keysym.sym ){
            case SDLK_LEFT:
              if(mainSnake->dir != 0 ){
                mainSnake->dir = 2;
                flag = 1;
              }
              break;
            case SDLK_RIGHT:
              if(mainSnake->dir != 2 ){
                mainSnake->dir = 0;
                flag = 1;
              }
              break;
            case SDLK_UP:
              if(mainSnake->dir != 3 ){
                mainSnake->dir = 1;
                flag = 1;
              }
              break;
            case SDLK_DOWN:
              if(mainSnake->dir != 1 ){
                mainSnake->dir = 3;
                flag = 1;
              }
              break;
            default:
                break;
      }
    }
  }

  if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
  drawBoard(screen,mainSnake->board,mainSnake->cur_food);
  mainSnake->updateSnake();
  if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  SDL_Flip(screen);
}

extern "C" {
  int getScore(){
    return mainSnake->score;
  }
}

int main(int argc, char **argv){
  std::srand(std::time(0));
  SDL_Init(SDL_INIT_VIDEO);
  printf("Init: %d\n", TTF_Init());
  printf("%d\n",getScore());
  screen = SDL_SetVideoMode(NX, NY, 32, SDL_HWSURFACE);
  mainSnake = new Snake();
  emscripten_set_main_loop(web_frame, 30, 0);
  SDL_Quit();
  return 0;
}
