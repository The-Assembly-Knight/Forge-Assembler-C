#pragma once

#include "../../../enums/literal/lit_t.h"

struct lit {
	enum lit_t value_t;
	union {
		char c;
		char *s;
		int i;
	} value;
};
