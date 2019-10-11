#include "Meteor.h"
#include <iostream>
Meteor::Meteor(SDL_Renderer * renderer, int posX, int posY)
: mTexture(new Texture("C:/Users/Miikka/Desktop/c++/SpaceGame/images/meteor.png", renderer))
{
    mRenderer = renderer;
    mWidth = mTexture->getWidth();
    mHeight = mTexture->getHeight();
    mCollision.x = posX + 2;
    mCollision.y = posY + 2;
    mCollision.w = 60;
    mCollision.h = 60;
    mPosX = posX;
    mPosY = posY;
}

Meteor::~Meteor()
{
    mTexture->~Texture();

}

void Meteor::move() {
    mPosX -= speed;
    mCollision.x = mPosX + 2;
    mCollision.y = mPosY + 2;
}

void Meteor::render() {
    mTexture->render(mPosX, mPosY);
}

bool Meteor::checkIfOverMap() {
     if (mPosX < -64) {
         return true;
    }
    return false;
}

SDL_Rect Meteor::getCollision() {
    return mCollision;
}
