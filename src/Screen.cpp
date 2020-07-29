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
	screenSurface = NULL;

	//Initialize SDL
	CreateWindow();
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
	SDL_Quit();
}

void Screen::CreateWindow() {
#if !defined DEBUG_NOVIDEO
	int rv = SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, &window, &renderer);
	if(rv < 0) {
		Log(string("Screen:  SDL_CreateWindow error:  ") + SDL_GetError());
	} else {
		SDL_RendererInfo rinfo;
		SDL_GetRendererInfo(renderer, &rinfo);
		Log(string("Screen:  SDL_RendererInfo:  name=") + string(rinfo.name) + ", max_texture_width="
				+ std::to_string(rinfo.max_texture_width));
		SDL_SetRenderDrawColor(renderer, 255,0,255,255);
		SDL_RenderFillRect(renderer, NULL);
		//Update the surface
		SDL_RenderPresent(renderer);
	}
#else
	Log("Screen:  DEBUG_NOVIDEO prevented window from being created");
#endif
}

/*
void Screen::CreateWindow_old() {
#if !defined DEBUG_NOVIDEO
	//Create window
	window = SDL_CreateWindow( "Iodine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		w, h, SDL_WINDOW_SHOWN );
	if( window == NULL ) {
		Log(string("Screen:  SDL_CreateWindow error:  ") + SDL_GetError());
	} else {
		renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
		if(renderer==NULL) {
			Log(string("Screen:  SDL_GetRenderer error:  ") + SDL_GetError());
		} else {
			Log("Screen:  Renderer created");
		}
		//Get window surface
		//screenSurface = SDL_GetWindowSurface( window );

		//Fill the surface white
		//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
		SDL_SetRenderDrawColor(renderer, 255,0,255,255);
		SDL_RenderFillRect(renderer, NULL);
            
		//Update the surface
		//SDL_UpdateWindowSurface( window );
		SDL_RenderPresent(renderer);
	}
#else
	Log("Screen:  DEBUG_NOVIDEO prevented window from being created");
#endif //DEBUG_NOVIDEO
}
*/
