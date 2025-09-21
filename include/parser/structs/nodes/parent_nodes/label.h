#pragma once

#include "../child_nodes/identifier.h"
#include "../../ast_node.h"

struct label {
	struct identifier id;
	struct ast_node *target;
	size_t address;
	bool local;
};
