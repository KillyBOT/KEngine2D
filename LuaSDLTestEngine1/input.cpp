#include "input.h"

KInputHandler::KInputHandler() {

	keyboardState = SDL_GetKeyboardState(NULL);
	prevKeyboardState = (Uint8*)malloc(sizeof(Uint8) * sizeof(keyboardState));


	for (int n = 0; n < 512; n++) {
		keys[n] = false;
		prevKeys[n] = false;
	}

	for (int n = 0; n < 3; n++) {
		mouseState[n] = false;
		prevMouseState[n] = false;
	}

	mouseX = -1;
	mouseY = -1;
	prevMouseX = -1;
	prevMouseY = -1;

	quit = false;
}

KInputHandler::~KInputHandler() {
	free(prevKeyboardState);
}

void KInputHandler::pollInputs() {

	memcpy(prevKeyboardState, keyboardState, sizeof(keyboardState));

	for (int n = 0; n < 3; n++) {
		prevMouseState[n] = mouseState[n];
	}

	prevMouseX = mouseX;
	prevMouseY = mouseY;

	while (!SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	Uint32 mouseStateMask = SDL_GetMouseState(&mouseX, &mouseY);

	if (mouseStateMask & SDL_BUTTON(SDL_BUTTON_LEFT)) mouseState[MOUSE_BUTTON_LEFT] = true;
	else mouseState[MOUSE_BUTTON_LEFT] = false;
	if (mouseStateMask & SDL_BUTTON(SDL_BUTTON_RIGHT)) mouseState[MOUSE_BUTTON_RIGHT] = true;
	else mouseState[MOUSE_BUTTON_RIGHT] = false;
	if (mouseStateMask & SDL_BUTTON(SDL_BUTTON_MIDDLE)) mouseState[MOUSE_BUTTON_MIDDLE] = true;
	else mouseState[MOUSE_BUTTON_MIDDLE] = false;
}
bool KInputHandler::hasQuit() {
	return quit;
}

int KInputHandler::getMouseX() {
	return mouseX;
}
int KInputHandler::getMouseY() {
	return mouseY;
}
int KInputHandler::getPrevMouseX() {
	return prevMouseX;
}
int KInputHandler::getPrevMouseY() {
	return prevMouseY;
}
int KInputHandler::getMouseDX() {
	return mouseX - prevMouseX;
}
int KInputHandler::getMouseDY() {
	return mouseY - prevMouseY;
}
int KInputHandler::getMouseState(int mouseButton) {
	if (mouseState[mouseButton] && prevMouseState[mouseButton]) return INPUT_STATE_DOWN;
	else if (mouseState[mouseButton] && !prevMouseState[mouseButton]) return INPUT_STATE_PRESSED;
	else if (!mouseState[mouseButton] && prevMouseState[mouseButton]) return INPUT_STATE_RELEASED;
	else if (!mouseState[mouseButton] && !prevMouseState[mouseButton]) return INPUT_STATE_UP;
}

int KInputHandler::getKeyState(SDL_Scancode scancode) {
	if (keyboardState[scancode] && prevKeyboardState[scancode]) return INPUT_STATE_DOWN;
	else if (keyboardState[scancode] && !prevKeyboardState[scancode]) return INPUT_STATE_PRESSED;
	else if (!keyboardState[scancode] && prevKeyboardState[scancode]) return INPUT_STATE_RELEASED;
	else if (!keyboardState[scancode] && !prevKeyboardState[scancode]) return INPUT_STATE_UP;
}