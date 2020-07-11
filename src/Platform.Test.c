/* Logger.Test.c
 *
 */

#include <stdio.h>
#include "Platform.h"
#include "Logger.h"

#if defined DEBUG
int Platform_Test() {
	char msg[128];
	sprintf(msg, "Platform_Test:  homedir=%s", GetHomeDir());
	Logger(msg);
	sprintf(msg, "Platform_Test:  tmpdir=%s", GetTmpDir());
	Logger(msg);
	Logger("Platform_Test:  Please check accuracy manually!");
	return 0;
}
#endif //DEBUG
