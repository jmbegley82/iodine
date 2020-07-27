/* Screen.cpp
 *
 */

#include "Screen.h"
#include "GfxTypes.h"
#include "Platform.h"
#include "Logger.h"

using std::string;

static Screen _screen;

Screen::Screen() {
    //The window we'll be rendering to
    window = NULL;
    
    //The surface contained by the window
    screenSurface = NULL;

    //Initialize SDL
    if( InitializeSDL() < 0 )
    {
	Log(string("Screen:  SDL_Init error:  ") + SDL_GetError());
    } else {

    }
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
        _screen.window = SDL_CreateWindow( "Iodine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_screen.w, _screen.h, SDL_WINDOW_SHOWN );
        if( _screen.window == NULL )
        {
            Log(string("Screen:  SDL_CreateWindow error:  ") + SDL_GetError());
        } else {
            //Get window surface
            _screen.screenSurface = SDL_GetWindowSurface( _screen.window );

            //Fill the surface white
            SDL_FillRect( _screen.screenSurface, NULL, SDL_MapRGB( _screen.screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( _screen.window );
        }
#else
	Log("Screen:  DEBUG_NOVIDEO prevented window from being created");
#endif //DEBUG_NOVIDEO
}
