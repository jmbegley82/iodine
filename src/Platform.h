/* Platform.h
 *
 */

#if !defined PLATFORM_H
#define PLATFORM_H

#if defined __cplusplus

#include <string>
#include "TexCache.h"
#include "GfxTypes.h"

using std::string;

class Platform {
public:
	Platform();
	~Platform();
	static Texture* LoadTexture(const string& path);
	//Logger* _logger;
	TexCache* _texcache;
};

extern "C" {
#endif //__cplusplus

const char* GetHomeDir();		//!< Return C-string containing a path to our user's home directory
const char* GetInstallDir();		//!< Return C-string containing a path to our installation directory
const char* GetTmpDir();		//!< Return C-string containing a path to a system-approved temporary storage space

int InitializeSDL();

#if defined DEBUG
int Platform_Test();			//!< Run tests
#endif //DEBUG

#if defined __cplusplus
}
#endif //__cplusplus

#endif //PLATFORM_H
