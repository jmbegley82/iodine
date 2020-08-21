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
#include <map>
#include "Sprite.h"
#include "AnimationSet.h"
#include "LList.h"
#include "VControl.h"

using std::string;

using std::map;
typedef map<string,Sprite*> SpriteMap;
typedef map<string,AnimationSet*> AnimSetMap;

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
	static VControl* GetP1VControl();
private:
	VControl P1;
	int _Command(const string& cmd);
#if defined DEBUG
	void _Test();
	void _Test2();
	void _Test3();
	void _Test4();
#endif //DEBUG
	TexCache* _texcache;
	Screen* _screen;
	SpriteMap _sprites;
	AnimSetMap _animsets;
	LList<Sprite*> _effects;
	double _timeOfLastSprite;
	double _timeOfLastEffect;
	bool _timeToQuit;
};

#endif //SYSTEM_H
