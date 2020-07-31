#ifndef OBJECT_H
#define OBJECT_H

#include "globals.h"
#include "input.h"
#include "sprite.h"
#include "spritesheet.h"

class KObject
{
public:
	KObject();
	~KObject();

	void setClip(SDL_Rect rect);
	void setClip(double x, double y, double w, double h);
	void setCoords(double x, double y);
	void addCoords(double dx, double dy);
	void setDimensions(double w, double h);
	void addDimensions(double dw, double dh);
	void setX(double x);
	void setY(double y);
	void setW(double w);
	void setH(double h);
	void setAngle(double r);
	void addAngle(double dr);
	void setCenter(SDL_Point p);
	void setCenter(int x, int y);
	void setFlipped(int axis, bool flip);
	void setVerticalFlip(bool flip);
	void setHorizontalFlip(bool flip);
	void setSpriteNum(int spriteNum);
	void setLayer(int layer);

	void loadTexture(const char* path);
	void loadTexture(std::string path);
	void setTexture(KSprite* sprite);

	void loadSpriteSheet(const char* path, int clipX, int clipY);
	void loadSpriteSheet(std::string path, int clipX, int clipY);
	void setSpriteSheet(KSpriteSheet* spriteSheet);

	SDL_Rect getClip();
	double getX();
	double getY();
	double getW();
	double getH();
	double getAngle();
	SDL_Point getCenter();
	int getCenterX();
	int getCenterY();
	bool getFlipped(int axis);
	bool getFlippedVertical();
	bool getFlippedHorizontal();
	int getSpriteNum();
	int getLayer();
	KSprite* getSprite();
	KSpriteSheet* getSpriteSheet();

	virtual void handleInput(KInputHandler input) { return; }
	virtual void update(double dt) { return; }
	virtual void draw(double dt) {
		switch (spriteType) {
		case OBJECT_SPRITE_SINGLE:
			sprite->render(clip.x, clip.y, NULL, &clip, angle, &center, flip);
			break;
		case OBJECT_SPRITE_SHEET:
			spriteSheet->renderSpriteNum(clip.x, clip.y, spriteNum, &clip, angle, &center, flip);
		default:
			break;
		}
	}
protected:
	KSprite* sprite;
	KSpriteSheet* spriteSheet;

	SDL_Rect clip;
	double clipX, clipY, clipW, clipH;
	int spriteType;
	double angle;
	SDL_Point center;
	SDL_RendererFlip flip;
	int spriteNum;
	int layer;
};
#endif
