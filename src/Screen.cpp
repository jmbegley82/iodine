/* Screen.cpp
 *
 */

#include <cassert>
#include "Screen.h"
#include "GfxTypes.h"
#include "System.h"
#include "Logger.h"

using std::string;

Screen::Screen() {
	w = h = 400;
	window = NULL;
	renderer = NULL;
}

Screen::~Screen() {
#if !defined DEBUG_NOVIDEO
	/*
	//Destroy window
	if(renderer) SDL_DestroyRenderer(renderer);
	if(window) SDL_DestroyWindow(window);
	else Log("Screen:  window is not open");
	*/
	DestroyWindow();
#else
	Log("Screen:  DEBUG_NOVIDEO specified; skipping SDL_DestroyWindow");
#endif //DEBUG_NOVIDEO
}

bool Screen::CreateWindow() {
#if !defined DEBUG_NOVIDEO
	if(window) return false;  // window already exists!
	window = SDL_CreateWindow("Iodine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if(!window) {
		return false;  // window could not be created!
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if(!renderer) {
		return false;  // window useless without a renderer!
	}
	SDL_RendererInfo rinfo;
	SDL_GetRendererInfo(renderer, &rinfo);
	Log(string("Screen:  SDL_RendererInfo:  name=") + string(rinfo.name) + ", max_texture_width="
			+ std::to_string(rinfo.max_texture_width));
	UpdateWindow();
#endif //DEBUG_NOVIDEO
	return true;
}

bool Screen::DestroyWindow() {
#if !defined DEBUG_NOVIDEO
	if(!window) return false;  // no window to destroy
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
#endif //DEBUG_NOVIDEO
	return true;  // window has ceased to be
}

void Screen::UpdateWindow() {
#if !defined DEBUG_NOVIDEO
	if(!window || !renderer) {
		Log("Screen:  UpdateWindow:  No window or renderer available!");
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawColor(renderer, 255,0,255,255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
#endif //DEBUG_NOVIDEO
}

bool Screen::WindowExists() {
#if !defined DEBUG_NOVIDEO
	if(window && renderer) return true;
#endif //DEBUG_NOVIDEO
	return false;
}

Renderer* Screen::GetRenderer() {
	return renderer;
}
