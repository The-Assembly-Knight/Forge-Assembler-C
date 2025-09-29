#pragma once

#include <stdbool.h>

#include "../../tokenizer/structs/token.h"
#include "../structs/ast_node.h"

bool process_instruction_line(struct ast_node *node, struct token *tok);
bool process_label_line	     (struct ast_node *node, struct token *tok);
bool process_directive_line  (struct ast_node *node, struct token *tok);
