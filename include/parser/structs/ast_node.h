#pragma once

#include "nodes/parent_nodes/instruction.h"
#include "nodes/parent_nodes/directive.h"
#include "nodes/parent_nodes/label.h"
#include "../enums/ast/ast_node_t.h"

struct ast_node {
	enum ast_node_t ast_node_t;
	union {
		struct instruction instr;
		struct directive dir;
		struct label label;
	} node;
	struct ast_node *next_node;
};
