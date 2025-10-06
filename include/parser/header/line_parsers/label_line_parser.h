#pragma once

#include <stdbool.h>

#include "../../../tokenizer/structs/token.h"
#include "../../structs/ast_node.h"
#include "../../../file_io/structs/file_buf.h"

bool process_label_line(struct ast_node *node, struct token *tok, struct file_buf *f_buf);
