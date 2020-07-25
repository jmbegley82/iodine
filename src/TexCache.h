/* TexCache.h
 *
 */

#if !defined TEXCACHE_H
#define TEXCACHE_H

#include <string>
#include <map>
#include "GfxTypes.h"

using std::string;
using std::map;

typedef map<string,Texture*> texmap;
typedef texmap::iterator texitr;

// TODO: actually load textures

class TexCache {
public:
	TexCache();
	~TexCache();
	static Texture* Load(const string& path);
	static bool Unload(const string& path);
	static void UnloadAll();
#if defined DEBUG
	static int Test();
#endif //DEBUG
private:
	texmap _textures;
};

#endif //TEXCACHE_H
