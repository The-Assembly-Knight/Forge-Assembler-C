#pragma once

#include <stdbool.h>
#include "../../tokenizer/header/tokenizer.h"

bool is_line_instruction (const enum token_t tok_t);
bool is_line_directive   (const enum token_t tok_t);
bool is_line_local_label (const enum token_t tok_t, const enum token_t next_tok_t);
bool is_line_global_label(const enum token_t tok_t, const enum token_t next_tok_t);

