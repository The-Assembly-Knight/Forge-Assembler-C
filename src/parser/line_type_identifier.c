#include "../../include/parser/header/line_type_identifier.h"

bool is_line_instruction(const enum token_t tok_t)
{
	if (tok_t >= INSTRUCTION_START && tok_t < INSTRUCTION_END)
		return true;
	return false;
}

bool is_line_directive(const enum token_t tok_t)
{
	if (tok_t >= DIRECTIVE_START && tok_t < DIRECTIVE_END)
		return true;
	return false;
}

bool is_line_local_label(const enum token_t tok_t, const enum token_t next_tok_t)
{
	if (tok_t == LOCAL_LABEL && next_tok_t == LABEL_BEG)
		return true;
	return false;
}

bool is_line_global_label(const enum token_t tok_t, const enum token_t next_tok_t)
{
	if (tok_t == IDENTIFIER && next_tok_t == LABEL_BEG)
		return true;
	return false;
}
