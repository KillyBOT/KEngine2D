#ifndef TEXT_H
#define TEXT_H

#include "globals.h"
#include "sprite.h"

class KText :
    public KSprite
{
public:
    KText();
    ~KText();

    void loadFont(const char* path);
    void loadFont(std::string path);
    void setFont(TTF_Font* font);
    void setFontSize(int fontSize);
    void setText(std::string text);

    TTF_Font* getFont();
    std::string getText();
    int getFontSize();
private:
    TTF_Font *font;
    std::string text;
    int fontSize;
};

#endif
