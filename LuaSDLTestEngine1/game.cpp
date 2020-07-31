#include "game.h"

KGame::KGame() {
	running = true;
}

KGame::~KGame() {
	int sceneNum = scenes.size();
	for (int n = 0; n < sceneNum; n++) {
		delete scenes.front();
		scenes.erase(scenes.begin());
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

		getInput(dTime);

		if (input.hasQuit()) running = false;

		update(dTime);
		draw();
	}
}
void KGame::load() {
	
	KScene* sceneObj;

	for (std::vector<KScene*>::iterator scene = scenes.begin(); scene != scenes.end(); ++scene) {
		(*scene)->load();
	}
}
void KGame::getInput(Uint32 dt) {
	input.pollInputs();
}
void KGame::update(Uint32 dt) {
	currentScene->update(dt);
}
void KGame::draw() {
	currentScene->draw();
}

void KGame::addScene(KScene* scene) {
	scenes.push_back(scene);
}
void KGame::setCurrentScene(int sceneNum) {
	if (sceneNum <= 0 && sceneNum < scenes.size()) {
		currentScene = scenes[sceneNum];
	}
}

KScene* KGame::getCurrentScene() { return currentScene; }