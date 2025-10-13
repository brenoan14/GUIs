#include <SDL2/SDL.h>


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
    
    SDL_Window* win = SDL_CreateWindow("Testando AUX_WaitEventTimeout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 600, SDL_WINDOW_SHOWN);
    
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
    
    SDL_Rect r = {200, 200, 10, 10};
    
    int rodar = 1;
    
    SDL_Event evt;
    
    Uint32 ms1 = 1000;
    
    while(rodar && AUX_WaitEventTimeout(&evt, &ms1)){
   	
   	ms1 = 1000;
	
    	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    	SDL_RenderClear(ren);
    	
    	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    	SDL_RenderFillRect(ren, &r);
    	
    	SDL_RenderPresent(ren);
    	
    	if(evt.type == SDL_KEYDOWN){
    		switch(evt.key.keysym.sym){
    		
    			case SDLK_UP: r.y -= 5;
    				     break;
    			case SDLK_DOWN: r.y += 5;
    				       break;
    			case SDLK_LEFT: r.x -= 5;
    				       break;
    			case SDLK_RIGHT: r.x += 5;
    				     	break;
    			}
    	}
    	
    	else if(evt.type == SDL_QUIT){
    		rodar = 0;
    	}
    	
    	}
    	
    	SDL_DestroyRenderer(ren);
    	SDL_DestroyWindow(win);
    	SDL_Quit();
    }
