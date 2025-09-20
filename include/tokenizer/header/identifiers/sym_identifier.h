#pragma once

#include "../../enums/token_t.h"
#include "../../structs/token.h"
#include "../../../file_io/structs/file_buf.h"

enum token_t identify_sym(struct file_buf *f_buf, struct token *tok);
	
