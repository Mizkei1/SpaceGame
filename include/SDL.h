#ifndef SDL_H
#define SDL_H
#include "InitError.h"
#include "Texture.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>

class SDL
{
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
public:
    SDL( Uint32 flags = 0 );
    virtual ~SDL();
    void draw();
    void drawMainMenu();

    SDL_Renderer * getRenderer();
    void highlightMainMenuItem(int number);
    void render();
    void clearScreen();

private:
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;
};

#endif // SDL_H

