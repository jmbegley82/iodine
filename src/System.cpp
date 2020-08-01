/* System.cpp
 *
 */

//#include <pthread.h>
#include <SDL.h>
#include "System.h"
#include "Logger.h"
#include "Timing.h"

static System _system;
//static pthread_t _eventThread;
//static pthread_mutex_t _eventMutex;
//static bool _timeToStop;

/*
void* System::PollIt(void* arg) {
	pthread_mutex_lock(&_eventMutex);
	bool cachedTTS = _timeToStop;
	pthread_mutex_unlock(&_eventMutex);
	while(!cachedTTS) {
		_system.PollEvents();
		if(_system._screen) {
			//Log("System:  PollIt:  Tick!");
			_system._screen->UpdateWindow();
		} else
			Log("System:  PollIt:  _screen=0!");
		SleepMsec(60);
		pthread_mutex_lock(&_eventMutex);
		cachedTTS = _timeToStop;
		pthread_mutex_unlock(&_eventMutex);
	}
#if defined DEBUGEXTRA
	Logger("PollIt has begun to exit correctly.");
#endif //DEBUGEXTRA
	pthread_exit((void*)0);
}
*/

System::System() {
	//pthread_mutex_init(&_eventMutex, NULL);
	//pthread_mutex_lock(&_eventMutex);
	//_timeToStop = false;
	//pthread_mutex_unlock(&_eventMutex);
	//pthread_create(&_eventThread, NULL, PollIt, NULL);
	_timeToQuit = false;
	_texcache = NULL;
	_screen = NULL;
	Logger_init();
}

System::~System() {
	//pthread_mutex_lock(&_eventMutex);
	//_timeToStop = true;
	//pthread_mutex_unlock(&_eventMutex);
	//pthread_join(_eventThread, NULL);
	Logger_finish();
	//pthread_mutex_destroy(&_eventMutex);
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
	if(!_system._screen) return;
	delete _system._screen;
	delete _system._texcache;
	SDL_Quit();
}

void System::Tick() {
	if(!_system._screen || _system._timeToQuit) return;
	_system.PollEvents();
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
			break;
		default:
			break;
		}
	}
}

