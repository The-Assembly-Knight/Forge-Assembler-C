#pragma once

#include <stddef.h>
#include "../enums/byte_t.h"

struct token {
	size_t start_off;
	size_t len;
	enum byte_gp last_b_gp;
};
