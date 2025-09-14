#pragma once

enum error_t {
	FATAL,
	WARNING,
};

void handle_error(const char *error_message, const enum error_t severity);
