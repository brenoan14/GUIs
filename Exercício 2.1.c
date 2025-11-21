#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int AUX_WaitEventTimeout(SDL_Event *evt, Uint32 *ms){
    Uint32 antes = SDL_GetTicks();
    int ret = SDL_WaitEventTimeout(evt, *ms);
    Uint32 agora = SDL_GetTicks();

    if (agora - antes < *ms)
        *ms -= (agora - antes);
    else
        *ms = 0;

    return ret;
}

int main(){

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *win = SDL_CreateWindow("Multiplos cliques",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Event e;
    bool rodar = true;

    SDL_Rect r1 = {100, 200, 150, 150};
    SDL_Rect r2 = {325, 200, 150, 150};
    SDL_Rect r3 = {550, 200, 150, 150};

    int n = 0;
    bool contando = false;
    bool resetado = false;

    int x = 0, y = 0;
    Uint32 ms = 250;

    int quadrado_clicado = 0;
    int max1 = 0;
    int max2 = 0;
    int max3 = 0;

    int x_clique, y_clique;
    int aux;

    int seq_final_quadrado = 0;
    
    int cliques;
    int quad;

    while(rodar){

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        SDL_RenderFillRect(ren, &r1);

        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
        SDL_RenderFillRect(ren, &r2);

        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        SDL_RenderFillRect(ren, &r3);

        SDL_RenderPresent(ren);

        ms = 250;

        while(true){

            aux = AUX_WaitEventTimeout(&e, &ms);

            if(aux == 0){

                if(contando && !resetado && n > 0){

                    seq_final_quadrado = quadrado_clicado;

                    SDL_Event evt;
                    evt.type = SDL_USEREVENT;
                    evt.user.type = SDL_USEREVENT;
                    evt.user.code = n;     
                    evt.user.data1 = NULL;
                    evt.user.data2 = NULL;

                    SDL_PushEvent(&evt);
                }

                n = 0;
                contando = false;
                resetado = false;
                quadrado_clicado = 0;
                break;
            }

            if(e.type == SDL_QUIT){
                rodar = false;
                break;
            }

            if(e.type == SDL_USEREVENT){

                cliques = e.user.code;
                quad = seq_final_quadrado;

                if(quad == 1 && cliques > max1) max1 = cliques;
                if(quad == 2 && cliques > max2) max2 = cliques;
                if(quad == 3 && cliques > max3) max3 = cliques;

                printf("Quadrado %d: %d cliques consecutivos\n", quad, cliques);
            }

            if(e.type == SDL_MOUSEMOTION && contando){
                resetado = true;
                n = 0;
                continue;
            }

            if(e.type == SDL_MOUSEBUTTONDOWN){

                x_clique = e.button.x;
                y_clique = e.button.y;

                if(x_clique >= r1.x && x_clique <= r1.x + r1.w && y_clique >= r1.y && y_clique <= r1.y + r1.h){
                    	quadrado_clicado = 1;
                    }

                else if(x_clique >= r2.x && x_clique <= r2.x + r2.w && y_clique >= r2.y && y_clique <= r2.y + r2.h){
                    quadrado_clicado = 2;
		}
		
                else if(x_clique >= r3.x && x_clique <= r3.x + r3.w && y_clique >= r3.y && y_clique <= r3.y + r3.h){
                    quadrado_clicado = 3;
                }
                
                else{
                    resetado = true;
                    n = 0;
                    continue;
                }

                if(!contando){
                    contando = true;
                    x = x_clique;
                    y = y_clique;
                    n = 1;
                }
                else if(x_clique == x && y_clique == y && !resetado){
                    n++;
                }
                else{
                    resetado = true;
                    n = 0;
                }

                ms = 250;
            }
        }
    }

    printf("\nNúmero máximo de cliques consecutivos:\n");
    printf("Quadrado vermelho: %d\n", max1);
    printf("Quadrado verde: %d\n", max2);
    printf("Quadrado azul: %d\n", max3);

    if(max1 > max2 && max1 > max3)
        printf("Quadrado vermelho teve a maior sequência.\n");
    else if(max2 > max1 && max2 > max3)
        printf("Quadrado verde teve a maior sequência.\n");
    else if(max3 > max1 && max3 > max2)
        printf("Quadrado azul teve a maior sequência.\n");
    else
        printf("Empate na maior sequência.\n");

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
