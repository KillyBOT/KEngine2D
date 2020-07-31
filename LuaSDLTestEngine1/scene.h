#ifndef SCENE_H
#define SCENE_H

#include "globals.h"
#include "sprite.h"
#include "spritesheet.h"
#include "input.h"

class KScene
{
public:

	KScene();
	~KScene();

	void addSprite(KSprite* sprite);
	KSprite* getSprite(int spriteNum);

	void addSpriteSheet(KSpriteSheet* spriteSheet);
	KSpriteSheet* getSpriteSheet(int spriteSheetNum);

	int getSceneChange();

	virtual void load() = 0;
	virtual void processInput(KInputHandler input, Uint32 dt) = 0;
	virtual void update(Uint32 dt) = 0;
	virtual void draw() = 0;

protected:
	std::vector<KSprite*> sprites;
	std::vector<KSpriteSheet*> spriteSheets;
	KInputHandler input;
	int changeScene;
};

#endif

