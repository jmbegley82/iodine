/* System.cpp
 *
 */

#include "System.h"
#include "Logger.h"

static System _system;

System::System() {
	Logger_init();
	_texcache = new TexCache();
	_screen = new Screen();
}

System::~System() {
	delete _screen;
	delete _texcache;
	Logger_finish();
}

Texture* System::LoadTexture(const string& path) {
	return _system._texcache->Load(path);
}

void System::UnloadTextures() {
	return _system._texcache->UnloadAll();
}
