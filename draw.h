#ifndef DRAW
#define DRAW

#include  <SDL/SDL.h>

void putPixel(SDL_Surface* dest, int x, int y, int r, int g, int b);
void drawPoint(SDL_Surface* dest, int x, int y, int r);
void drawLine(SDL_Surface* dest, int x1, int y1, int x2, int y2, int e=1);

#endif