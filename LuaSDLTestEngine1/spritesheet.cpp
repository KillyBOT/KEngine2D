#include "spritesheet.h"

KSpriteSheet::KSpriteSheet() {
	sprite = new KSprite();
	clipX = 0;
	clipY = 0;
}
KSpriteSheet::KSpriteSheet(const char* path, int clipX, int clipY) {
	sprite = new KSprite();
	clipX = 0;
	clipY = 0;
	loadFromFile(path, clipX, clipY);
	
}
KSpriteSheet::KSpriteSheet(std::string path, int clipX, int clipY) {
	sprite = new KSprite();
	clipX = 0;
	clipY = 0;
	loadFromFile(path, clipX, clipY);
}
KSpriteSheet::~KSpriteSheet() {
	delete sprite;
}

bool KSpriteSheet::loadFromFile(const char* path, int clipX, int clipY) {
	bool success = sprite->loadFromFile(path);

	for (int w = 0; w < SPRITESHEET_HORIZONTAL_MAX; w++) {
		for (int h = 0; h < SPRITESHEET_VERTICAL_MAX; h++) {
			spriteClips[w][h].x = w * clipX;
			spriteClips[w][h].y = h * clipY;
			spriteClips[w][h].w = (w + 1) * clipX;
			spriteClips[w][h].h = (h + 1) * clipY;
		}
	}

	this->clipX = clipX;
	this->clipY = clipY;

	return success;
}
bool KSpriteSheet::loadFromFile(std::string path, int clipX, int clipY) {
	return loadFromFile(path.c_str(), clipX, clipY);
}

void KSpriteSheet::renderSpritePos(int x, int y, int sx, int sy, SDL_Rect* dest, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	
	SDL_Rect destFinal = { x, y, spriteClips[sx][sy].w, spriteClips[sx][sy].h };

	if (dest != NULL) {
		destFinal.w = dest->w;
		destFinal.h = dest->h;
	}

	sprite->render(x, y, &spriteClips[sx][sy], dest, angle, center, flip);
}
void KSpriteSheet::renderSpriteNum(int x, int y, int spriteNum, SDL_Rect* dest, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	renderSpritePos(x, y, spriteNum / SPRITESHEET_HORIZONTAL_MAX, spriteNum % SPRITESHEET_HORIZONTAL_MAX, dest, angle, center, flip);
}