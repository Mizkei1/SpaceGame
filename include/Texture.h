#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <SDL2/SDL_image.h>
#include <sys/types.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
class Texture
{
    public:
        Texture(std::string url, SDL_Renderer* renderer);
        Texture(SDL_Renderer*);
        Texture();
        virtual ~Texture();
        void loadTexture(std::string url);
        void loadTextTexture(std::string);
        void render(int posX, int posY);
        int getWidth();
        int getHeight();
        void setColor(Uint8 r, Uint8 b, Uint8 g);
        void renderAngle(int posX, int posY, double angle);

    protected:

    private:
        SDL_Texture * mTexture = NULL;
        TTF_Font * mFont = NULL;
        int mWidth, mHeight;
        SDL_Renderer * mRenderer;
};

#endif // TEXTURE_H

