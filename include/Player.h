#ifndef PLAYER_H
#define PLAYER_H
#include "Texture.h"
typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point p0;
    Point p1;
} Line;
class Player
{
    public:
        Player(SDL_Renderer * renderer);
        virtual ~Player();
        void render();
        void moveUp();
        void gravity();
        bool checkCollision(SDL_Rect  rect);
        void calculateCollisionBox();
        bool segmentIntersect(Line, Line);
        void resetPos();
        bool checkBounds();
    protected:

    private:
        SDL_Renderer * mRenderer;
        Texture * mTexture;
        int mPosX, mPosY;
        int topLeftX, topLeftY;
        const int MAX_UPVEL = -10;
        float mCurrentVel = 0;
        float mCurrentGravity = 0;
        static constexpr float MAX_GRAVITY = 0.8;
        static const int SCREEN_WIDTH = 640;
        static const int SCREEN_HEIGHT = 480;
        int mCurrentAngle = 0;
        const int MAX_ANGLE= 80;
        SDL_Rect mCollision;
        Point mLeftPoint;
        Point mTopPoint;
        Point mRightPoint;
        Point mBottomPoint;
};

#endif // PLAYER_H
