#include "game.h"

KGame::KGame() {
	running = true;
}

KGame::~KGame() {
	int sceneNum = mScenes.size();
	for (int n = 0; n < sceneNum; n++) {
		delete mScenes.front();
		mScenes.erase(mScenes.begin());
	}
}

void KGame::start() {

	printf("Starting main game loop...\n");

	std::thread gameThread(&KGame::mainloop, this);

	gameThread.join();
}
void KGame::mainloop() {
	load();

	Uint32 time = 0;
	Uint32 prevTime = 0;
	Uint32 dTime = 0;

	while (running = true) {
		prevTime = time;
		time = SDL_GetTicks();
		dTime = time - prevTime;

		//getInput(dTime);

		update(dTime);
		draw();
	}
}
void KGame::load() {
	
	KScene* sceneObj;

	for (std::vector<KScene*>::iterator scene = mScenes.begin(); scene != mScenes.end(); ++scene) {
		(*scene)->load();
	}
}
void KGame::getInput(Uint32 dt) {
	//input.pollInputs();
}
void KGame::update(Uint32 dt) {
	mCurrentScene->update(dt);
}
void KGame::draw() {
	mCurrentScene->draw();
}

void KGame::addScene(KScene* scene) {
	mScenes.push_back(scene);
}
void KGame::setCurrentScene(int sceneNum) {
	if (sceneNum <= 0 && sceneNum < mScenes.size()) {
		mCurrentScene = mScenes[sceneNum];
	}
}

KScene* KGame::getCurrentScene() { return mCurrentScene; }