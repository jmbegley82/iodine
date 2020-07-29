/* Logger.Test.c
 *
 */

#include <stdio.h>
#include "Filesystem.h"
#include "Logger.h"

#if defined DEBUG
int Filesystem_Test() {
	char msg[128];
	sprintf(msg, "Filesystem_Test:  homedir=%s", GetHomeDir());
	Logger(msg);
	sprintf(msg, "Filesystem_Test:  installdir=%s", GetInstallDir());
	Logger(msg);
	sprintf(msg, "Filesystem_Test:  tmpdir=%s", GetTmpDir());
	Logger(msg);
	Logger("Filesystem_Test:  Please check accuracy manually!");
	return 0;
}
#endif //DEBUG
