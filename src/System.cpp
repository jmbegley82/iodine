/* System.cpp
 *
 */

#include <SDL.h>
#include "System.h"
#include "Logger.h"

static System _system;

System::System() {
	Logger_init();
#if defined DEBUG_NOVIDEO
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER);
#else
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER);
#endif //DEBUG_NOVIDEO
	_texcache = new TexCache();
	_screen = new Screen();
}

System::~System() {
	delete _screen;
	delete _texcache;
	SDL_Quit();
	Logger_finish();
}

Texture* System::LoadTexture(const string& path) {
	return _system._texcache->Load(path);
}

void System::UnloadTextures() {
	return _system._texcache->UnloadAll();
}
