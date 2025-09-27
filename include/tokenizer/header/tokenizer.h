#pragma once

#include "../structs/token_line.h"
#include "../../../libs/tiltyard/include/tiltyard_API.h"
#include "../../file_io/structs/file_buf.h"

struct token *tokenize_file(Arena *arena, struct file_buf *f_buf);
