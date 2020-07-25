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
#include "TexCache.h"
#include "GfxTypes.h"

static TexCache _texcache;

TexCache::TexCache() {
}

TexCache::~TexCache() {
	UnloadAll();
}

Texture* TexCache::Load(const string& path) {
	Texture* retval = NULL;
	texitr i = _texcache._textures.find(path);
	if(i != _texcache._textures.end()) {
		retval = i->second;
	} else {
		// not found
		// pretend retval now contains an actual Texture
		_texcache._textures[path] = retval;
	}
	return retval;
}

bool TexCache::Unload(const string& path) {
	return false;
}

void TexCache::UnloadAll() {
	for(texitr i=_textures.begin(); i!=_textures.end(); ++i) {
		delete i->second;
	}
	_textures.clear();
}
