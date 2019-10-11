#include "MainMenu.h"
#include "Gameplay.h"

MainMenu::MainMenu()
{
    //ctor
}

MainMenu::~MainMenu()
{
    //dtor
}

bool MainMenu::mainmenu(SDL sdl) {
     bool quit = false;
    SDL_Event e;
    bool rerenderMainMenu = false;
    bool play = false;
    while (!quit) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                int x,y;
                SDL_GetMouseState(&x, &y);
                if(x > 220 && x <  420 && y > 480 / 4 && y < 480 / 4 + 60) {
                    Gameplay gameplay(sdl.getRenderer());
                    gameplay.play(sdl, sdl.getRenderer());
                    return true;
                }
                else if (x > 220 && x < 420 && y > 480 / 2 && y < 480 / 2 + 70) {
                    sdl.~SDL();
                    quit = true;
                }
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&x, &y);
                if(x > 220 && x <  420 && y > 480 / 4 && y < 480 / 4 + 60) {
                    sdl.highlightMainMenuItem(0);
                    rerenderMainMenu = true;
                }
                else if (x > 220 && x < 420 && y > 480 / 2 && y < 480 / 2 + 70) {
                    sdl.highlightMainMenuItem(1);
                    rerenderMainMenu = true;
                }
                else if (rerenderMainMenu) {
                    sdl.drawMainMenu();
                    rerenderMainMenu = false;
                }
                break;
            }
        }
    }

}
