/* Logger.h
 *
 */

#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**
 * @brief Initialize the Logger
 * @details In the future, this will accept parameters that will specify console output, file output, path of output file
 * and will almost certainly initialize a mutex.
 *
 * @return int 0 for everything went okay, -1 if it's already initialized
 */
int Logger_init();

/**
 * @brief Lock mutex, then call Logger_process_unsafe to write pending buffered log entries and clear the buffer
 * @details This function will be primarily called internally but should be safe for general use.
 */
void Logger_process();

/**
 * @brief Flush the buffer and deinitialize things and such
 */
void Logger_finish();

/**
 * @brief Add entry to log buffer
 * @details Once the entry is added to the buffer, the buffer size will be checked.  If it is over its predetermined
 * maximum length, Logger_process() will be called afterward to write the contents of the buffer and clear it, leaving us
 * with an empty buffer.
 *
 * @param str (const char*) the C-string to add to the log buffer
 * @return void
 */
void Logger(const char* str);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //LOGGER_H
