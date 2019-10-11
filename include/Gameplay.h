#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include "Texture.h"
#include "SDL.h"
#include "Player.h"
#include "Timer.h"
#include "Meteor.h"
#include <vector>
#include <SDL2/SDL_ttf.h>

class Gameplay
{
    public:
        Gameplay(SDL_Renderer *renderer);
        virtual ~Gameplay();
        void play(SDL sdl, SDL_Renderer * renderer);
        void moveMeteors();
        bool checkMeteorCollision();
        void gameplayLoop(SDL sdl);
        bool gameoverLoop();
        void resetGame();
        void renderGameplay();
        void limitFPS(int *, Timer, Timer );
        void spawnMeteor(Timer);
        void updateScore();
    protected:

    private:
        Player *mPlayer;
        SDL_Renderer* mRenderer;
        Texture * mBG;
        Texture * mBG2;
        Texture * mScoreTexture = NULL;
        static const int FPS = 60;
        int mScore = 0;
        const int SCREEN_TICKS_PER_FRAME = 1000 / FPS;
        const int LEVEL_WIDTH = 1280;
        const int LEVEL_HEIGHT = 960;

        std::vector<Meteor*> mMeteorVector;

};

#endif // GAMEPLAY_H
