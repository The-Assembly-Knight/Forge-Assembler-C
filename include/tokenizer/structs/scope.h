#pragma once

#include <stdbool.h>
#include <stddef.h>

enum scope_t {
	NO_SCOPE,
	SINGLE_QUOTE_SCOPE,
	DOUBLE_QUOTE_SCOPE
};

struct scope {
	enum scope_t type;
	bool active;
	size_t continuous_back_slash_count;
};
