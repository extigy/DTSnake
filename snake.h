#ifndef SNAKE_H
#define SNAKE_H
#include <cmath>
#include <vector>
#include <SDL/SDL.h>
#include "const.h"

class Snake
{
   public:
      int dir;
      std::vector<SDL_Point> snakePoints;
      std::vector< std::vector<int> > board;
      Snake();
      void makeBoard();
      void updateSnake();
      void addToBoard(int x, int y, int val);
      SDL_Point handleBC(SDL_Point);
};

#endif
