/* Logger.c
 *
 */

#include <stdio.h>
#include "Logger.h"

/** @brief Write debug information to designated area
 * @details by default logs to stdout, in the future optionally to a file or both, with consideration
 * for being called by multiple threads at once, possibly by implementing a buffer (pending).
 *
 * @param str (const char*) the C-string to write to output
 * @return void
 */
void Logger(const char* str) {
	// for now, dump to stdout
	printf("%s\n", str);
}
