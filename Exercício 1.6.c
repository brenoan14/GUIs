#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

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
	TTF_Init();
	
	SDL_Window *w = SDL_CreateWindow("3 retângulos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300, SDL_WINDOW_SHOWN);
	
	SDL_Renderer *ren = SDL_CreateRenderer(w, -1, 0);
	
	TTF_Font* fnt = TTF_OpenFont("tiny.ttf", 20);
	assert(fnt != NULL);
	SDL_Color clr = {255,255,255,255};
	
	int rodar = 1;
	
	int i = 0;
	
	Uint32 tempo[3];
	
	Uint32 tprimeiro;
	
	int chegada[3];
	
	for(i = 0; i < 3; i++){
		chegada[i] = 0;
	}
	
	int primeiro = 0;
	
	typedef struct Textos{
			char str[40];
	}Texto;
	
	Texto vet[3];
	
	strcpy(vet[0].str,"O vermelho venceu !!");
	strcpy(vet[1].str,"O verde venceu !!");
	strcpy(vet[2].str, "O azul venceu !!");
	
	SDL_Rect r[3];
	
	SDL_Rect rc = {350, 0, 50, 300};
	
	SDL_Rect re = {150, 5, 100, 20};
	
	for(i = 0; i < 3; i++){
		r[i].w = 10;
		r[i].h = 10;
	}
	
	r[0].y = 30;
	r[1].y = 50;
	r[2].y = 70;
	
	SDL_Color cores[3] = {{255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}};
	
	Uint32 tempoinicial = SDL_GetTicks();
	
	Uint32 ms1;
	
	SDL_Texture* txt = NULL;
	SDL_Surface* sfc = NULL;
	
	int fim = 1;
	
	int ms2 = 1000;
	
	SDL_Event evt;
	
	while(rodar){
		
		if(evt.type == SDL_QUIT){
			break;
		}
		
		for(i = 0; i < 3; i++){
			chegada[i] = 0;
		}
	
		int primeiro = 0;
		
		for(i = 0; i < 3; i++){
			r[i].x = 30;
		}
		
		r[0].y = 30;
		r[1].y = 50;
		r[2].y = 70;
		
		fim = 1;
		
		while(fim){	
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderFillRect(ren, &rc);
		
		SDL_Event evt;
		
		ms1 = 10;
		
		AUX_WaitEventTimeout(&evt, &ms1);
		
		if(evt.type == SDL_KEYDOWN && r[1].x < 350){
			switch(evt.key.keysym.sym){
						
				case SDLK_LEFT: if(r[1].x > 0){
							r[1].x -= 5;	
						}
						break;
						
				case SDLK_RIGHT:r[1].x += 5;
						break;
				}	
			}
		
		else if(evt.type == SDL_MOUSEMOTION && r[2].x < 350){
			
			if(evt.motion.x < 0){   
					r[2].x = 0; 
			} 
			
			else if(evt.motion.x > 350){
				r[2].x = 350;
			}
			else{ 
				r[2].x = evt.motion.x;
			} 
		}

		else if(evt.type == SDL_QUIT){
			rodar = 0;
			break;
		}
		
		Uint32 tempoatual = SDL_GetTicks();
	
		if(tempoatual - tempoinicial >= 500){
			if(r[0].x < 350){
					    r[0].x += 5;
					}
			tempoinicial = tempoatual;
			}
			
		for(i = 0; i < 3; i++){
			SDL_SetRenderDrawColor(ren, cores[i].r, cores[i].g, cores[i].b, cores[i].a);
			SDL_RenderFillRect(ren, &r[i]);
		
			if(r[i].x == 350 && chegada[i] == 0){
				tempo[i] = SDL_GetTicks();
				chegada[i] = 1;
			}
		}
		
		if(r[0].x == 350 && r[1].x == 350 && r[2].x == 350){
		
			tprimeiro = tempo[0];
			
			for(i = 1; i < 3; i++){
				if(tempo[i] < tprimeiro){
					tprimeiro = tempo[i];
					primeiro = i;
				}
			}
			
			sfc = TTF_RenderText_Blended(fnt, vet[primeiro].str, clr);
			assert(sfc != NULL);
			txt = SDL_CreateTextureFromSurface(ren, sfc);
			assert(txt != NULL);
			SDL_FreeSurface(sfc);
				
			SDL_RenderCopy(ren, txt, NULL, &re);
			
			ms2 = 5000;
			fim = 0;
		}
		
		SDL_RenderPresent(ren);
		
		if(fim == 0){
			AUX_WaitEventTimeout(&evt, &ms2);
		}
	}
	}
	SDL_DestroyTexture(txt);
	TTF_CloseFont(fnt);
	TTF_Quit();
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(w);
	SDL_Quit();

	return 0;
}
