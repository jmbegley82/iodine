/* Screen.cpp
 *
 */

#include "Screen.h"
#include "GfxTypes.h"
#include "Platform.h"

static Screen _screen;

Screen::Screen() {
    //The window we'll be rendering to
    window = NULL;
    
    //The surface contained by the window
    screenSurface = NULL;

    //Initialize SDL
    if( InitializeSDL() < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    } else {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        } else {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Wait two seconds
            //SDL_Delay( 2000 );
        }
    }
}

Screen::~Screen() {
    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
}
