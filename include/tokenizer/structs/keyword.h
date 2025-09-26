#pragma once

#include <stddef.h>
#include "../../../include/tokenizer/enums/token_t.h"

struct keyword {
	char *word;
	size_t len;
	enum token_t type;
};
