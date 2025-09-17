#pragma once

#include "../structs/token.h"
#include "../enums/token_t.h"
#include "../../file_io/header/file_i.h"

enum token_t get_token_type(struct file_buf *f_buf, struct token *tok);
