/* Logger.c
 *
 */

//#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Logger.h"
#include "Timing.h"

#ifndef MAX_LINELENGTH
//! The maximum length of a logbuffer entry
#define MAX_LINELENGTH 4096
#endif //MAX_LINELENGTH

#ifndef MAX_LOGLINES
//! The maximum number of logbuffer entries
#define MAX_LOGLINES 128
#endif //MAX_LOGLINES

pthread_mutex_t _logMutex;	//!< This mutex is used to cover _logbuffer and _logCurrentLine
char* _logbuffer[MAX_LOGLINES];	//!< This buffer holds our log entries
int _logCurrentLine;		//!< This index represents the next entry in _logbuffer that will be written
int _logStatus;			//!< This is used to pause/resume/exit the Logger_autoflush thread
pthread_t _logFlushThread;	//!< This pthread_t holds the Logger_autoflush thread

/**
 * @brief Simple thread that calls Logger_process and then waits a specified amount of time
 * @details If _logStatus is LOG_STOPPED, nothing will be printed.  If _logStatus is LOG_RUNNING,
 * lines will be printed.  If _logStatus is LOG_EXITING, nothing will be printed and this thread will exit.
 */
void* Logger_autoflush(void* arg) {
	while(_logStatus != LOG_EXITING) {
		if(_logStatus == LOG_RUNNING) {
			Logger_process();
		}
		SleepMsec(100); // that seems reasonable and I base that on nothing
	}
#ifdef EXTRADEBUG
	Logger("Logger_autoflush has begun to exit correctly.");
#endif //EXTRADEBUG
	pthread_exit((void*)0);
}

int Logger_init() {
	_logStatus = LOG_STOPPED;
	pthread_mutex_init(&_logMutex, NULL);
	pthread_mutex_lock(&_logMutex);
	for(int i=0; i<MAX_LOGLINES; i++) {
		_logbuffer[i] = malloc(MAX_LINELENGTH);
		memset(_logbuffer[i], 0, MAX_LINELENGTH);
	}
	_logCurrentLine = 0;
	pthread_mutex_unlock(&_logMutex);
	_logStatus = LOG_RUNNING;
	pthread_create(&_logFlushThread, NULL, Logger_autoflush, NULL);
	//pthread_setname_np(_logFlushThread, "LogFlusher");
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
	_logStatus = LOG_EXITING;
	void* status;
	pthread_join(_logFlushThread, &status);
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

void Logger_pause() {
	_logStatus = LOG_STOPPED;
}

void Logger_unpause() {
	_logStatus = LOG_RUNNING;
}

int Logger_status() {
	return _logStatus;
}
