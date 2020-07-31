#include "sprite.h"

KSprite::KSprite() {
	sprite = NULL;
	pixels = NULL;
	width = 0;
	height = 0;
	pitch = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
}
KSprite::KSprite(const char* path) {
	sprite = NULL;
	pixels = NULL;
	width = 0;
	height = 0;
	pitch = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	loadFromFile(path);
}
KSprite::KSprite(std::string path) {
	sprite = NULL;
	pixels = NULL;
	width = 0;
	height = 0;
	pitch = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	loadFromFile(path);
}
KSprite::~KSprite() {
	free();
}

bool KSprite::setBlank(int w, int h, SDL_TextureAccess access) {
	sprite = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, access, w, h);
	if (sprite == NULL) printf("Blank texture could not be created! %s\n", SDL_GetError());
	
	width = w;
	height = h;

	return sprite != NULL;
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

	SDL_LockTexture(finalTex, &formattedSurface->clip_rect, &pixels, &pitch);

	memcpy(pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

	width = formattedSurface->w;
	height = formattedSurface->h;

	Uint32* p = (Uint32*)pixels;
	int pixelCount = (pitch / 4) * height;

	Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0xFF, 0x00, 0xFF);
	Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0xFF, 0x00, 0xFF, 0x00);

	for (int i = 0; i < pixelCount; i++) {
		if (p[i] == colorKey) p[i] = transparent;
	}

	SDL_UnlockTexture(finalTex);
	pixels = NULL;

	SDL_FreeSurface(formattedSurface);
	SDL_FreeSurface(surface);

	sprite = finalTex;
	return sprite != NULL;
}
bool KSprite::loadFromFile(std::string path) {
	return loadFromFile(path.c_str());
}

void KSprite::free() {
	if (sprite != NULL) {
		SDL_DestroyTexture(sprite);
		sprite = NULL;
		pixels = NULL;
		width = NULL;
		height = NULL;
		pitch = NULL;
	}
}

void KSprite::setColor(Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetTextureColorMod(sprite, r, g, b);
	color.r = r;
	color.g = g;
	color.b = b;
}
void KSprite::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(sprite, blending);
}
void KSprite::setAlpha(Uint8 a) {
	SDL_SetTextureAlphaMod(sprite, a);
	color.a = a;
}

void KSprite::makeRenderTarget() {
	SDL_SetRenderTarget(gRenderer, sprite);
}
void KSprite::render(int x, int y, SDL_Rect* src, SDL_Rect* dest, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	
	SDL_Rect srcFinal = { 0, 0, width, height };
	SDL_Rect destFinal = { x, y, width, height };
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

	SDL_RenderCopyEx(gRenderer, sprite, &srcFinal, &destFinal, angle, center, flip);
}

int KSprite::getWidth() { return width; }
int KSprite::getHeight() { return height; }
SDL_Color KSprite::getColor() { return color; }

bool KSprite::lock() {
	if (pixels != NULL) {
		printf("Texture is already locked!\n");
		return false;
	}

	if (SDL_LockTexture(sprite, NULL, &pixels, &pitch) != 0)
	{
		printf("Texture unable to be locked!\n");
		return false;
	}

	return true;
}
bool KSprite::unlock() {
	if (pixels == NULL) {
		printf("Texture already unlocked!\n");
		return false;
	}

	SDL_UnlockTexture(sprite);
	pixels = NULL;
	pitch = 0;

	return true;
}
void* KSprite::getPixels() {
	return pixels;
}
void KSprite::copyPixels(void* pixels) {
	if (pixels != NULL) memcpy(this->pixels, pixels, pitch * height);
}
int KSprite::getPitch() {
	return pitch;
}
Uint32 KSprite::getPixel32(unsigned int x, unsigned int y) {
	Uint32* p = (Uint32*)pixels;

	return p[(y * (pitch / 4)) + x];
}

void KSprite::printNotText() {
	printf("Error: Specified sprite is not text type!\n");
}