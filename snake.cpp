#include "snake.h"

Snake::Snake(){
  SDL_Point p1 = {0,0};
  SDL_Point p2 = {0,0};
  SDL_Point p3 = {0,0};
  snakePoints.push_back (p1);
  snakePoints.push_back (p2);
  snakePoints.push_back (p3);
  dir = 1;
  score = 0;
  newFood();
  makeBoard();
}

void Snake::makeBoard(){
  board.resize( 2*NY/NS , std::vector<int>( 2*NY/NS , 0 ) );
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
    case 2:
      point.x = snakePoints[lv].x-1;
      point.y = snakePoints[lv].y;
      break;
    case 3:
      point.x = snakePoints[lv].x;
      point.y = snakePoints[lv].y+1;
      break;
    case 4:
      point.x = snakePoints[lv].x+1;
      point.y = snakePoints[lv].y-1;
      break;
    case 5:
      point.x = snakePoints[lv].x-1;
      point.y = snakePoints[lv].y-1;
      break;
    case 6:
      point.x = snakePoints[lv].x-1;
      point.y = snakePoints[lv].y+1;
      break;
    case 7:
      point.x = snakePoints[lv].x+1;
      point.y = snakePoints[lv].y+1;
      break;
  }

  point = handleBC(point);
  if(isPointonSnake(point) == 1){
    restart();
    return;
  }
  snakePoints.push_back(point);
  addToBoard(snakePoints[lv+1].x, snakePoints[lv+1].y, 1);
  takeBite(point);
}

void Snake::restart(){
  for(int i=0;i<2*(NY/NS);i++){
    for(int j=0;j<2*(NY/NS);j++){
      board[i][j] = 0;
    }
  }
  snakePoints.clear();
  SDL_Point p1 = {0,0};
  SDL_Point p2 = {0,0};
  SDL_Point p3 = {0,0};
  snakePoints.push_back (p1);
  snakePoints.push_back (p2);
  snakePoints.push_back (p3);
  dir = 1;
  score = 0;
  newFood();
}

void Snake::takeBite(SDL_Point point){
  if(point.x == cur_food.x && point.y == cur_food.y){
    snakePoints.push_back(point);
    score++;
    newFood();
  }
}

void Snake::newFood(){
  cur_food.x = 999;
  cur_food.y = 999;
  while(fabs(cur_food.x)+fabs(cur_food.y) + 2 > M_SQRT2*(0.5*NY/NS) && isPointonSnake(cur_food) == 0){
    cur_food.x = rand()%(NY/NS - 2) - (0.5*NY/NS - 1);
    cur_food.y = rand()%(NY/NS - 2) - (0.5*NY/NS - 1);
  }
}

int Snake::isPointonSnake(SDL_Point point){
  int flag = 0;
  for(int i=0;i<snakePoints.size();i++){
    if(point.x == snakePoints[i].x && point.y == snakePoints[i].y){
      flag = 1;
      break;
    }
  }
  return flag;
}

SDL_Point Snake::handleBC(SDL_Point point){
  SDL_Point newpoint = point;
  if( point.x >= floor(0.5*NY/NS) ){
    newpoint.x = point.y;
    newpoint.y = floor(0.5*NY/NS);
    switch(dir){
      case 0:
        dir = 1;
        break;
      case 4:
        dir = 5;
        break;
      case 7:
        dir = 4;
        break;
    }
    return newpoint;
  }

  if( point.y <= -floor(0.5*NY/NS) ){
    newpoint.y = point.x;
    newpoint.x = -floor(0.5*NY/NS);
    switch(dir){
      case 1:
        dir = 0;
        break;
      case 4:
        dir = 7;
        break;
      case 5:
        dir = 4;
        break;
    }
    return newpoint;
  }

  if( point.y >= floor(0.5*NY/NS) ){
    newpoint.y = point.x;
    newpoint.x = floor(0.5*NY/NS);
    switch(dir){
      case 3:
        dir = 2;
        break;
      case 6:
        dir = 5;
        break;
      case 7:
        dir = 6;
        break;
    }
    return newpoint;
  }

  if( point.x <= -floor(0.5*NY/NS) ){
    newpoint.x = point.y;
    newpoint.y = -floor(0.5*NY/NS);
    switch(dir){
      case 2:
        dir = 3;
        break;
      case 5:
        dir = 6;
        break;
      case 6:
        dir = 7;
        break;
    }
    return newpoint;
  }

  if( point.x - point.y  > M_SQRT2*(0.5*NY/NS) ){
    newpoint.x = point.x;
    newpoint.y = -point.y;
    switch(dir){
      case 4:
        dir = 5;
        break;
      case 0:
        dir = 1;
        break;
      case 1:
        dir = 2;
        break;
    }
    return newpoint;
  }

  if( -point.x - point.y  > M_SQRT2*(0.5*NY/NS) ){
    newpoint.x = point.x;
    newpoint.y = -point.y;
    switch(dir){
      case 5:
        dir = 4;
        break;
      case 2:
        dir = 1;
        break;
      case 1:
        dir = 0;
        break;
    }
    return newpoint;
  }

  if( -point.x + point.y  > M_SQRT2*(0.5*NY/NS) ){
    newpoint.x = point.x;
    newpoint.y = -point.y;
    switch(dir){
      case 6:
        dir = 7;
        break;
      case 2:
        dir = 3;
        break;
      case 3:
        dir = 0;
        break;
    }
    return newpoint;
  }

  if( point.x + point.y  > M_SQRT2*(0.5*NY/NS) ){
    newpoint.x = point.x;
    newpoint.y = -point.y;
    switch(dir){
      case 7:
        dir = 6;
        break;
      case 0:
        dir = 3;
        break;
      case 3:
        dir = 2;
        break;
    }
    return newpoint;
  }

  return newpoint;
}

void Snake::addToBoard(int x, int y, int val){
  board[NY/NS+x][NY/NS+y] = val;
}
