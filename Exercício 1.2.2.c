#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

int main (){

	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window* w = SDL_CreateWindow("Desenho complexo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 500, SDL_WINDOW_SHOWN);
	
	SDL_Renderer* r = SDL_CreateRenderer(w, -1, 0);
	
	boxRGBA(r, 0, 0, 640, 300, 135, 206, 235, 255);
	
	boxRGBA(r, 0, 300, 640, 480, 34, 139, 34, 255);
	
	filledCircleRGBA(r, 550, 80, 40, 255, 255, 0, 255);
	
	boxRGBA(r, 100, 250, 120, 340, 139, 69, 19, 255);
	
	filledCircleRGBA(r, 90, 240, 25, 0, 128, 0, 255);
  	filledCircleRGBA(r, 120, 240, 25, 0, 128, 0, 255);
    	filledCircleRGBA(r, 105, 220, 25, 0, 128, 0, 255);
	
	SDL_RenderPresent(r);
	
	SDL_Event e;
	int aux = 1;
	
	while(aux){
		if(SDL_WaitEvent(&e) && e.type == SDL_QUIT){
			aux = 0;
		}
	}
		
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	SDL_Quit();	
	
	return 0;
}
