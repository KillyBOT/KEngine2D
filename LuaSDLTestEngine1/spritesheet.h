#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "sprite.h"

#define SPRITESHEET_VERTICAL_MAX 256
#define SPRITESHEET_HORIZONTAL_MAX 256

class KSpriteSheet
{
public:
    KSpriteSheet();
	KSpriteSheet(const char* path, int clipX, int clipY);
    KSpriteSheet(std::string path, int clipX, int clipY);
    ~KSpriteSheet();

	bool loadFromFile(const char* path, int clipX, int clipY);
	bool loadFromFile(std::string path, int clipX, int clipY);

    void renderSpritePos(int x, int y, int sx, int sy, SDL_Rect* dest = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void renderSpriteNum(int x, int y, int spriteNum, SDL_Rect* dest = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    KSprite* sprite;
    SDL_Rect spriteClips[SPRITESHEET_HORIZONTAL_MAX][SPRITESHEET_VERTICAL_MAX];
    //bool spriteInit[SPRITESHEET_HORIZONTAL_MAX][SPRITESHEET_VERTICAL_MAX];

    int clipX, clipY;
};

#endif

