/* Platform.h
 *
 */

#if !defined PLATFORM_H
#define PLATFORM_H

#if defined __cplusplus
extern "C" {
#endif //__cplusplus

void GetUserHomeDir(char* dir);
void GetWritableTmpDir(char* dir);

#if defined DEBUG
int Platform_Test();
#endif //DEBUG

#if defined __cplusplus
}
#endif //__cplusplus

#endif //PLATFORM_H
