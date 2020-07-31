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

#define OBJECT_SPRITE_SINGLE 0
#define OBJECT_SPRITE_SHEET 1
#define OBJECT_SPRITE_TEXT 2

#define OBJECT_FLIPAXIS_VERTICAL 0
#define OBJECT_FLIPAXIS_HORIZONTAL 1

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern lua_State* L;

extern SDL_Rect gViewport;

extern int screenWidth, screenHeight;

#endif