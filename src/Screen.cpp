/* Screen.cpp
 *
 */

#include <cassert>
#include "Screen.h"
#include "GfxTypes.h"
#include "Logger.h"

using std::string;

Screen::Screen() {
	w = h = 400;
	_window = NULL;
	_renderer = NULL;
}

Screen::~Screen() {
#if !defined DEBUG_NOVIDEO
	DestroyWindow();
#else
	Log("Screen:  DEBUG_NOVIDEO specified; skipping DestroyWindow");
#endif //DEBUG_NOVIDEO
}

bool Screen::CreateWindow() {
#if !defined DEBUG_NOVIDEO
	if(_window) return false;  // _window already exists!
	_window = SDL_CreateWindow("Iodine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if(!_window) {
		return false;  // _window could not be created!
	}
	_renderer = SDL_CreateRenderer(_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if(!_renderer) {
		return false;  // _window useless without a _renderer!
	}
	SDL_RendererInfo rinfo;
	SDL_GetRendererInfo(_renderer, &rinfo);
	Log(string("Screen:  SDL_RendererInfo:  name=") + string(rinfo.name) + ", max_texture_width="
			+ std::to_string(rinfo.max_texture_width));
	UpdateWindow();
#endif //DEBUG_NOVIDEO
	return true;
}

bool Screen::DestroyWindow() {
#if !defined DEBUG_NOVIDEO
	if(!_window) return false;  // no _window to destroy
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_renderer = NULL;
	_window = NULL;
#endif //DEBUG_NOVIDEO
	return true;  // _window has ceased to be
}

void Screen::UpdateWindow() {
#if !defined DEBUG_NOVIDEO
	if(!_window || !_renderer) {
		Log("Screen:  UpdateWindow:  No _window or _renderer available!");
		return;
	}
	// set target and screen clearing color
	SDL_SetRenderTarget(_renderer, NULL);
	SDL_SetRenderDrawColor(_renderer, 31,0,0,255);
	// wipe the screen
	SDL_RenderClear(_renderer);
	// iterate through _drawlist
	dlistEntry* entries = _drawlist.GetEntries();
	for(int i=0; i<_drawlist.GetCount(); ++i) {
		SDL_RenderCopy(_renderer, entries[i].tex, &entries[i].src, &entries[i].dst);
	}
	// draw everything we just did
	SDL_RenderPresent(_renderer);
	_drawlist.Clear();
#endif //DEBUG_NOVIDEO
}

bool Screen::AddToDrawlist(Texture* tex, SrcRect* src, DstRect* dst) {
	return _drawlist.Add(tex, src, dst);
}

bool Screen::WindowExists() {
#if !defined DEBUG_NOVIDEO
	if(_window && _renderer) return true;
#endif //DEBUG_NOVIDEO
	return false;
}

Renderer* Screen::GetRenderer() {
	return _renderer;
}
