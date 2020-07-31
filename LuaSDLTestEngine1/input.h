#ifndef INPUT_H
#define INPUT_H

#include "globals.h"

class KInputHandler
{
public:

	KInputHandler();
	~KInputHandler();

	void pollInputs();
	bool hasQuit();

	int getMouseX();
	int getMouseY();
	int getPrevMouseX();
	int getPrevMouseY();
	int getMouseDX();
	int getMouseDY();
	int getMouseState(int mouseButton);

	int getKeyState(SDL_Scancode scancode);
private:
	SDL_Event e;

	bool quit;

	int mouseX, mouseY;
	int prevMouseX, prevMouseY;
	bool mouseState[3];
	bool prevMouseState[3];

	const Uint8* keyboardState;
	Uint8* prevKeyboardState;
	bool keys[512];
	bool prevKeys[512];

	Uint32 eventType;
};

#endif

