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
#if defined SYSTEM_USE_CONTAINER
#include "Container.h"
#else
#include <map>
#endif //SYSTEM_USE_CONTAINER
#include "Sprite.h"
#include "AnimationSet.h"
#include "LList.h"

using std::string;

#if !defined SYSTEM_USE_CONTAINER
using std::map;
typedef map<string,Sprite*> SpriteMap;
typedef map<string,AnimationSet*> AnimSetMap;
#endif //SYSTEM_USE_CONTAINER

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
	static Renderer* GetRenderer();
	static int Command(const string& cmd);
	static AnimationSet* GetAnimationSet(const string& name);
	void PollEvents();
private:
	int _Command(const string& cmd);
#if defined DEBUG
	void _Test();
	void _Test2();
	void _Test3();
#endif //DEBUG
	TexCache* _texcache;
	Screen* _screen;
#if defined SYSTEM_USE_CONTAINER
	Container<Sprite*> _sprites;
	Container<AnimationSet*> _animsets;
#else
	SpriteMap _sprites;
	AnimSetMap _animsets;
#endif //SYSTEM_USE_CONTAINER
	LList<Sprite*> _effects;
	double _timeOfLastSprite;
	double _timeOfLastEffect;
	bool _timeToQuit;
};

#endif //SYSTEM_H
