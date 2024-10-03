#include "SDL.h"

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
	#include <emscripten/html5.h>
#endif

#include <iostream>

int width = 800;
int height = 800;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool quit = false;

#define LOG(x) std::cout << x << std::endl;

void MainLoop() {
	SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) quit = true;
        if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
            LOG("Window resized: " << event.window.data1 << "x" << event.window.data2);
        }
		if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            LOG("Window size changed: " << event.window.data1 << "x" << event.window.data2);
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_F) {
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_W) {
			SDL_SetWindowFullscreen(window, 0);
		}
    }

	int w = 0;
	int h = 0;
	SDL_Rect rect;

	SDL_GetWindowSize(window, &w, &h);
	SDL_GetDisplayBounds(0, &rect);

	LOG("SDL_GetWindowSize: " << w << "x" << h);
	LOG("SDL_GetDisplayBounds: " << rect.w << "x" << rect.h);

	SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
    SDL_RenderPresent(renderer);

#ifdef __EMSCRIPTEN__
	if (quit) emscripten_cancel_main_loop();
#endif
}

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("F = desktop fullscreen, W = windowed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, 0, 0);

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(MainLoop, 0, 1);
#else
	while (!quit) { MainLoop(); }
#endif
    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}