#include "../../include/parser/header/token_type_checker.h"

bool is_tok_instr(const enum token_t tok_t)
{
	return (tok_t >= INSTRUCTION_START && tok_t < INSTRUCTION_END) ? true : false;
}

bool is_tok_reg(const enum token_t tok_t)
{
	return (tok_t >= REGISTER_START && tok_t < REGISTER_END) ? true : false;
}

bool is_tok_id(const enum token_t tok_t)
{
	return (tok_t == IDENTIFIER) ? true : false;
}

bool is_tok_local_label(const enum token_t tok_beg_t, const enum token_t tok_end_t) 
{
	return (tok_beg_t == LOCAL && tok_end_t == IDENTIFIER) ? true : false;
}

bool is_tok_global_label(const enum token_t tok_beg_t, const enum token_t tok_end_t)
{
	return (tok_beg_t == IDENTIFIER && tok_end_t == LABEL_BEG) ? true : false;
}

bool is_tok_dir(const enum token_t tok_beg_t, const enum token_t tok_end_t) 
{
	return (tok_beg_t == LOCAL && tok_end_t >= DIRECTIVE_START && tok_end_t < DIRECTIVE_END) ? true : false;

}
