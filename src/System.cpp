/* System.cpp
 *
 */

//#include <pthread.h>
#include <SDL.h>
#include "System.h"
#include "Logger.h"
#include "Timing.h"

#if defined DEBUG
#include <cstdlib>
#endif //DEBUG

static System _system;

System::System() {
	_timeToQuit = false;
	_texcache = NULL;
	_screen = NULL;
	Logger_init();
}

System::~System() {
	_animsets.Clear();
	Logger_finish();
}

void System::Start() {
	if(_system._screen) return;
#if defined DEBUG_NOVIDEO
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER);
#else
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER);
#endif //DEBUG_NOVIDEO
	_system._texcache = new TexCache();
	_system._screen = new Screen();
}

void System::Stop() {
	if(_system._texcache) delete _system._texcache;
	if(_system._screen) delete _system._screen;
	_system._timeToQuit = true;
	SDL_Quit();
}

void System::Tick() {
	if(!_system._screen || _system._timeToQuit) return;
	_system.PollEvents();

	// Tick Sprites
	for(int i=0; i<_system._sprites.GetCount(); ++i) {
		Sprite* spr = _system._sprites.GetByIndex(i);
		spr->Tick();
	}
	// Tick Effects
	for(int i=0; i<_system._effects.GetCount(); ++i) {
		Sprite* spr = _system._effects.GetByIndex(i);
		spr->Tick();
	}
	// Check for and remove Sprites that have expired
	bool makeSpritesContiguous = false;
	for(int i=_system._sprites.GetCount() - 1; i>= 0; --i) {
		Sprite* spr = _system._sprites.GetByIndex(i);
		if(spr->HasExpired()) {
#if defined DEBUGEXTRA
			Log(string("System::Tick:  Destroy Sprite:  ") + _system._sprites.GetNameByIndex(i));
#endif //DEBUGEXTRA
			//_system._sprites.Destroy(spr);
			_system._sprites.Destroy_unsafe(i);
			makeSpritesContiguous = true;
		}
	}
	if(makeSpritesContiguous) _system._sprites.MakeContiguous();
	// (Same for Effects)
	bool makeEffectsContiguous = false;
	for(int i=_system._effects.GetCount() - 1; i>= 0; --i) {
		Sprite* spr = _system._effects.GetByIndex(i);
		if(spr->HasExpired()) {
#if defined DEBUGEXTRA
			Log(string("System::Tick:  Destroy Sprite:  (anonymous)"));
#endif //DEBUGEXTRA
			_system._effects.Destroy_unsafe(i);
			makeEffectsContiguous = true;
		}
	}
	if(makeEffectsContiguous) _system._effects.MakeContiguous();
	// Add Sprites' current Cels to Drawlist
	for(int i=0; i<_system._sprites.GetCount(); ++i) {
		SrcRect src;
		DstRect dst;
		Sprite* spr = _system._sprites.GetByIndex(i);
		spr->GetDrawSrcRect(&src);
		spr->GetDrawDstRect(&dst);
		_system._screen->AddToDrawlist(spr->GetTexture(), &src, &dst);
	}
	// Add Effects' current Cels to Drawlist
	for(int i=0; i<_system._effects.GetCount(); ++i) {
		SrcRect src;
		DstRect dst;
		Sprite* spr = _system._effects.GetByIndex(i);
		spr->GetDrawSrcRect(&src);
		spr->GetDrawDstRect(&dst);
		_system._screen->AddToDrawlist(spr->GetTexture(), &src, &dst);
	}
	_system._screen->UpdateWindow();
}

Texture* System::LoadTexture(const string& path) {
	return _system._texcache->Load(path);
}

void System::UnloadTextures() {
	return _system._texcache->UnloadAll();
}

bool System::TimeToQuit() {
	return _system._timeToQuit;
}

bool System::WindowExists() {
	return _system._screen->WindowExists();
}

bool System::CreateWindow() {
	return _system._screen->CreateWindow();
}

bool System::DestroyWindow() {
	return _system._screen->DestroyWindow();
}

Renderer* System::GetRenderer() {
	if(!_system._screen) return NULL;
	return _system._screen->GetRenderer();
}

int System::Command(const string& cmd) {
	return _system._Command(cmd);
}

AnimationSet* System::GetAnimationSet(const string& name) {
	AnimationSet* retval = NULL;
	retval = _system._animsets.Get(name);
	return retval;
}

void System::PollEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT:
			_timeToQuit = true;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_RETURN)
				_timeToQuit = true;
			else if(event.key.keysym.sym == SDLK_SPACE)
				_Test2();
			break;
		default:
			break;
		}
	}
}

int System::_Command(const string& cmd) {
	if(cmd == "test") {
#if defined DEBUG
		// do the thing
		_Test();
#endif //DEBUG
		return 0;
	}
	if(cmd == "test2") {
#if defined DEBUG
		// do the other thing
		_Test2();
#endif //DEBUG
		return 0;
	}
	return -1;
}

#if defined DEBUG
void System::_Test() {
	AnimationSet* anm = new AnimationSet();
	anm->LoadAnimation("walkl", "data/terra.walkl.anm");
	anm->LoadAnimation("walkr", "data/terra.walkr.anm");
	_animsets.Add("terra", anm);
	Sprite* spr = new Sprite();
	spr->SetAnimationSet("terra");
	spr->SetAnimation("walkl");
	spr->SetPosition({200.0,200.0});
	_sprites.Add("player", spr);

	anm = new AnimationSet();
	anm->LoadAnimation("default", "data/poof.anm");
	_animsets.Add("poof", anm);
	spr = new Sprite();
	spr->SetAnimationSet("poof");
	spr->SetPosition({100.0,100.0});
	spr->SetOneshot();
	_sprites.Add("testobj", spr);
}

void System::_Test2() {
	/*
	Sprite* spr = new Sprite();
	spr->SetAnimationSet("poof");
	spr->SetPosition({static_cast<double>(rand()%400),
		static_cast<double>(rand()%400)});
	spr->SetOneshot();
	_sprites.Add("testobj", spr);
	*/
	Sprite* spr = new Sprite();
	spr->SetAnimationSet("poof");
	spr->SetPosition({static_cast<double>(rand()%400),
		static_cast<double>(rand()%400)});
	spr->SetOneshot();
	_effects.Add(spr);
}
#endif //DEBUG
