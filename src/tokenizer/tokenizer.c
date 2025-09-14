#include "../../include/tokenizer/header/tokenizer.h"
#include "../../include/error/handle_error.h"

static struct token_line get_clean_token_line(void)
{
	static const struct token_line cleaned_tok_line = {
	.tokens = {0},
	.token_c = 0,
	};

	return cleaned_tok_line;
}

struct token_line *tokenize_next_line(Arena *arena, struct file_buf *f_buf, struct token_line **tok_line)
{
	if (!tok_line)
		handle_error("Pointer to tok_line passed to tokenize_next_line is null", FATAL);

	if (!*tok_line)
		*tok_line = tiltyard_calloc(arena, sizeof(tok_line));
	else
		**tok_line = get_clean_token_line();

	return *tok_line;
}
