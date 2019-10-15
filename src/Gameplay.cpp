#include "Gameplay.h"



Gameplay::Gameplay(SDL_Renderer * renderer)
: mPlayer(new Player(renderer)), mBG(new Texture("./images/bg.png",renderer)),
mBG2(new Texture("./images/bg.png",renderer))
{
    mRenderer = renderer;
}

Gameplay::~Gameplay()
{
    delete mBG;
    delete mBG2;
    delete mScoreTexture;
}

void Gameplay::play(SDL sdl, SDL_Renderer * renderer) {
    gameplayLoop(sdl);
}

void Gameplay::gameplayLoop(SDL sdl) {
    bool quit = false;
    SDL_Event e;
    Timer timer;
    timer.start();
    Timer capTimer;
    int frames = 0;
    int *framePointer = &frames;
    int offset = 0;
    bool upPress = false;
    SDL_Rect testRect;
    while (!quit) {
        capTimer.start();

        while (SDL_PollEvent(&e)) {
            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            switch(e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if (currentKeyStates[SDL_SCANCODE_W] && !upPress) {
                    mPlayer->moveUp();
                    upPress = true;
                }
                break;
            case SDL_KEYUP:
                    if (e.key.keysym.sym == SDLK_w) {
                    upPress = false;
                    }
                break;
            }
        }
        sdl.clearScreen();
        mBG->render(offset, 0);
        mBG2->render(offset + mBG2->getWidth(), 0);
        mPlayer->render();
        mPlayer->calculateCollisionBox();
        moveMeteors();
        mPlayer->gravity();
        if (mScoreTexture != NULL)
            mScoreTexture->render(0,0);

        spawnMeteor(timer);
        sdl.render();
        if (checkMeteorCollision() || mPlayer->checkBounds()) {
            Texture *gameOver = new Texture("./images/gameovar.png", mRenderer);
            gameOver->render(0,0);
            sdl.render();
            bool replay = gameoverLoop();
            if (replay) {
                upPress = false;
                capTimer.stop();
                timer.stop();
                timer.start();
                delete gameOver;
                resetGame();
            }else {
                quit = true;
            }
        }
        offset--;
        if (offset < mBG->getWidth() * -1) {
            offset = 0;
        }
         limitFPS(framePointer, timer, capTimer);
    }
}
void Gameplay::limitFPS(int* frames, Timer timer, Timer capTimer) {
    float avgFPS = *frames / ( timer.getTicks() / 1000.f );

    if (avgFPS > 200000) {
        avgFPS = 0;
    }
    *frames = *frames +1;
    int frameTicks = capTimer.getTicks();

    if( frameTicks < SCREEN_TICKS_PER_FRAME )
    {
        SDL_Delay( SCREEN_TICKS_PER_FRAME  - frameTicks );
    }
}

void Gameplay::renderGameplay() {

}

void Gameplay::updateScore() {
    if (mScoreTexture == NULL) {
         mScoreTexture = new Texture(mRenderer);
    }
    mScoreTexture->loadTextTexture(std::to_string(mScore));
}

void Gameplay::resetGame() {
    mPlayer->resetPos();
    mScore = 0;
    mMeteorVector.clear();
    if (mScoreTexture != NULL)
        mScoreTexture->loadTextTexture(std::to_string(mScore));
}

bool Gameplay::gameoverLoop() {
    bool quit2 = false;
    SDL_Event e;
    while (!quit2) {
        while (SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    quit2 = true;
                    return false;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_r) {
                        return true;
                    }
                    break;
            }
        }
    }

}

bool Gameplay::checkMeteorCollision() {
     for(std::vector<Meteor*>::iterator it = mMeteorVector.begin(); it != mMeteorVector.end(); ++it) {
           if(mPlayer->checkCollision((*it)->getCollision())) {
                return true;
           }
        }
        return false;
}

void Gameplay::moveMeteors() {
   for(std::vector<Meteor*>::iterator it = mMeteorVector.begin(); it != mMeteorVector.end(); ) {
            if((*it)->checkIfOverMap()) {
                mScore++;
                updateScore();
                delete (*it);
                it = mMeteorVector.erase(it);
            }
            else {
                (*it)->move();
                (*it)->render();
                ++it;
            }
        }

}

void Gameplay::spawnMeteor(Timer timer) {
    int sec = timer.getTicks() / 100;
        if(sec % 10 == 0 ) {
                int ifOne = rand() % 4;
            if (ifOne == 1) {
                int random = rand() % 200;
                Meteor *meteor = new Meteor(mRenderer, 640 + random, rand()% 450);
                mMeteorVector.push_back(meteor);
            }
        }

}
