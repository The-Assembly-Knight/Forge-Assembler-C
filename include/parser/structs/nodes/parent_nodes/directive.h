#pragma once

#include "../../../enums/directive/dir_t.h"
#include "../../../enums/directive/dir_arg_t.h"
#include "../child_nodes/literal.h"
#include "../child_nodes/identifier.h"
#include "../child_nodes/reg.h"

#define MAX_DIR_ARG_C 10

struct directive {
	union arg {
		struct lit lit;
		struct reg reg;
		struct identifier id;
	};
	
	enum dir_t type;
	enum dir_arg_t args_t[MAX_DIR_ARG_C];
	union arg args[MAX_DIR_ARG_C];
};
