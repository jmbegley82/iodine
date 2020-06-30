#include <stdio.h>
#include "Logger.h"

/** @brief Logger - writes debug information to designated area
 * @details Writes debug information to stdout and/or a file, with consideration
 * for being called by multiple threads at once (pending).
 *
 * @param str (const char*) the c-string to write to output
 * @return void
 */
void Logger(const char* str) {
	// for now, dump to stdout
	printf("%s\n", str);
}
