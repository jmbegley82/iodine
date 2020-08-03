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
#include "Gfx.h"
#include "System.h"

#if defined DEBUGEXTRA
#include "Logger.h"
#endif //DEBUGEXTRA

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
	texitr i = _textures.find(path);
	if(i != _textures.end()) {
		retval = i->second;
	} else {
		// not found
		retval = LoadTextureFromFile(path);
		_textures[path] = retval;
	}
	return retval;
}

bool TexCache::Unload(const string& path) {
	texitr i = _textures.find(path);
	if(i != _textures.end()) {
		DestroyTexture(i->second);
		_textures.erase(i);
		return true;
	}
	return false;
}

void TexCache::UnloadAll() {
	for(texitr i=_textures.begin(); i!=_textures.end(); ++i) {
		DestroyTexture(i->second);
	}
	_textures.clear();
}
