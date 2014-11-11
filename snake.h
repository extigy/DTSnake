#ifndef SNAKE_H
#define SNAKE_H
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SDL/SDL.h>
#include "const.h"

class Snake
{
   public:
      int dir;
      int score;
      SDL_Point cur_food = {0,0};
      std::vector<SDL_Point> snakePoints;
      std::vector< std::vector<int> > board;
      Snake();
      void makeBoard();
      void updateSnake();
      void addToBoard(int x, int y, int val);
      void takeBite(SDL_Point);
      void newFood();
      SDL_Point handleBC(SDL_Point);
      int isPointonSnake(SDL_Point point);
      void restart();
};
#endif
