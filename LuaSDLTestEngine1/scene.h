#ifndef SCENE_H
#define SCENE_H

#include "globals.h"
#include "input.h"
#include "system.h"

class KScene
{
public:

	KScene();
	~KScene();

	int getSceneChange();

	virtual void load() = 0;
	virtual void update(Uint32 dt) = 0;
	virtual void draw() = 0;

	void addSystem(KSystem* system);
	KSystem* getSystem(int systemID);

	void addEntity(KEntity* entity);
	KEntity* getEntity(int entityID);

protected:
	std::vector<KSystem*> mSystems;
	std::vector<KEntity*> mEntities;
	int mChangeScene;
};

#endif

