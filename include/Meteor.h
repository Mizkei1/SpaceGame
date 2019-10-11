#ifndef METEOR_H
#define METEOR_H
#include "Texture.h"

class Meteor
{
    public:
        Meteor(SDL_Renderer * renderer, int posX, int posY);
        virtual ~Meteor();
        void move();
        void render();
        bool checkIfOverMap();
        SDL_Rect getCollision();
    protected:

    private:
        Texture * mTexture;
        SDL_Rect mCollision;
        int mWidth, mHeight;
        int mPosX, mPosY;
        SDL_Renderer * mRenderer;
        const int speed = 3;
};

#endif // METEOR_H
