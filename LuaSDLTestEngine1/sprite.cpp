#include "sprite.h"

KSprite::KSprite() {
	mSprite = NULL;
	mPixels = NULL;
	mWidth = 0;
	mHeight = 0;
	mPitch = 0;
	mColor.r = 0;
	mColor.g = 0;
	mColor.b = 0;
	mColor.a = 0;
}
KSprite::KSprite(const char* path) {
	mSprite = NULL;
	mPixels = NULL;
	mWidth = 0;
	mHeight = 0;
	mPitch = 0;
	mColor.r = 0;
	mColor.g = 0;
	mColor.b = 0;
	mColor.a = 0;
	loadFromFile(path);
}
KSprite::KSprite(std::string path) {
	mSprite = NULL;
	mPixels = NULL;
	mWidth = 0;
	mHeight = 0;
	mPitch = 0;
	mColor.r = 0;
	mColor.g = 0;
	mColor.b = 0;
	mColor.a = 0;
	loadFromFile(path);
}
KSprite::~KSprite() {
	free();
}

bool KSprite::setBlank(int w, int h, SDL_TextureAccess access) {
	mSprite = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, access, w, h);
	if (mSprite == NULL) printf("Blank texture could not be created! %s\n", SDL_GetError());
	
	mWidth = w;
	mHeight = h;

	return mSprite != NULL;
}

bool KSprite::loadFromFile(const char* path) {
	free();

	SDL_Texture* finalTex = NULL;
	SDL_Surface* surface = NULL;
	SDL_Surface* formattedSurface = NULL;

	surface = IMG_Load(path);
	if (surface == NULL) {
		printf("Image %s could not be loaded! %s\n", path, SDL_GetError());
		return false;
	}

	formattedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
	if (formattedSurface == NULL) {
		printf("Image %s could not be formatted correctly! %s\n", path, SDL_GetError());
		return false;
	}

	finalTex = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
	if (finalTex == NULL) {
		printf("Blank texture could not be created! %s\n", SDL_GetError());
		return false;
	}

	SDL_SetTextureBlendMode(finalTex, SDL_BLENDMODE_BLEND);

	SDL_LockTexture(finalTex, &formattedSurface->clip_rect, &mPixels, &mPitch);

	memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

	mWidth = formattedSurface->w;
	mHeight = formattedSurface->h;

	Uint32* p = (Uint32*)mPixels;
	int pixelCount = (mPitch / 4) * mHeight;

	Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0xFF, 0x00, 0xFF);
	Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0xFF, 0x00, 0xFF, 0x00);

	for (int i = 0; i < pixelCount; i++) {
		if (p[i] == colorKey) p[i] = transparent;
	}

	SDL_UnlockTexture(finalTex);
	mPixels = NULL;

	SDL_FreeSurface(formattedSurface);
	SDL_FreeSurface(surface);

	mSprite = finalTex;
	return mSprite != NULL;
}
bool KSprite::loadFromFile(std::string path) {
	return loadFromFile(path.c_str());
}

void KSprite::free() {
	if (mSprite != NULL) {
		SDL_DestroyTexture(mSprite);
		mSprite = NULL;
		mPixels = NULL;
		mWidth = NULL;
		mHeight = NULL;
		mPitch = NULL;
	}
}

void KSprite::setColor(Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetTextureColorMod(mSprite, r, g, b);
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;
}
void KSprite::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(mSprite, blending);
}
void KSprite::setAlpha(Uint8 a) {
	SDL_SetTextureAlphaMod(mSprite, a);
	mColor.a = a;
}

void KSprite::makeRenderTarget() {
	SDL_SetRenderTarget(gRenderer, mSprite);
}
void KSprite::render(int x, int y, SDL_Rect* src, SDL_Rect* dest, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	
	SDL_Rect srcFinal = { 0, 0, mWidth, mHeight };
	SDL_Rect destFinal = { x, y, mWidth, mHeight };
	if(src != NULL) {
		srcFinal.x = src->x;
		srcFinal.y = src->y;
		srcFinal.w = src->w;
		srcFinal.h = src->h;
	}

	if(dest != NULL){
		destFinal.w = dest->w;
		destFinal.h = dest->h;
	}

	SDL_RenderCopyEx(gRenderer, mSprite, &srcFinal, &destFinal, angle, center, flip);
}

int KSprite::getWidth() { return mWidth; }
int KSprite::getHeight() { return mHeight; }
SDL_Color KSprite::getColor() { return mColor; }

bool KSprite::lock() {
	if (mPixels != NULL) {
		printf("Texture is already locked!\n");
		return false;
	}

	if (SDL_LockTexture(mSprite, NULL, &mPixels, &mPitch) != 0)
	{
		printf("Texture unable to be locked!\n");
		return false;
	}

	return true;
}
bool KSprite::unlock() {
	if (mPixels == NULL) {
		printf("Texture already unlocked!\n");
		return false;
	}

	SDL_UnlockTexture(mSprite);
	mPixels = NULL;
	mPitch = 0;

	return true;
}
void* KSprite::getPixels() {
	return mPixels;
}
void KSprite::copyPixels(void* pixels) {
	if (pixels != NULL) memcpy(mPixels, pixels, mPitch * mHeight);
}
int KSprite::getPitch() {
	return mPitch;
}
Uint32 KSprite::getPixel32(unsigned int x, unsigned int y) {
	Uint32* p = (Uint32*)mPixels;

	return p[(y * (mPitch / 4)) + x];
}

void KSprite::printNotText() {
	printf("Error: Specified sprite is not text type!\n");
}