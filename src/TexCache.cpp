/* TexCache.cpp
 *
 */

/*
TexCache();
~TexCache();
Texture* Load(const string& path);
bool Unload(const string& path);
void UnloadAll();	
 */

#include <string>
#include <map>
// remove the following once rand is no longer needed
#include <cstdlib>
#include "TexCache.h"
#include "GfxTypes.h"

#if defined DEBUGEXTRA
#include "Logger.h"
#endif //DEBUGEXTRA

static TexCache _texcache;

TexCache::TexCache() {
#if defined DEBUGEXTRA
	Log("TexCache:  initialized");
#endif //DEBUGEXTRA
}

TexCache::~TexCache() {
	UnloadAll();
#if defined DEBUGEXTRA
	Log("TexCache:  *pop*");
#endif //DEBUGEXTRA
}

Texture* TexCache::Load(const string& path) {
	Texture* retval = NULL;
	texitr i = _texcache._textures.find(path);
	if(i != _texcache._textures.end()) {
		retval = i->second;
	} else {
		// not found
		retval = new Texture;
		*retval = (Texture)(rand()%10000000);
		// pretend retval now contains an actual Texture
		_texcache._textures[path] = retval;
	}
	return retval;
}

bool TexCache::Unload(const string& path) {
	texitr i = _texcache._textures.find(path);
	if(i != _texcache._textures.end()) {
		delete i->second;
		_texcache._textures.erase(i);  // TODO: test this!
		return true;
	}
	return false;
}

void TexCache::UnloadAll() {
	for(texitr i=_texcache._textures.begin(); i!=_texcache._textures.end(); ++i) {
		delete i->second;
	}
	_texcache._textures.clear();
}
