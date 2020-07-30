/* System.h
 *
 */

#if !defined SYSTEM_H
#define SYSTEM_H

#include <string>
#include "Screen.h"
#include "TexCache.h"
#include "GfxTypes.h"
#include "Filesystem.h"

using std::string;

class System {
public:
	System();
	~System();
	static Texture* LoadTexture(const string& path);
	static void UnloadTextures();
	static void PollEvents();
	TexCache* _texcache;
	Screen* _screen;
//would be private if they could:
	static void* PollIt(void* arg);
};

#endif //SYSTEM_H
