#include "text.h"

KText::KText()
{
	font = NULL;
	text = "Uninitialized text";
}
KText::~KText()
{
	TTF_CloseFont(font);
	font = NULL;
}

void KText::loadFont(const char* path) {

	if (fontSize < 0) return;

	font = TTF_OpenFont(path, fontSize);

	if (font == NULL) {
		fprintf(stderr,"Font from path %s could not be initialized! %s\n", path, TTF_GetError());
	}
}
void KText::loadFont(std::string path) { loadFont(path.c_str()); }
void KText::setFont(TTF_Font* font) { this->font = font; }
void KText::setFontSize(int fontSize) { this->fontSize = fontSize; }
void KText::setText(std::string text) { 
	this->text = text; 

	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, this->text.c_str(), color);
	if (textSurface == NULL) fprintf(stderr, "Text could not be rendered! %s\n", TTF_GetError());

	sprite = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	if (sprite == NULL) fprintf(stderr, "Text could not be turned into texture! %s\n", TTF_GetError());

	width = textSurface->w;
	height = textSurface->h;

	SDL_FreeSurface(textSurface);
}

TTF_Font* KText::getFont() {
	return font;
}
std::string KText::getText() {
	return text;
}
int KText::getFontSize() {
	return fontSize;
}