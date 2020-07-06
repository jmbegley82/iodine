/* Logger.h
 *
 */

#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

int Logger_init();
void Logger_process();
//void Logger_process_unsafe();
void Logger_finish();
void Logger(const char* str);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //LOGGER_H
