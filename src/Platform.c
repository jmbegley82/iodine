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

void GetUserHomeDir(char* dir) {
	char* home;
#if defined __linux__
	home = getenv("HOME");  // should we be using getpwuid(getuid())->pw_dir for this instead?
#else
#error Platform support not written yet!
#endif //platforms
#if defined DEBUGEXTRA
	char msg[128];
	sprintf(msg, "Platform:  GetUserHomeDir:  home=%s", home);
	Logger(msg);
#endif //DEBUGEXTRA
	strcpy(dir, home);
}

void GetWritableTmpDir(char* dir) {
	char* tmp;
#if defined __linux__
	tmp = "/tmp";  // TODO:  there's *got* to be a better way
#else
#error Platform support not written yet!
#endif //platforms
#if defined DEBUGEXTRA
	char msg[128];
	sprintf(msg, "Platform:  GetWritableTmpDir:  tmp=%s", tmp);
	Logger(msg);
#endif //DEBUGEXTRA
	strcpy(dir, tmp);
}

