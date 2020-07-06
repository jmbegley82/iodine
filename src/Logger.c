/* Logger.c
 *
 */

#include <pthread.h>
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

static pthread_mutex_t _logMutex;
static char* _logbuffer[MAX_LOGLINES];
static int _logCurrentLine;

int Logger_init() {
	pthread_mutex_init(&_logMutex, NULL);
	pthread_mutex_lock(&_logMutex);
	for(int i=0; i<MAX_LOGLINES; i++) {
		_logbuffer[i] = malloc(MAX_LINELENGTH);
		memset(_logbuffer[i], 0, MAX_LINELENGTH);
	}
	_logCurrentLine = 0;
	pthread_mutex_unlock(&_logMutex);
	return 0;
}

/**
 * @brief Write pending buffered log entries and clear the buffer.
 * @details This function should only be used internally because it does not lock the mutex!
 */
void Logger_process_unsafe() {
	for(int i=0; i<_logCurrentLine; i++) {
		printf("%s\n", _logbuffer[i]);
		memset(_logbuffer[i], 0, MAX_LINELENGTH);
	}
#ifdef EXTRADEBUG
	printf("Bawooooooosh!\n");
#endif //EXTRADEBUG
	_logCurrentLine = 0;
}

void Logger_process() {
	pthread_mutex_lock(&_logMutex);
	Logger_process_unsafe();
	pthread_mutex_unlock(&_logMutex);
}

void Logger_finish() {
	pthread_mutex_lock(&_logMutex);
	Logger_process_unsafe();
	for(int i=0; i<MAX_LOGLINES; i++) {
		free((void*)_logbuffer[i]);
	}
	pthread_mutex_unlock(&_logMutex);
	pthread_mutex_destroy(&_logMutex);
}

/**
 * @brief Add entry to _logbuffer the dangerous way
 * @details Write str to _logbuffer[_logCurrentLine], increment _logCurrentLine, if it's over MAX_LOGLINES,
 * flush it with Logger_process_unsafe.  Internal use only!
 * @param str (const char*) the C-string to add to the log buffer
 * @return int 0 = success, 1 = success and the buffer was emptied
 */
int Logger_unsafe(const char* str) {
	int retval = 0;
	assert(_logCurrentLine < MAX_LOGLINES);
	strncpy(_logbuffer[_logCurrentLine], str, MAX_LINELENGTH);
	_logbuffer[_logCurrentLine][MAX_LINELENGTH-1] = '\0';
	_logCurrentLine++;
	if(_logCurrentLine >= MAX_LOGLINES) {
		Logger_process_unsafe();
		retval = 1;
	}
	return retval;
}

int Logger(const char* str) {
	pthread_mutex_lock(&_logMutex);
	int retval = Logger_unsafe(str);
	pthread_mutex_unlock(&_logMutex);
	return retval;
}

void Logger_now(const char* str) {
	pthread_mutex_lock(&_logMutex);
	int status = Logger_unsafe(str);
	// if the log didn't flush, do it now:
	if(status != 1) Logger_process_unsafe();
	pthread_mutex_unlock(&_logMutex);
}
