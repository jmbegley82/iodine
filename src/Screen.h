/* Screen.h
 *
 */

#if !defined SCREEN_H
#define SCREEN_H

#include "Drawlist.h"
#include "GfxTypes.h"

class Screen {
public:
	Screen();
	~Screen();
	bool CreateWindow();
	bool DestroyWindow();
	void UpdateWindow();
	bool AddToDrawlist(Texture* tex, SrcRect* src, DstRect* dst);
	bool WindowExists();
	Renderer* GetRenderer();
private:
	Window* _window;
	Renderer* _renderer;
	Drawlist _drawlist;
	int w;
	int h;
};

#endif //SCREEN_H
