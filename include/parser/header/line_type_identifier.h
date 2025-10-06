#pragma once

#include "../../tokenizer/header/tokenizer.h"
#include "../enums/line_t.h"

enum line_t identify_line_type(const enum token_t first_token_type, const enum token_t second_token_type);

