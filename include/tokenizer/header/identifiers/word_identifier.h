#pragma once

#include "../../enums/token_t.h"
#include "../../../file_io/structs/file_buf.h"
#include "../../structs/token.h"

enum token_t identify_word(struct file_buf *f_buf, struct token *tok);
