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
	//The window we'll be rendering to
	window = NULL;
	renderer = NULL;

	//The surface contained by the window
	//screenSurface = NULL;

	//Initialize SDL
	//CreateWindow();
}

Screen::~Screen() {
#if !defined DEBUG_NOVIDEO
	//Destroy window
	if(renderer) SDL_DestroyRenderer(renderer);
	if(window) SDL_DestroyWindow( window );
	else Log("Screen:  window is not open");
#else
	Log("Screen:  DEBUG_NOVIDEO specified; skipping SDL_DestroyWindow");
#endif //DEBUG_NOVIDEO
	//Quit SDL subsystems
	//SDL_Quit();
}

bool Screen::CreateWindow() {
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
	return true;
}

bool Screen::DestroyWindow() {
	if(!window) return false;  // no window to destroy
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	return true;  // window has ceased to be
}

/*
void Screen::CreateWindow() {
#if !defined DEBUG_NOVIDEO
	int rv = SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_RESIZABLE, &window, &renderer);
	if(rv < 0) {
		Log(string("Screen:  SDL_CreateWindow error:  ") + SDL_GetError());
	} else {
		SDL_RendererInfo rinfo;
		SDL_GetRendererInfo(renderer, &rinfo);
		Log(string("Screen:  SDL_RendererInfo:  name=") + string(rinfo.name) + ", max_texture_width="
				+ std::to_string(rinfo.max_texture_width));
		SDL_SetRenderDrawColor(renderer, 255,0,255,255);
		SDL_RenderClear(renderer);
		//Update the surface
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);
	}
#else
	Log("Screen:  DEBUG_NOVIDEO prevented window from being created");
#endif
}
*/

void Screen::UpdateWindow() {
#if !defined DEBUG_NOVIDEO
	if(!window || !renderer) {
		Log("Screen:  UpdateWindow:  No window or renderer available!");
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawColor(renderer, 255,0,255,255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	//SDL_UpdateWindowSurface(window);
#endif //DEBUG_NOVIDEO
}

bool Screen::WindowExists() {
	if(window && renderer) return true;
	return false;
}

Renderer* Screen::GetRenderer() {
	return renderer;
}
