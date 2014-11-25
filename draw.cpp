#include "draw.h"

#include <SDL/SDL.h>
#include <math.h>

void putPixel(SDL_Surface* dest, int x, int y, int r, int g, int b){
	if (x>=0 && x<dest->w && y>=0 && y<dest->h){
		((Uint32*)dest->pixels)[y*dest->pitch/4+x]=SDL_MapRGB(dest->format,r,g,b);
	}
}

void swap(int& a,int& b){
	int tmp=a;
	a=b;
	b=tmp;
}

void drawPoint(SDL_Surface* dest, int x, int y, int r){
	for(int i = 0; i<r; i++){
		for(int a=0;a<360;a++){
			putPixel(dest,x+i*cos(a),y+i*sin(a),0,0,0);
		}
	}	
}

//a mettre après fillrect
void drawLine(SDL_Surface* dest, int x0, int y0, int x1, int y1, int e){
	bool step=abs(x1-x0)<abs(y1-y0);
	if(step){
		swap(x0,y0);
		swap(x1,y1);
	}
	if(x1<x0){
		swap(x0,x1);
		swap(y0,y1);
	}
	float error=0.0f;
	float roundError=(float)abs(y1-y0)/(x1-x0);
	int y=y0;
	int ystep=(y1>y0 ? 1 : -1);
	for(int i=x0;i<x1;i++){
		if(step)putPixel(dest,y,i,0,0,0);
		else putPixel(dest,i,y,0,0,0);
		error += roundError;
		if(error>=0.5){
			y+=ystep;
			error-=1.0;
		}
	}
}