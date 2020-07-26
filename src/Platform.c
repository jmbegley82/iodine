/* Platform.c
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <SDL.h>
#include "Platform.h"

#if defined DEBUGEXTRA
#include "Logger.h"
#endif //DEBUGEXTRA

static const char* _homedir = 0;
static const char* _installdir = 0;
static const char* _tmpdir = 0;

const char* GetHomeDir() {
	if(!_homedir) { 
#if defined (__linux__) || defined (__OpenBSD__)
		_homedir = getenv("HOME");
#else
#error Platform support not written yet!
#endif //platforms
	}
	return _homedir;
}

const char* GetInstallDir() {
	if(!_installdir) {
#if defined NOINSTALL
		_installdir = getenv("PWD");
#else
#error Platform support not written yet!
#endif //NOINSTALL
	}
	return _installdir;
}

const char* GetTmpDir() {
	if(!_tmpdir) {
#if defined (__linux__) || defined (__OpenBSD__)
		_tmpdir = "/tmp";
#else
#error Platform support not written yet!
#endif //platforms
	}
	return _tmpdir;
}

int InitializeSDL() {
	int retval = -1;
#if defined DEBUG_NOVIDEO
	retval = SDL_Init();
#else
	retval = SDL_Init(SDL_INIT_VIDEO);
#endif //DEBUG_NOVIDEO
	return retval;
}
