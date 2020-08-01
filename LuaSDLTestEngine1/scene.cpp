#include "scene.h"

using namespace std;

KScene::KScene() {
	mChangeScene = -1;
}
KScene::~KScene() {

	int mSystemsSize = mSystems.size();

	for (int n = 0; n < mSystemsSize; n++) {
		delete mSystems.front();
		mSystems.erase(mSystems.begin());
	}

	int mEntitiesSize = mEntities.size();

	for (int n = 0; n < mEntitiesSize; n++) {
		delete mEntities.front();
		mEntities.erase(mEntities.begin());
	}
}

int KScene::getSceneChange() { return mChangeScene; }

void KScene::addSystem(KSystem* system) { mSystems.push_back(system); }
KSystem* KScene::getSystem(int systemID) {
	for (vector<KSystem*>::iterator it = mSystems.begin(); it != mSystems.end(); it++) {
		if ((*it)->getID() == systemID) return (*it);
	}

	return NULL;
}

void KScene::addEntity(KEntity* entity) { mEntities.push_back(entity); }
KEntity* KScene::getEntity(int entityID) {
	for (vector<KEntity*>::iterator it = mEntities.begin(); it != mEntities.end(); it++) {
		if ((*it)->getID() == entityID) return (*it);
	}

	return NULL;
}