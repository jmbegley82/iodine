/* Logger.h
 *
 */

#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**
 * @brief These represent values returned from Logger_status and stored in _logStatus.
 * @details They refer to various running states of the Logger_autoflush thread.  LOG_EXITING should probably never be
 * used manually!  The others can be set externally via Logger_pause and Logger_unpause.
 */
enum LogStatuses {
	LOG_STOPPED,	//!< Do not print anything via Logger_autoflush
	LOG_RUNNING,	//!< Do print things via Logger_autoflush
	LOG_EXITING	//!< Do not print anything via Logger_autoflush and cause its thread to exit
};

/**
 * @brief Initialize the Logger
 * @details In the future, this will accept parameters that will specify console output, file output, path of output file
 * and will almost certainly initialize a mutex.
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
 * @param str (const char*) the C-string to add to the log buffer
 * @return int 0 = success, 1 = success and the buffer was emptied
 */
int Logger(const char* str);

/**
 * @brief Print this message to the log right now
 * @details Well, literally, add the line to the buffer and immediately flush it with Logger_process_unsafe
 * @param str (const char*) the C-string to log
 */
void Logger_now(const char* str);

/**
 * @brief Pause the automatic log-processing thread
 * @details Set _logStatus to LOG_STOPPED
 */
void Logger_pause();

/**
 * @brief Resume the automatic log-processing thread
 * @details Set _logStatus to LOG_RUNNING
 */
void Logger_unpause();

/**
 * @brief return _logStatus
 */
int Logger_status();

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //LOGGER_H
