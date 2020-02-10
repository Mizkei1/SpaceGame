#include <exception>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "InitError.h"

#include "SDL.h"
#include "MainMenu.h"
#include "Gameplay.h"


void loop(SDL sdl);

int main( int argc, char * argv[] )
{
    try
    {
        SDL sdl( SDL_INIT_VIDEO | SDL_INIT_TIMER );
        sdl.drawMainMenu();
        MainMenu mainmenu;
        bool play = mainmenu.mainmenu(sdl);
        sdl.~SDL();

    }
    catch ( const InitError & err )
    {
        std::cerr << "Error while initializing SDL:  "
                  << err.what()
                  << std::endl;
    }

    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }


    return 1;
}




