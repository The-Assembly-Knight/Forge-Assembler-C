#pragma once

#include "nodes/parent_nodes/instruction.h"
#include "nodes/parent_nodes/directive.h"
#include "../enums/ast/ast_node_t.h"

struct ast_node {
	enum ast_node_t ast_node_t;
	union {
		struct instruction instr;
		struct directive dir;
	} node;
	ast_node *next_node;
};
