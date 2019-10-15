#include "Player.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265
Player::Player(SDL_Renderer * renderer)
: mTexture(new Texture("./images/spaceship.png", renderer))
{
    mRenderer = renderer;
    mPosX = SCREEN_WIDTH / 2 - SCREEN_WIDTH / 10;
    mPosY = SCREEN_HEIGHT / 2 - mTexture->getHeight() / 2;
    topLeftX = mPosX;
    topLeftY = mPosY;
    mCollision.x = SCREEN_WIDTH / 2 - SCREEN_WIDTH / 10 - 3;
    mCollision.y = SCREEN_HEIGHT / 2 - mTexture->getHeight() / 2;
    mCollision.w = mTexture->getWidth() - 3;
    mCollision.y = mTexture->getHeight();
}

Player::~Player()
{
    //dtor
}

void Player::calculateCollisionBox() {
    int r = mTexture->getWidth() / 2;
    int heightDivided = mTexture->getHeight() / 2;
    int centerX, centerY;
    double angle = mCurrentAngle;

    double topLeftAngle =  atan2(r , heightDivided) * 180 / PI;
    topLeftX = mPosX + cos(angle * PI / 180.0) * r  ;
    topLeftY = mPosY +  sin(angle  * PI / 180.0) * heightDivided + heightDivided;
    centerX = mPosX + r+ cos(topLeftAngle* PI / 180.0);
    centerY = mPosY + heightDivided + sin(topLeftAngle * PI / 180.0);

    double x1 = centerX - (r-2) * cos(angle * PI / 180.0);
    double y1 = centerY - r* sin(angle * PI / 180.0);
    double x2X = centerX+ (r-2) * cos(angle * PI / 180.0);
    double  y2Y =  centerY+ r * sin(angle * PI / 180.0);
    double topX = centerX + heightDivided * sin(angle * PI / 180.0);
    double topY = centerY - heightDivided * cos(angle * PI / 180.0);
    double bottomX = centerX - heightDivided * sin(angle * PI / 180.0);
    double bottomY = centerY + heightDivided * cos(angle * PI / 180.0);

    mLeftPoint.x = x1;
    mLeftPoint.y = y1;
    mTopPoint = {topX, topY};
    mRightPoint = {x2X, y2Y};
    mBottomPoint = {bottomX, bottomY};
/*
    SDL_SetRenderDrawColor(mRenderer, 255, 0,0,255);
    SDL_RenderDrawLineF(mRenderer, x2X, y2Y, topX, topY);
    SDL_RenderDrawLineF(mRenderer, x1, y1, topX, topY);
    SDL_RenderDrawLineF(mRenderer, x2X, y2Y, bottomX, bottomY);
    SDL_RenderDrawLineF(mRenderer, x1, y1, bottomX, bottomY);
    */
}

bool Player::checkCollision(SDL_Rect rect) {

    Line topToLeft = {mTopPoint, mLeftPoint};
    Line topToRight = {mTopPoint, mRightPoint};
    Line bottomToLeft = {mBottomPoint, mLeftPoint};
    Line bottomToRight = {mBottomPoint, mRightPoint};

    int topLX, topLY, topRX, topRY, bottomLX, bottomLY, bottomRX, bottomRY;
    Point topLeft = {rect.x, rect.y};
    Point topRight = {rect.x + rect.w, rect.y};
    Point bottomLeft = {rect.x, rect.y + rect.h};
    Point bottomRight = {rect.x + rect.w , rect.y + rect.h};

    topLX = rect.x;
    topLY = rect.y;
    topRX = rect.x + rect.w;
    topRY = rect.y;
    bottomLX = rect.x;
    bottomLY = rect.y + rect.h;
    bottomRX = rect.x + rect.w;
    bottomRY = rect.y + rect.h ;


    /*
    SDL_RenderDrawLineF(mRenderer, topLX, topLY, topRX,topRY);
    SDL_RenderDrawLineF(mRenderer, topLX, topLY, bottomLX,bottomLY);
    SDL_RenderDrawLineF(mRenderer, bottomRX, bottomRY, topRX,topRY);
    SDL_RenderDrawLineF(mRenderer, bottomRX, bottomRY, bottomLX,bottomLY);
    */
    Line rectTopLeftToRight = {topLeft, topRight};
    Line rectTopLeftToBottom = {topLeft, bottomLeft};
    Line rectTopRightToBottom = {topRight, bottomRight};
    Line rectBottomLeftToRight = {bottomLeft, bottomRight};
    if (mLeftPoint.x > topRight.x || mRightPoint.x < topLeft.x) {
        return false;
    }
    if ((mLeftPoint.y < topLeft.y && mBottomPoint.y < topLeft.y && mRightPoint.y < topLeft.y) ) {
            return false;
    }
    else if (
        (mLeftPoint.y > bottomLeft.y && mTopPoint.y > bottomLeft.y && mRightPoint.y > bottomLeft.y)) {
            return false;
    }

    Line playerLines[4] = {topToLeft, topToRight, bottomToLeft, bottomToRight};
    Line rectLines [4] = {rectTopLeftToRight, rectTopLeftToBottom, rectTopRightToBottom, rectBottomLeftToRight};

    for(int i = 0; i < 4; i++) {
        for (int o = 0; o < 4; o++) {
            if (segmentIntersect(playerLines[i], rectLines[o])) {
                return true;
            }
        }
    }

    return false;
}

