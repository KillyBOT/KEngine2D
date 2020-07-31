#include "scene.h"

KScene::KScene() {
	changeScene = -1;
}
KScene::~KScene() {
	KSprite* spriteObj;
	KSpriteSheet* spriteSheetObj;

	for (std::vector<KSprite*>::iterator sprite = sprites.begin(); sprite != sprites.end(); ++sprite) {
		spriteObj = (*sprite);
		delete spriteObj;
	}

	for (std::vector<KSpriteSheet*>::iterator spriteSheet = spriteSheets.begin(); spriteSheet != spriteSheets.end(); ++spriteSheet) {
		spriteSheetObj = *spriteSheet;
		delete spriteSheetObj;
	}
}

void KScene::addSprite(KSprite* sprite) { sprites.push_back(sprite); }
KSprite* KScene::getSprite(int spriteNum) { if (spriteNum >= 0 && spriteNum < sprites.size()) return sprites[spriteNum]; }

void KScene::addSpriteSheet(KSpriteSheet* spriteSheet) { spriteSheets.push_back(spriteSheet); }
KSpriteSheet* KScene::getSpriteSheet(int spriteSheetNum) { if (spriteSheetNum >= 0 && spriteSheetNum < spriteSheets.size()) return spriteSheets[spriteSheetNum]; }

int KScene::getSceneChange() { return changeScene; }