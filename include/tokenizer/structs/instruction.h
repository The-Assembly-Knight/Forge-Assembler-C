#pragma once

#include <stddef.h>

#include "../enums/instruction_t.h"
#include "../enums/instruction_size.h"

struct instruction {
	instruction_t type;
	instruction_size size;
	size_t argc;
};
