#pragma once

#include <stdbool.h>
#include "../../tokenizer/header/tokenizer.h"

bool is_tok_instr(const enum token_t tok_t);
bool is_tok_reg  (const enum token_t tok_t);
bool is_tok_dir	 (const enum token_t f_tok_t, const enum token_t sec_tok_t);
bool is_tok_id	 (const enum token_t tok_t);
bool is_tok_local_label (const enum token_t tok_beg_t, const enum token_t tok_end_t);
bool is_tok_global_label(const enum token_t tok_beg_t, const enum token_t tok_end_t);


