#ifndef SPRITE_H
#define SPRITE_H

#include "globals.h"
#include <iterator>
#include <map>

//#define SPRITES_MAX 65536

class KSprite
{
public:

	KSprite();
	KSprite(const char* path);
	KSprite(std::string path);
	~KSprite();

	bool setBlank(int w, int h, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING);

	bool loadFromFile(const char* path);
	bool loadFromFile(std::string path);

	void free();

	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 a);
	
	void makeRenderTarget();
	void render(int x, int y, SDL_Rect* src = NULL, SDL_Rect* dest = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();
	SDL_Color getColor();

	bool lock();
	bool unlock();
	void* getPixels();
	void copyPixels(void* pixels);
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);

	virtual void loadFont(const char* path) { printNotText(); }
	virtual void loadFont(std::string path) { printNotText(); }
	virtual void setFont(TTF_Font* font) { printNotText(); }
	virtual void setFontSize(int fontSize) { printNotText(); }
	virtual void setText(std::string text) { printNotText(); }

	virtual TTF_Font* getFont() { return NULL; }
	virtual std::string getText() { return ""; }
	virtual int getFontSize() { return -1; }

protected:
	SDL_Texture* mSprite;
	void* mPixels;
	
	int mPitch;
	int mWidth;
	int mHeight;
	SDL_Color mColor;
private:
	void printNotText();
};

#endif

