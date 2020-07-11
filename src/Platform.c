/* Platform.c
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "Platform.h"

#if defined DEBUGEXTRA
#include "Logger.h"
#endif //DEBUGEXTRA

static const char* _homedir = 0;
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
