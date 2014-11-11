#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <cmath>
#include <vector>
#include "const.h"

void drawBoard(SDL_Surface *surface,std::vector< std::vector<int> > &snake,SDL_Point cur_food);
#endif
