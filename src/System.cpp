/* System.cpp
 *
 */

//#include <pthread.h>
#include <SDL.h>
#include "System.h"
#include "Logger.h"
#include "Timing.h"
#include "ActionDemo.h"

#if defined DEBUG
#include <cstdlib>
#endif //DEBUG

static System _system;

System::System() {
	_timeToQuit = false;
	_texcache = NULL;
	_screen = NULL;
	memset(&P1, 0, sizeof(VControl));
	_timeOfLastSprite = _timeOfLastEffect = GetTimeInMsec();
	Logger_init();
}

System::~System() {
#if defined SYSTEM_USE_CONTAINER
	_animsets.Clear();
#endif
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
#if defined SYSTEM_USE_CONTAINER
	for(int i=0; i<_system._sprites.GetCount(); ++i) {
		Sprite* spr = _system._sprites.GetByIndex(i);
		spr->Tick();
	}
#else
	for(SpriteMap::iterator i=_system._sprites.begin(); i!= _system._sprites.end(); ++i) {
		i->second->Tick();
	}
#endif //SYSTEM_USE_CONTAINER
	// Tick Effects
	for(LList<Sprite*>::iterator i = _system._effects.GetFirst(); i != NULL; i = i->next) {
		i->item->Tick();
	}
	// Check for and remove Sprites that have expired
#if defined SYSTEM_USE_CONTAINER
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
#else
	for(SpriteMap::iterator i=_system._sprites.begin(), i_next=i; i!=_system._sprites.end(); i=i_next) {
		++i_next;
		Sprite* spr = i->second;
		if(spr->HasExpired()) {
#if defined DEBUGEXTRA
			Log(string("System::Tick:  Destroy Sprite:  ") + i->first);
#endif //DEBUGEXTRA
		delete spr;
		_system._sprites.erase(i);
		}
	}
#endif //SYSTEM_USE_CONTAINER
	// (Same for Effects)
	bool makeEffectsContiguous = false;
	for(LList<Sprite*>::iterator i = _system._effects.GetLast(); i != NULL; i = i->prev) {
		Sprite* spr = i->item;
		if(spr->HasExpired()) {
#if defined DEBUGEXTRA
			Log(string("System::Tick:  Destroy Sprite:  (anonymous)"));
#endif //DEBUGEXTRA
			_system._effects.Remove(i);
			delete i->item;
			makeEffectsContiguous = true;
		}
	}
	// make contiguous if anything was destroyed
	/*
	if(makeSpritesContiguous) {
		_system._sprites.MakeContiguous();
		_system._timeOfLastSprite = GetTimeInMsec();
	}
	*/
	if(makeEffectsContiguous) {
		//_system._effects.MakeContiguous();
		//_system._effects.Compact();
		_system._timeOfLastEffect = GetTimeInMsec();
	}
	// try to shrink if it's been long enough
#if defined SYSTEM_USE_CONTAINER
	if(GetTimeInMsec() - _system._timeOfLastSprite >= 5000.0) {
		_system._sprites.Shrink();
		_system._timeOfLastSprite = GetTimeInMsec();
	}
#endif //SYSTEM_USE_CONTAINER
	if(GetTimeInMsec() - _system._timeOfLastEffect >= 5000.0) {
		//_system._effects.Shrink();
		//_system._effects.Compact();
		_system._timeOfLastEffect = GetTimeInMsec();
	}
	// Add Sprites' current Cels to Drawlist
#if defined SYSTEM_USE_CONTAINER
	for(int i=0; i<_system._sprites.GetCount(); ++i) {
		Sprite* spr = _system._sprites.GetByIndex(i);
#else
	for(SpriteMap::iterator i=_system._sprites.begin(); i!=_system._sprites.end(); ++i) {
		Sprite* spr = i->second;
#endif //SYSTEM_USE_CONTAINER
		SrcRect src;
		DstRect dst;
		spr->GetDrawSrcRect(&src);
		spr->GetDrawDstRect(&dst);
		_system._screen->AddToDrawlist(spr->GetTexture(), &src, &dst);
	}
	// Add Effects' current Cels to Drawlist
	for(LList<Sprite*>::iterator i = _system._effects.GetFirst(); i != NULL; i = i->next) {
		SrcRect src;
		DstRect dst;
		Sprite* spr = i->item;
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
#if defined SYSTEM_USE_CONTAINER
	retval = _system._animsets.Get(name);
#else
	AnimSetMap::iterator i = _system._animsets.find(name);
	if(i != _system._animsets.end()) retval = i->second;
#endif //SYSTEM_USE_CONTAINER
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
			if(event.key.keysym.sym == SDLK_UP)
				P1.Up = true;
			else if(event.key.keysym.sym == SDLK_DOWN)
				P1.Down = true;
			else if(event.key.keysym.sym == SDLK_LEFT)
				P1.Left = true;
			else if(event.key.keysym.sym == SDLK_RIGHT)
				P1.Right = true;
			else if(event.key.keysym.sym == SDLK_z)
				P1.Button1 = true;
			else if(event.key.keysym.sym == SDLK_x)
				P1.Button2 = true;
			else if(event.key.keysym.sym == SDLK_a)
				P1.Select = true;
			else if(event.key.keysym.sym == SDLK_s)
				P1.Start = true;
			else if(event.key.keysym.sym == SDLK_RETURN)
				_timeToQuit = true;
			else if(event.key.keysym.sym == SDLK_SPACE)
				_Test2();
			else if(event.key.keysym.sym == SDLK_TAB)
				_Test3();
			else if(event.key.keysym.sym == SDLK_b)
				_Test4();
			break;
		case SDL_KEYUP:
			if(event.key.keysym.sym == SDLK_UP)
				P1.Up = false;
			else if(event.key.keysym.sym == SDLK_DOWN)
				P1.Down = false;
			else if(event.key.keysym.sym == SDLK_LEFT)
				P1.Left = false;
			else if(event.key.keysym.sym == SDLK_RIGHT)
				P1.Right = false;
			else if(event.key.keysym.sym == SDLK_z)
				P1.Button1 = false;
			else if(event.key.keysym.sym == SDLK_x)
				P1.Button2 = false;
			else if(event.key.keysym.sym == SDLK_a)
				P1.Select = false;
			else if(event.key.keysym.sym == SDLK_s)
				P1.Start = false;
			else if(event.key.keysym.sym == SDLK_RETURN)
				_timeToQuit = false;
			break;
		default:
			break;
		}
	}
}

