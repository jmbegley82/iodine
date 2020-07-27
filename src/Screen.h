/* Screen.h
 *
 */

#if !defined SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include "GfxTypes.h"

class Screen {
public:
	Screen();
	~Screen();
	void CreateWindow();
private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	int w;
	int h;
};

#endif //SCREEN_H
