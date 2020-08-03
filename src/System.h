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
	static void Start();
	static void Stop();
	static void Tick();
	static Texture* LoadTexture(const string& path);
	static void UnloadTextures();
	static bool TimeToQuit();
	static bool WindowExists();
	static bool CreateWindow();
	static bool DestroyWindow();
	static SDL_Renderer* GetRenderer();
	void PollEvents();
private:
	TexCache* _texcache;
	Screen* _screen;
	bool _timeToQuit;
};

#endif //SYSTEM_H