VControl* System::GetP1VControl() {
	return &_system.P1;
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
	if(cmd == "test3") {
#if defined DEBUG
		// do a third thing
		_Test3();
#endif //DEBUG
		return 0;
	}
	return -1;
}

#if defined DEBUG
void System::_Test() {
	AnimationSet* anm = new AnimationSet();
	anm->LoadAnimation("wl", "data/terra.walkl.anm");
	anm->LoadAnimation("wr", "data/terra.walkr.anm");
	AnimationSet* ball = new AnimationSet();
	ball->LoadAnimation("de", "data/ball.anm");
#if defined SYSTEM_USE_CONTAINER
	_animsets.Add("terra", anm);
	_animsets.Add("ball", ball);
#else
	_animsets["terra"] = anm;
	_animsets["ball"] = ball;
#endif //SYSTEM_USE_CONTAINER
	Sprite* spr = new Sprite();
	spr->SetAnimationSet("terra");
	spr->SetAnimation("wl");
	spr->SetPosition({200.0,200.0});
	spr->AddAction(DbgControl);
#if defined SYSTEM_USE_CONTAINER
	_sprites.Add("player", spr);
#else
	_sprites["player"] = spr;
#endif //SYSTEM_USE_CONTAINER
	anm = new AnimationSet();
	anm->LoadAnimation("de", "data/poof.anm");
#if defined SYSTEM_USE_CONTAINER
	_animsets.Add("poof", anm);
#else
	_animsets["poof"] = anm;
#endif //SYSTEM_USE_CONTAINER
	spr = new Sprite();
	spr->SetAnimationSet("poof");
	spr->SetPosition({100.0,100.0});
	spr->SetOneshot();
#if defined SYSTEM_USE_CONTAINER
	_sprites.Add("testobj", spr);
#else
	_sprites["testobj"] = spr;
#endif //SYSTEM_USE_CONTAINER

	anm = new AnimationSet();
	anm->LoadAnimation("de", "data/pop.anm");
#if defined SYSTEM_USE_CONTAINER
	_animsets.Add("pop", anm);
#else
	_animsets["pop"] = anm;
#endif //SYSTEM_USE_CONTAINER
	spr = new Sprite();
	spr->SetAnimationSet("pop");
	spr->SetPosition({200.0,100.0});
	spr->SetOneshot();
#if defined SYSTEM_USE_CONTAINER
	_sprites.Add("testobj2", spr);
#else
	_sprites["testobj2"] = spr;
#endif //SYSTEM_USE_CONTAINER

	anm = new AnimationSet();
	anm->LoadAnimation("de", "data/expl128.anm");
#if defined SYSTEM_USE_CONTAINER
	_animsets.Add("expl128", anm);
#else
	_animsets["expl128"] = anm;
#endif //SYSTEM_USE_CONTAINER
	spr = new Sprite();
	spr->SetAnimationSet("expl128");
	spr->SetPosition({300.0,100.0});
	spr->SetOneshot();
#if defined SYSTEM_USE_CONTAINER
	_sprites.Add("testobj3", spr);
#else
	_sprites["testobj3"] = spr;
#endif //SYSTEM_USE_CONTAINER
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

void System::_Test3() {
	Sprite* spr = NULL;
	for(int i=0; i<100; ++i) {
		spr = new Sprite();
		int rando = rand()%64;
		if(rando > 62)
			spr->SetAnimationSet("expl128");
		else if(rando > 54)
			spr->SetAnimationSet("poof");
		else {
			spr->SetAnimationSet("pop");
			spr->SetVelocityX((static_cast<double>(rand()%100)-50.0)/400.0);
			spr->SetVelocityY((static_cast<double>(rand()%100)-50.0)/400.0);
		}
		spr->SetPosition({static_cast<double>(rand()%400),
			static_cast<double>(rand()%400)});
		spr->SetOneshot();
		_effects.Add(spr);
	}
}

void System::_Test4() {
	Sprite* spr = new Sprite();
	spr->SetAnimationSet("ball");
	spr->SetVelocityX(0.125);
	spr->SetVelocityY(0.125);
	spr->SetPosition({static_cast<double>(rand()%400),
		static_cast<double>(rand()%400)});
	spr->MakeBouncy();
	_effects.Add(spr);
}

#endif //DEBUG
