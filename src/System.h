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
#include "Container.h"
#include "Sprite.h"
#include "AnimationSet.h"
//#include "Array.h"
#include "LList.h"

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
	Container<Sprite> _sprites;
	//Array<Sprite> _effects;
	LList<Sprite*> _effects;
	double _timeOfLastSprite;
	double _timeOfLastEffect;
	Container<AnimationSet> _animsets;
	bool _timeToQuit;
};

#endif //SYSTEM_H
