#ifndef GAME_H
#define GAME_H

#include <thread>

#include "globals.h"

#include "scene.h"
#include "input.h"

class KGame
{
public:
	KGame();
	~KGame();

	void start();
	void mainloop();
	void load();
	void getInput(Uint32 dt);
	void update(Uint32 dt);
	void draw();

	void addScene(KScene* scene);
	void setCurrentScene(int sceneNum);
	
	KScene* getCurrentScene();

private:
	std::vector<KScene *> scenes;
	KScene* currentScene;
	KInputHandler input;

	bool running;
};
#endif
