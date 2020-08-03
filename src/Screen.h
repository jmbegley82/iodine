/* Screen.h
 *
 */

#if !defined SCREEN_H
#define SCREEN_H

#include "GfxTypes.h"

class Screen {
public:
	Screen();
	~Screen();
	bool CreateWindow();
	bool DestroyWindow();
	void UpdateWindow();
	bool WindowExists();
	Renderer* GetRenderer();
private:
	Window* window;
	Renderer* renderer;
	//SDL_Surface* screenSurface;
	int w;
	int h;
};

#endif //SCREEN_H
