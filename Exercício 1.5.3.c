#include <SDL2/SDL.h>
#include <stdio.h>

int AUX_WaitEventTimeout (SDL_Event* evt, Uint32* ms){
	
	Uint32 antes = SDL_GetTicks();
	
	int ret = SDL_WaitEventTimeout(evt, *ms);
	
	Uint32 agora = SDL_GetTicks();
	
	if(agora - antes < *ms){
		*ms -= (agora - antes);
	}
	
	else{
		*ms = 0;
	}
	
	return ret;
}

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
	Uint32 ms1;
	
	while(aux){
		
		ms1 = 1;
		
		if(AUX_WaitEventTimeout(&e, &ms1)){
			if(e.type == SDL_QUIT){
				aux = 0;
			}
		}
			
		mover = 10 * (1 - ms1) / 1000.0f;
			
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
		
		re.x = (int)fx;
		re.y = (int)fy;
	}
	
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	SDL_Quit();	
	
 }
