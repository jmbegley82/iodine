/* Screen.cpp
 *
 */

#include "Screen.h"
#include "GfxTypes.h"
#include "System.h"
#include "Logger.h"

using std::string;

Screen::Screen() {
	w = h = 400;
	//The window we'll be rendering to
	window = NULL;

	//The surface contained by the window
	screenSurface = NULL;

	//Initialize SDL
	CreateWindow();
}

Screen::~Screen() {
#if !defined DEBUG_NOVIDEO
	//Destroy window
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
	//Create window
	window = SDL_CreateWindow( "Iodine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		w, h, SDL_WINDOW_SHOWN );
	if( window == NULL ) {
		Log(string("Screen:  SDL_CreateWindow error:  ") + SDL_GetError());
	} else {
		//Get window surface
		screenSurface = SDL_GetWindowSurface( window );

		//Fill the surface white
		SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
		//Update the surface
		SDL_UpdateWindowSurface( window );
	}
#else
	Log("Screen:  DEBUG_NOVIDEO prevented window from being created");
#endif //DEBUG_NOVIDEO
}
