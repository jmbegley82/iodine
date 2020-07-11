/* Logger.Test.c
 *
 */

#include <stdio.h>
#include "Platform.h"
#include "Logger.h"

#if defined DEBUG
int Platform_Test() {
	char homedir[64];
	char tmpdir[64];
	GetUserHomeDir(homedir);
	GetWritableTmpDir(tmpdir);
	char msg[128];
	sprintf(msg, "Platform_Test:  homedir=%s", homedir);
	Logger(msg);
	sprintf(msg, "Platform_Test:  tmpdir=%s", tmpdir);
	Logger(msg);
	Logger("Platform_Test:  Please check accuracy manually!");
	return 0;
}
#endif //DEBUG
