#include "Texture.h"


 #ifdef NDEBUG
  #define PLAYERFILE "../../fonts/century.ttf"
 #else
  #define PLAYERFILE "./fonts/century.ttf"
 #endif

Texture::Texture() {

}

Texture::Texture(SDL_Renderer * renderer) {
    mRenderer = renderer;
}

Texture::Texture(std::string url, SDL_Renderer *renderer)
{
    mRenderer = renderer;
    try {
    loadTexture(url);
    } catch (std::exception &e) {
        throw std::exception();
    }

}

Texture::~Texture()
{
    SDL_DestroyTexture(mTexture);
}


void Texture::loadTexture(std::string url) {
    SDL_Surface * surface = IMG_Load(url.c_str());
    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    mWidth = surface->w;
    mHeight = surface->h;
    SDL_FreeSurface(surface);
}

void Texture::loadTextTexture(std::string text) {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
    }
    if (mFont == NULL) {
        mFont = TTF_OpenFont("../../fonts/century.ttf", 28);
    }
    SDL_Color color = {255, 0,0,255};

    if (mFont == NULL) {
    }
    SDL_Surface * textSurface = TTF_RenderText_Solid(mFont, text.c_str(),color );

    mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if (mTexture != NULL) {
        mWidth = textSurface->w;
        mHeight = textSurface->h;
    }
    SDL_FreeSurface(textSurface);
}

void Texture::render(int posX, int posY) {
    SDL_Rect dest;
    dest.x = posX;
    dest.y = posY;
    dest.w = mWidth;
    dest.h = mHeight;
    SDL_RenderCopy(mRenderer, mTexture, NULL, &dest);

}

void Texture::renderAngle(int posX, int posY, double angle) {
    SDL_Rect dest;
    dest.x = posX;
    dest.y = posY;
    dest.w = mWidth;
    dest.h = mHeight;
    SDL_RenderCopyEx(mRenderer, mTexture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);

}

void Texture::setColor(Uint8 r, Uint8 b, Uint8 g) {
    SDL_SetTextureColorMod(mTexture, r, g, b);
}

int Texture::getHeight() {
    return mHeight;
}

int Texture::getWidth() {
    return mWidth;
}
