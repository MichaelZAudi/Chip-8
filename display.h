#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL.h"

class Display{
    public:
    // Window, renderer, and texture pointers from SDL.
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    // Set the default height and width of the Chip-8 output.
    int height = 32;
    int width = 64;
    
    Display(const char* title, int scalar);

    ~Display();
    
    void clearScreen();

    void updateScreen(u_int32_t* videoOut, int videoPitch);

    void keyProcessing(u_int8_t* key){
        bool exit = false;

        SDL_Event keyPress;

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_Quit:
                    exit = true;
                    break;
                case SDL_KEYDOWN:
            }
        }
    }
};



#endif