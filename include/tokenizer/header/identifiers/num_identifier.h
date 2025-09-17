#pragma once

#include "../../../file_io/structs/file_buf.h"
#include "../../structs/token.h"
#include "../../enums/token_t.h"

enum token_t identify_number(struct file_buf *f_buf, struct token *tok);
