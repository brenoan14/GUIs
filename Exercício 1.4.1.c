#include <SDL2/SDL.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    SDL_Rect rs[10];
    SDL_Color cores[10] = { {255, 0, 0, 255}, {0, 255, 0, 255}, {255, 255, 0, 255}, {255, 0, 255, 255}, {0, 255, 255, 255}, {128, 0, 0, 255}, {0, 128, 0, 255}, {0, 0, 128, 255}, {128, 128, 0, 255}, {128, 0, 128, 255}};
    
    int i = 0;
    int j = 0
    ;
    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        
        SDL_WaitEvent(&evt);

        if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                
                    if(r.y > 0){
                    	r.y -= 5;
                    	}
                    	
                    break;
                    
                case SDLK_DOWN:
                
                    if(r.y < 90){
                    	r.y += 5;
                    	}
                    	
                    break;
                    
                case SDLK_LEFT:
                
                    if(r.x > 0){
                    r.x -= 5;
                    }
                    
                    break;
                    
                case SDLK_RIGHT:
                
                    if(r.x < 190){
                    r.x += 5;
                    }
                    
                    break;
            }
        }
        
        else if(evt.type == SDL_QUIT){
        	break;
        }
        
        else if(evt.type == SDL_MOUSEBUTTONDOWN && i < 10){
        
        	if(evt.button.button == SDL_BUTTON_LEFT){
        		rs[i].x = evt.button.x;
        		rs[i].y = evt.button.y;
        		rs[i].w = 10;
        		rs[i].h = 10;
        		i++;
        	}
        }
        
        for(j = 0; j < i; j++){
        		SDL_SetRenderDrawColor(ren, cores[j].r, cores[j].g, cores[j].b, cores[j].a);
        		SDL_RenderFillRect(ren, &rs[j]);
        }
        
        SDL_RenderPresent(ren);
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
