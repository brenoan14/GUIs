#include <SDL2/SDL.h>
#include <stdio.h>

int main (){

	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window* w = SDL_CreateWindow("Andando em quadrado", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_SHOWN);
	
	SDL_Renderer* r = SDL_CreateRenderer(w, -1, 0);
	
	SDL_Rect re = {500, 500, 10, 10};
	
	SDL_Event e;
	
	int aux = 1;
	
	float tempo = 0.0f;
	
	float mover = 0.0f;
	
	float fx, fy;
	
	fx = fy = 20.0f;
	
	Uint32 antes = SDL_GetTicks();
	
	while(aux){
		
		if(SDL_WaitEventTimeout(&e, 1)){
            		if(e.type == SDL_QUIT){
                		aux = 0;
            		}
        	}
        	
		Uint32 atual = SDL_GetTicks();
        	tempo = (atual - antes) / 1000.0f;
        	antes = atual;

       		mover = 10 * tempo;
        
		SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
		SDL_RenderClear(r);
		
		SDL_SetRenderDrawColor(r, 0, 0, 255, 0);
		SDL_RenderFillRect(r, &re);
		
		SDL_RenderPresent(r);
		
		if(fx < 100 && fy == 20){
			fx += mover;
			
			if(fx > 100) fx = 100;
		}
		
		else if(fx == 100 && fy < 100){
			fy += mover;
			
			if(fy > 100) fy = 100;
		}
		
		else if(fx > 20 && fy == 100){
			fx -= mover;
		}
		
		else{
			fy -= mover;
			if(fy < 20) fy = 20;
		}
		
		if(e.type == SDL_QUIT){
			aux = 0;
		}
		
		re.x = (int)fx;
		re.y = (int)fy;
	}
	
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	SDL_Quit();	
	
	return 0;
}
