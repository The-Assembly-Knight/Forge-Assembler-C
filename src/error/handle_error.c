#include <stdio.h>
#include <stdlib.h>

#include "../../include/error/handle_error.h"

/* handle errors/warnings
 * 
 * Returns:
 * - Nothing.
 * 
 * If severity is FATAL print error + abort. Otherwise, just
 * print warning message without aborting.
 */

void handle_error(const char *error_message, const enum error_t severity)
{	if (severity == FATAL) {
		fprintf(stderr, "ERROR: %s\n", error_message);
		abort();
	}

	fprintf(stderr, "WARNING: %s\n", error_message);
}
