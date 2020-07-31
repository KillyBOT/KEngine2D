#include "object.h"

KObject::KObject() {
	sprite = new KSprite();
	spriteSheet = new KSpriteSheet();

	spriteType = -1;

	clip.x = 0;
	clip.y = 0;
	clip.w = 0;
	clip.h = 0;
	clipX = 0;
	clipY = 0;
	clipW = 0;
	clipH = 0;

	angle = 0.0;
	center.x = 0;
	center.y = 0;
	flip = SDL_FLIP_NONE;
	spriteNum = 0;
	layer = 0;
}
KObject::~KObject() {
	delete sprite;
	delete spriteSheet;
}

void KObject::setClip(SDL_Rect rect) {
	clipX = rect.x;
	clipY = rect.y;
	clipW = rect.w;
	clipH = rect.h;
	clip.x = rect.x;
	clip.y = rect.y;
	clip.w = rect.w;
	clip.h = rect.h;
}
void KObject::setClip(double x, double y, double w, double h) {
	setCoords(x, y);
	setDimensions(w, h);
}
void KObject::setCoords(double x, double y) {
	setX(x);
	setY(y);
}
void KObject::addCoords(double dx, double dy) { setCoords(clipX + dx, clipY + dy); }
void KObject::setDimensions(double w, double h) {
	setW(w);
	setH(h);
}
void KObject::addDimensions(double dw, double dh) { setDimensions(clipW + dw, clipH + dh); }
void KObject::setX(double x) {
	clipX = x;
	clip.x = (int)clipX;
}
void KObject::setY(double y) {
	clipY = y;
	clip.y = (int)clipY;
}
void KObject::setW(double w) {
	clipW = w;
	clip.w = (int)clipW;
}
void KObject::setH(double h) {
	clipH = h;
	clip.h = (int)clipH;
}
void KObject::setAngle(double r) { angle = r; }
void KObject::addAngle(double dr) { angle += dr; }
void KObject::setCenter(SDL_Point p) {
	center.x = p.x;
	center.y = p.y;
}
void KObject::setCenter(int x, int y) {
	center.x = x;
	center.y = y;
}
void KObject::setFlipped(int axis, bool flip) {
	if (axis == OBJECT_FLIPAXIS_HORIZONTAL) setHorizontalFlip(flip);
	else if (axis == OBJECT_FLIPAXIS_VERTICAL) setVerticalFlip(flip);
}
void KObject::setVerticalFlip(bool flip) {
	if (flip && this->flip == SDL_FLIP_HORIZONTAL) this->flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (!flip && this->flip == (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL)) this->flip = SDL_FLIP_HORIZONTAL;
	else if (flip && this->flip == SDL_FLIP_NONE) this->flip = SDL_FLIP_VERTICAL;
	else if (!flip && this->flip == SDL_FLIP_VERTICAL) this->flip = SDL_FLIP_NONE;
}
void KObject::setHorizontalFlip(bool flip) {
	if (flip && this->flip == SDL_FLIP_VERTICAL) this->flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else if (!flip && this->flip == (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL)) this->flip = SDL_FLIP_VERTICAL;
	else if (flip && this->flip == SDL_FLIP_NONE) this->flip = SDL_FLIP_HORIZONTAL;
	else if (!flip && this->flip == SDL_FLIP_HORIZONTAL) this->flip = SDL_FLIP_NONE;
}
void KObject::setSpriteNum(int spriteNum) { this->spriteNum = spriteNum; }
void KObject::setLayer(int layer) { this->layer = layer; }

void KObject::loadTexture(const char* path) {
	sprite->loadFromFile(path);
	spriteType = OBJECT_SPRITE_SINGLE;
}
void KObject::loadTexture(std::string path) {
	sprite->loadFromFile(path);
	spriteType = OBJECT_SPRITE_SINGLE;
}
void KObject::setTexture(KSprite* sprite) {
	this->sprite = sprite;
	spriteType = OBJECT_SPRITE_SINGLE;
}

void KObject::loadSpriteSheet(const char* path, int clipX, int clipY) {
	spriteSheet->loadFromFile(path, clipX, clipY);
	spriteType = OBJECT_SPRITE_SHEET;
}
void KObject::loadSpriteSheet(std::string path, int clipX, int clipY) {
	spriteSheet->loadFromFile(path, clipX, clipY);
	spriteType = OBJECT_SPRITE_SHEET;
}
void KObject::setSpriteSheet(KSpriteSheet* spriteSheet) {
	this->spriteSheet = spriteSheet;
	spriteType = OBJECT_SPRITE_SHEET;
}

SDL_Rect KObject::getClip() { return clip; }
double KObject::getX() { return clipX; }
double KObject::getY() { return clipY; }
double KObject::getW() { return clipW; }
double KObject::getH() { return clipH; }
double KObject::getAngle() { return angle; }
SDL_Point KObject::getCenter() { return center; }
int KObject::getCenterX() { return center.x; }
int KObject::getCenterY() { return center.y; }
bool KObject::getFlipped(int axis) {
	if (axis == OBJECT_FLIPAXIS_HORIZONTAL) {
		return getFlippedVertical();
	}
	else if (axis == OBJECT_FLIPAXIS_VERTICAL) {
		return getFlippedHorizontal();
	}
}
bool KObject::getFlippedVertical() {
	return flip == (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL) || flip == SDL_FLIP_VERTICAL;
}
bool KObject::getFlippedHorizontal() {
	return flip == (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL) || flip == SDL_FLIP_HORIZONTAL;
}
int KObject::getSpriteNum() { return spriteNum; }
int KObject::getLayer() { return layer; }
KSprite* KObject::getSprite() {
	if (spriteType == OBJECT_SPRITE_SINGLE) return sprite;
	else return NULL;
}
KSpriteSheet* KObject::getSpriteSheet() {
	if (spriteType == OBJECT_SPRITE_SHEET) return spriteSheet;
	else return NULL;
}
