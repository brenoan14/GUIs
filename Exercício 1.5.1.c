#include <stdio.h>
#include <SDL2/SDL.h>

int main (){

	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *w = SDL_CreateWindow("3 retângulos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300, SDL_WINDOW_SHOWN);
	
	SDL_Renderer *ren = SDL_CreateRenderer(w, -1, 0);
	
	int rodar = 1;
	
	int i = 0;
	
	int inverter = 0;
	
	SDL_Rect r[3];
	
	for(i = 0; i < 3; i++){
		r[i].x = 30;
		r[i].w = 10;
		r[i].h = 10;
	}
	
	r[0].y = 30;
	r[1].y = 50;
	r[2].y = 70;
	
	SDL_Color cores[3] = {{255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}};
	
	Uint32 tempoinicial = SDL_GetTicks();
	
	while(rodar){
		
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		SDL_Event evt;
		
		SDL_WaitEventTimeout(&evt, 10);
		
		if(evt.type == SDL_KEYDOWN){
			switch(evt.key.keysym.sym){
			
				case SDLK_UP: if(r[1].y > 0){
							r[1].y -= 5;	
						}
						break;
						
				case SDLK_DOWN: if(r[1].y < 290){
							r[1].y += 5;	
						}
						break;
						
				case SDLK_LEFT: if(r[1].x > 0){
							r[1].x -= 5;	
						}
						break;
						
				case SDLK_RIGHT: if(r[1].x < 390){
							r[1].x += 5;	
						}
						break;
						
				}	
			}
		
		else if(evt.type == SDL_MOUSEMOTION){
			
			if(evt.motion.x >= 390 || evt.motion.x <= 0 || evt.motion.y >= 290|| evt.motion.y <= 0){ 
				if(evt.motion.x > 390){ 
					r[2].y = evt.motion.y; 
					r[2].x = 390; 
				}
				 
				else if(evt.motion.x < 0){ 
					r[2].y = evt.motion.y; 
					r[2].x = 0; 
				}
				 
				if(evt.motion.y > 290){ 
					if(evt.motion.x > 390){
						r[2].x = 390;
					}
					
					else if(evt.motion.x < 0){
						r[2].x = 0;
					}
					
					else{
						r[2].x = evt.motion.x;
					}
					 
					r[2].y = 290; 
				}
				 
				else if(evt.motion.y < 0){ 
					if(evt.motion.x > 390){
						r[2].x = 390;
					}
					
					else if(evt.motion.x < 0){
						r[2].x = 0;
					}
					
					else{
						r[2].x = evt.motion.x;
					}
					
					r[2].y = 0; 
				} 
				} 
			else{ 
				r[2].x = evt.motion.x; 
				r[2].y = evt.motion.y; 
				} 
		}

		else if(evt.type == SDL_QUIT){
			break;
		}
		
		Uint32 tempoatual = SDL_GetTicks();
	
		if(tempoatual - tempoinicial >= 500){
					switch(inverter){
						case 0:
							if(r[0].x < 390){
								r[0].x += 5;
							}
							else if(r[0].x == 390){
								inverter = 1;
							}
							break;
						case 1: 
							if(r[0].x > 0){
								r[0].x -= 5;
							}
							else if(r[0].x == 0){
								inverter = 0;
							}
							break;
						}
			tempoinicial = tempoatual;
			}
			
		for(i = 0; i < 3; i++){
			SDL_SetRenderDrawColor(ren, cores[i].r, cores[i].g, cores[i].b, cores[i].a);
			SDL_RenderFillRect(ren, &r[i]);
		}
		
		SDL_RenderPresent(ren);
	}
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(w);
	SDL_Quit();

	return 0;
}
