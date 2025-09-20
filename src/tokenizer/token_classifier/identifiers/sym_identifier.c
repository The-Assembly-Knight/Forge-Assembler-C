#include "../../../../include/tokenizer/header/identifiers/sym_identifier.h"
#include "../../../../include/error/handle_error.h"

enum token_t identify_sym(struct file_buf *f_buf, struct token *tok)
{
	const char first_b = f_buf->buf[tok->start_off];

	if (tok->len > 1)
		handle_error("There is a symbol with len > 1", WARNING);

	switch (first_b) {
	case '.': return LOCAL;
	case ':': return LABEL_BEG;
	case ',': return ARG_SEPARATOR;
	case '"': return STRING_LITERAL;
	case '\'': return CHAR_LITERAL;
	case '\n': return INSTRUCTION_END;
	}

	return INVALID;
}
