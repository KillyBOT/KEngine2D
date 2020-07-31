#include "globals.h"
#include "luafuncs.h"
#include "draw.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
lua_State* L = NULL;

int screenWidth = 800;
int screenHeight = 600;

SDL_Rect gViewport = { 0, 0, screenWidth, screenHeight };

int init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL could not init! %s\n", SDL_GetError());
		return 0;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Texture filtering not set to linear!\n");
	}

	gWindow = SDL_CreateWindow("Lua SDL Testing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		fprintf(stderr, "SDL_Window could not be created! %s\n", SDL_GetError());
		return 0;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL) {
		fprintf(stderr, "SDL_Renderer could not be created! %s\n", SDL_GetError());
		return 0;
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		fprintf(stderr,"SDL_IMG could not init! Error: %s\n", IMG_GetError());
		return 0;
	}

	if (TTF_Init() == -1) {
		fprintf(stderr, "SDL_ttf could not init! Error: %s\n", TTF_GetError);
		return 0;
	}

	L = luaL_newstate();
	luaL_openlibs(L);
	//lOpenLibCustom(L);

	int lVM = luaL_loadfile(L, "scripts/main.lua");
	if (lVM) {
		fprintf(stderr, "%s\n", lua_tostring(L, -1));
		return lVM;
	}
	else {
		lua_pcall(L, 0, 0, lua_gettop(L) - 1);
	}

	//lCallFunc(L, "engine_load", 0, 0, lua_gettop(L) - 1);

	return 1;
}

int close() {
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);

	gWindow = NULL;
	gRenderer = NULL;

	lua_close(L);
	SDL_Quit();
	IMG_Quit();
	return 1;
}

int main(int argc, char** argv) {

	if (!init()) return 0;

	bool running = true;
	SDL_Event e;

	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		SDL_RenderSetViewport(gRenderer, &gViewport);

		SDL_RenderPresent(gRenderer);
	}

	close();

	return 0;
}