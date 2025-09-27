#pragma once

#include <stddef.h>

#include "../enums/byte_t.h"
#include "../enums/token_t.h"

#define MAX_TOKEN_LEN 200

struct token {
	struct token *next_tok;

	size_t start_off;
	size_t len;
	enum byte_gp last_b_gp;
	enum token_t type;
};
