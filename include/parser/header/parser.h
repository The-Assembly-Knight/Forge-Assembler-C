#pragma once

#include "../structs/ast_node.h"
#include "../../file_io/structs/file_buf.h"
#include "../../tokenizer/structs/token.h"
#include "../../../libs/tiltyard/include/tiltyard_API.h"

struct ast_node *parse_program(Arena *arena, struct file_buf *f_buf);
