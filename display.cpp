#include "display.h"
#include "SDL.h"


Display::Display(const char* title, int scalar){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (width * scalar), (height * scalar), 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
}

Display::~Display(){
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void Display::updateScreen(u_int32_t* videoOut, int videoPitch){
    SDL_UpdateTexture(texture, NULL, videoOut, videoPitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool Display::keyProcessing(u_int8_t* key){
    bool exit = false;
    SDL_Event press;
    while(SDL_PollEvent(&press)){
        switch(press.type){
            case SDL_QUIT:
                exit = true;
                break;
            case SDL_KEYDOWN:
                switch (press.key.keysym.sym)
                {
                    case SDLK_x:
                        key[0] = 1;
                        break;
                    case SDLK_1:
                        key[1] = 1;
                        break;
                    case SDLK_2:
                        key[2] = 1;
                        break;
                    case SDLK_3:
                        key[3] = 1;
                        break;
                    case SDLK_q:
                        key[4] = 1;
                        break;
                    case SDLK_w:
                        key[5] = 1;
                        break;
                    case SDLK_e:
                        key[6] = 1;
                        break;
                    case SDLK_a:
                        key[7] = 1;
                        break;
                    case SDLK_s:
                        key[8] = 1;
                        break;
                    case SDLK_d:
                        key[9] = 1;
                        break;
                    case SDLK_z:
                        key[0xA] = 1;
                        break;
                    case SDLK_c:
                        key[0xB] = 1;
                        break;
                    case SDLK_4:
                        key[0xC] = 1;
                        break;
                    case SDLK_r:
                        key[0xD] = 1;
                        break;
                    case SDLK_f:
                        key[0xE] = 1;
                        break;
                    case SDLK_v:
                        key[0xF] = 1;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (press.key.keysym.sym)
                {
                    case SDLK_x:
                        key[0] = 0;
                        break;
                    case SDLK_1:
                        key[1] = 0;
                        break;
                    case SDLK_2:
                        key[2] = 0;
                        break;
                    case SDLK_3:
                        key[3] = 0;
                        break;
                    case SDLK_q:
                        key[4] = 0;
                        break;
                    case SDLK_w:
                        key[5] = 0;
                        break;
                    case SDLK_e:
                        key[6] = 0;
                        break;
                    case SDLK_a:
                        key[7] = 0;
                        break;
                    case SDLK_s:
                        key[8] = 0;
                        break;
                    case SDLK_d:
                        key[9] = 0;
                        break;
                    case SDLK_z:
                        key[0xA] = 0;
                        break;
                    case SDLK_c:
                        key[0xB] = 0;
                        break;
                    case SDLK_4:
                        key[0xC] = 0;
                        break;
                    case SDLK_r:
                        key[0xD] = 0;
                        break;
                    case SDLK_f:
                        key[0xE] = 0;
                        break;
                    case SDLK_v:
                        key[0xF] = 0;
                        break;
                }
                break;
        }
    }
    return exit;
}