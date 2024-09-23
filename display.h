#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL.h"

class display{
    public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    u_int32_t backgroundColor = 0xFFFFFFFF;
    u_int32_t textColor = 0x00000000;
    
    display(const char* title, int scalar);
    
    void clearScreen();
};



#endif