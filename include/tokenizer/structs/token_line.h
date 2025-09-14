#pragma once

#include <stddef.h>

#include "token.h"

#define MAX_TOKEN_AMOUNT 30

struct token_line {
	struct token tokens[MAX_TOKEN_AMOUNT];
	size_t token_c;
};
