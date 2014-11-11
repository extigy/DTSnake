#include <iostream>
#include <cmath>
#include <SDL/SDL.h>
#include <vector>
#include "const.h"
#include "graphics.h"
#include "snake.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif



SDL_Surface *screen;
Snake* mainSnake;

void web_frame(){
  SDL_PumpEvents();
  /*
  if (SDL_GetMouseState(x, y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
    //printf("Mouse Button 1 (left) is pressed. at %d. %d", x/4, y/4);
    vortex_loc(ws->grid,0,x/4, y/4);
  }
  if (SDL_GetMouseState(x, y) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
    //printf("Mouse Button 1 (left) is pressed. at %d. %d", x/4, y/4);
    vortex_loc(ws->grid,1,x/4, y/4);
  }*/

  if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
  drawBoard(screen,mainSnake->board);
  mainSnake->updateSnake();
  if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  SDL_Flip(screen);
}

int main(){
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(NX, NY, 32, SDL_SWSURFACE);
  mainSnake = new Snake();
  emscripten_set_main_loop(web_frame, 10, 0);
  SDL_Quit();
  return 0;
}
