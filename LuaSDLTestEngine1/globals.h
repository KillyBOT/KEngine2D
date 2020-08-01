#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define INPUT_STATE_DOWN 0
#define INPUT_STATE_UP 1
#define INPUT_STATE_PRESSED 2
#define INPUT_STATE_RELEASED 3

#define MOUSE_BUTTON_LEFT 0
#define MOUSE_BUTTON_RIGHT 1
#define MOUSE_BUTTON_MIDDLE 2

#define SYSTEM_ID_GRAPHICS 0
#define SYSTEM_ID_TEXT 1
#define SYSTEM_ID_PHYSICS 2
#define SYSTEM_ID_TRANSFORM 3
#define SYSTEM_ID_COLLIDE 4
#define SYSTEM_ID_GAMELOGIC 5
#define SYSTEM_ID_INPUT 6
#define SYSTEM_ID_UI 7
#define SYSTEM_ID_AUDIO 8
#define SYSTEM_ID_ENTITYLOADER 9
#define SYSTEM_ID_EVENTHANDLER 10
#define SYSTEM_ID_ANIMATION 11

#define COMPONENT_ID_GRAPHICS 0
#define COMPONENT_ID_TEXT 1
#define COMPONENT_ID_PHYSICS 2
#define COMPONENT_ID_TRANSFORM 3
#define COMPONENT_ID_COLLIDE 4
#define COMPONENT_ID_GAMELOGIC 5
#define COMPONENT_ID_INPUT 6
#define COMPONENT_ID_UI 7
#define COMPONENT_ID_AUDIO 8
#define COMPONENT_ID_ENTITYLOADER 9
#define COMPONENT_ID_EVENTHANDLER 10
#define COMPONENT_ID_ANIMATION 11

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern lua_State* L;

extern SDL_Rect gViewport;

extern int screenWidth, screenHeight;

#endif