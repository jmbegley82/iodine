/* Platform.cpp
 *
 */

#include "Platform.h"

static Platform _platform;

Platform::Platform() {
	_texcache = new TexCache();
}

Platform::~Platform() {
	delete _texcache;
}

Texture* Platform::LoadTexture(const string& path) {
	return _platform._texcache->Load(path);
}
