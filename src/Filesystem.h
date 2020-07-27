/* Filesystem.h
 *
 */

#if !defined FILESYSTEM_H
#define FILESYSTEM_H

#if defined __cplusplus

extern "C" {
#endif //__cplusplus

const char* GetHomeDir();		//!< Return C-string containing a path to our user's home directory
const char* GetInstallDir();		//!< Return C-string containing a path to our installation directory
const char* GetTmpDir();		//!< Return C-string containing a path to a system-approved temporary storage space

int InitializeSDL();

#if defined DEBUG
int Filesystem_Test();			//!< Run tests
#endif //DEBUG

#if defined __cplusplus
}
#endif //__cplusplus

#endif //FILESYSTEM_H
