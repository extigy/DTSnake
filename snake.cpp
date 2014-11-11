#include "snake.h"

Snake::Snake(){
  SDL_Point p1 = {0,0};
  SDL_Point p2 = {1,1};
  SDL_Point p3 = {2,2};
  snakePoints.push_back (p1);
  snakePoints.push_back (p2);
  snakePoints.push_back (p3);
  dir = 0;
  makeBoard();
}

void Snake::makeBoard(){
  board.resize( 2*NX/NS , std::vector<int>( 2*NX/NS , 0 ) );
  for(int i=0;i<snakePoints.size();i++){
    addToBoard(snakePoints[i].x, snakePoints[i].y, 1);
  }
}

void Snake::updateSnake(){
  addToBoard(snakePoints[0].x, snakePoints[0].y, 0);
  snakePoints.erase(snakePoints.begin());

  int lv = snakePoints.size()-1;
  SDL_Point point = {0,0};
  switch(dir){
    case 0:
      point.x = snakePoints[lv].x+1;
      point.y = snakePoints[lv].y;
      break;
    case 1:
      point.x = snakePoints[lv].x;
      point.y = snakePoints[lv].y-1;
      break;
  }

  point = handleBC(point);
  snakePoints.push_back(point);
  addToBoard(snakePoints[lv+1].x, snakePoints[lv+1].y, 1);
}

SDL_Point Snake::handleBC(SDL_Point point){
  SDL_Point newpoint = point;
  if( point.x >= floor(0.5*NX/NS) ){
    newpoint.x = point.y;
    newpoint.y = floor(0.5*NX/NS);
    dir = 1;
  }

  if( point.y <= -floor(0.5*NX/NS) ){
    newpoint.y = point.x;
    newpoint.x = -floor(0.5*NX/NS);
    dir = 0;
  }

  return newpoint;
}

void Snake::addToBoard(int x, int y, int val){
  board[NX/NS+x][NX/NS+y] = val;
}
