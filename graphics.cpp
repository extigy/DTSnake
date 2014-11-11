#include "graphics.h"

SDL_Point pointRotated(SDL_Point actual, SDL_Point orig, float radians) {
  SDL_Point rotated;

  actual.x = actual.x - orig.x;
  actual.y = actual.y - orig.y;
  rotated.x = actual.x * cos(radians) - actual.y * sin(radians);
  rotated.y = actual.x * sin(radians) + actual.y * cos(radians);
  rotated.x = rotated.x + orig.x;
  rotated.y = rotated.y + orig.y;
  return rotated;
}

/*void drawRect(SDL_Surface *surface,SDL_Point pos,SDL_Point size,float rot){
  SDL_Point rot_point;
  SDL_Point orig = {pos.x+size.x/2.0f, pos.y+size.y/2.0f};
  for(int i=pos.x-size.x;i<pos.x+1.42*size.x;i++){
    for(int j=pos.y-size.x;j<pos.y+1.42*size.y;j++){
      SDL_Point ij = {i, j};
      rot_point = pointRotated(ij, orig,rot);
      if(rot_point.x > pos.x && rot_point.x < pos.x+size.x)
      if(rot_point.y > pos.y && rot_point.y < pos.y+size.y)
        *((Uint32*)surface->pixels + ij.y*NY  + ij.x) = SDL_MapRGBA(surface->format, 255,255,255, 255);
    }
  }
}*/

void drawBoard(SDL_Surface *surface, std::vector< std::vector<int> > &snake,SDL_Point cur_food){
  SDL_Point origin = {NX/2.0f, NY/2.0f};
  //for(int i=(NX-NY)/2;i<NX/2+NY/2;i++){
  for(int i=0;i<NX;i++){
    for(int j=0;j<NY;j++){

      if (i < (NX-NY)/2 || i >NX/2+NY/2){
        *((Uint32*)surface->pixels + j*NX  + i) = SDL_MapRGBA(surface->format, 153,232,153, 255);
      }else{
        SDL_Point ij = {i, j};
        //ij = pointRotated(ij, origin, M_PI/4);
        SDL_Point block = {round((ij.x - origin.x)/(double)NS), round((ij.y - origin.y)/(double)NS)};
        if(snake[(NY/NS)+block.x][(NY/NS)+block.y] > 0 || (cur_food.x == block.x && cur_food.y == block.y)){
          *((Uint32*)surface->pixels + j*NX  + i) = SDL_MapRGBA(surface->format, 0,0,0, 240);
        } else {
          if(fabs(block.x)+fabs(block.y) < M_SQRT2*(0.5*NY/NS) && fmax(fabs(block.x),fabs(block.y))<(0.5*NY/NS)){
              //cool effect
              if(i%NS == 0 || i%NS==NS-1 || j%NS == 0 || j%NS==NS-1){
                *((Uint32*)surface->pixels + j*NX  + i) = SDL_MapRGBA(surface->format, 103,182,103, 255);
              }else{
                *((Uint32*)surface->pixels + j*NX  + i) = SDL_MapRGBA(surface->format, 153,232,153, 255);
              }
            } else {
              *((Uint32*)surface->pixels + j*NX  + i) = SDL_MapRGBA(surface->format, 0,0,0, 240);
          }
        }
      }
    }
  }
}
