#include <ctype.h>

#include "../../include/tokenizer/header/classifier.h"
#include "../../include/error/handle_error.h"
#include "../../include/tokenizer/header/identifiers/num_identifier.h"
#include "../../include/tokenizer/header/identifiers/word_identifier.h"

static enum vague_token_t get_vague_token_t(struct file_buf *f_buf, struct token *tok)
{
	if (!f_buf || !tok)
		handle_error("One of the pointers passed to get_vague_token_t is null", FATAL);

	const char first_b = f_buf->buf[tok->start_off];

	if (isdigit(first_b)) return NUM;
	if (isalpha(first_b)) return WORD;
	return SYM;
}

enum token_t get_token_type(struct file_buf *f_buf, struct token *tok)
{
	enum vague_token_t vague_t = get_vague_token_t(f_buf, tok);
	
	switch (vague_t) {
	case WORD: return identify_word(f_buf, tok);
	case SYM:  return UNKNOWN;
	default:   return identify_number(f_buf, tok);
	}

}