bool Player::segmentIntersect(Line line1, Line line2) {
    double A1 = line1.p1.y - line1.p0.y,
            B1 = line1.p0.x - line1.p1.x,
            C1 = A1 * line1.p0.x + B1 * line1.p0.y,
            A2 = line2.p1.y - line2.p0.y,
            B2 = line2.p0.x - line2.p1.x,
            C2 = A2 * line2.p0.x + B2 * line2.p0.y,
            denominator = A1* B2 - A2* B1;

        if (denominator == 0) {
            return false;
        }
        double intersectX = (B2 * C1 - B1 * C2) / denominator,
                intersectY = (A1 * C2 - A2 * C1) / denominator,
                rx0 = (intersectX - line1.p0.x) / (line1.p1.x - line1.p0.x),
                ry0 = (intersectY - line1.p0.y) / (line1.p1.y - line1.p0.y),
                rx1 = (intersectX - line2.p0.x) / (line2.p1.x - line2.p0.x),
                ry1 = (intersectY - line2.p0.y) / (line2.p1.y - line2.p0.y);


        if (((rx0 >= 0 && rx0 <= 1) || (ry0 >= 0 && ry0 <= 1)) && ((rx1 >= 0 && rx1 <= 1) || (ry1 >= 0 && ry1 <= 1))) {
                SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
                SDL_RenderDrawPoint(mRenderer, intersectX, intersectY);
            return true;
        }
        return false;
}

void Player::moveUp() {
    mCurrentGravity = 0;
    mCurrentVel -= 14;
    mCurrentAngle -= 50;
    if (mCurrentAngle < MAX_ANGLE * -1) {
        mCurrentAngle = MAX_ANGLE * -1;
    }
    if (mCurrentVel < MAX_UPVEL) {
      mCurrentVel = MAX_UPVEL;
    }
    mPosY += mCurrentVel;
    mCollision.y = mPosY;

}

void Player::render() {
    mTexture->renderAngle(mPosX, mPosY, mCurrentAngle);
}

void Player::gravity() {
    mCurrentGravity += 0.05;
    mCurrentAngle += 2;
    if (mCurrentGravity > MAX_GRAVITY) {
        mCurrentGravity = MAX_GRAVITY;
    }
    if (mCurrentAngle > MAX_ANGLE) {
        mCurrentAngle = MAX_ANGLE;
    }
    mCurrentVel += mCurrentGravity;
    mPosY += mCurrentVel;

    mCollision.y = mPosY;
}

bool Player::checkBounds() {
    if (mTopPoint.y > SCREEN_HEIGHT && mRightPoint.y > SCREEN_HEIGHT && mLeftPoint.y > SCREEN_HEIGHT) {
        return true;
    }
    else if (mBottomPoint.y < 0 && mRightPoint.y < 0 && mLeftPoint.y < 0) {
        return true;
    }
    return false;
}

void Player::resetPos(){
    mPosX = SCREEN_WIDTH / 2 - SCREEN_WIDTH / 10;
    mPosY = SCREEN_HEIGHT / 2 - mTexture->getHeight() / 2;
    mCurrentGravity = 0;
    mCurrentVel = 0;
    mCurrentAngle = 0;
}
