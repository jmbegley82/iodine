/* Logger.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Logger.h"


#ifndef MAX_LINELENGTH
#define MAX_LINELENGTH 4096
#endif //MAX_LINELENGTH

#ifndef MAX_LOGLINES
#define MAX_LOGLINES 128
#endif //MAX_LOGLINES

static char* _logbuffer[MAX_LOGLINES];
static int _logCurrentLine;

/**
 * @brief Initialize the Logger
 * @details In the future, this will accept parameters that will specify console output, file output, path of output file
 * and will almost certainly initialize a mutex.
 *
 * @return int 0 for everything went okay, -1 if it's already initialized
 */
int Logger_init() {
	for(int i=0; i<MAX_LOGLINES; i++)
		_logbuffer[i] = malloc(MAX_LINELENGTH);
	_logCurrentLine = 0;
	return 0;
}

/**
 * @brief Write pending buffered log entries and clear the buffer
 * @details This function will be primarily called internally but should be safe for general use.
 */
void Logger_process() {
	for(int i=0; i<_logCurrentLine; i++) {
		printf("%s\n", _logbuffer[i]);
		free((void*)_logbuffer[i]);
		_logbuffer[i] = malloc(MAX_LINELENGTH);
	}
	_logCurrentLine = 0;
}

/**
 * @brief Flush the buffer and deinitialize things and such
 */
void Logger_finish() {
	Logger_process();
	for(int i=0; i<MAX_LOGLINES; i++) {
		free((void*)_logbuffer[i]);
	}
}

/**
 * @brief Add entry to log buffer
 * @details Once the entry is added to the buffer, the buffer size will be checked.  If it is over its predetermined
 * maximum length, Logger_process() will be called afterward to write the contents of the buffer and clear it, leaving us
 * with an empty buffer.
 *
 * @param str (const char*) the C-string to add to the log buffer
 * @return void
 */
void Logger(const char* str) {
/*
	// for now, dump to stdout
	printf("%s\n", str);
*/
	assert(_logCurrentLine < MAX_LOGLINES);
	//_logbuffer[_logCurrentLine] = str;
	strncpy(_logbuffer[_logCurrentLine], str, MAX_LINELENGTH);
	_logbuffer[_logCurrentLine][MAX_LINELENGTH] = '\0';
	_logCurrentLine++;
	if(_logCurrentLine >= MAX_LOGLINES)
		Logger_process();
}
