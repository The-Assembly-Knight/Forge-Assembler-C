#include <stdbool.h>

#include "../../include/tokenizer/header/tokenizer.h"
#include "../../include/error/handle_error.h"
#include "../../include/tokenizer/enums/byte_t.h"
#include "../../include/tokenizer/table/b_gp.h"

static void clean_token(struct token *token)
{
	static struct token clean_tok = {
	.start_off = 0,
	.len = 0,
	.last_b_gp = 0,
	};
	*token = clean_tok;
}

static void advance_file_buffer_offset(struct file_buf *f_buf)
{
	if (!f_buf)
		handle_error("The pointer to f_buf passed to advance_file_buffer_offset is null", FATAL);

	if (f_buf->offset == f_buf->len)
		handle_error("Overflow of f_buf in advance_file_buffer_offset", FATAL);

	f_buf->offset++;
}

static enum byte_gp get_byte_group(const char b)
{
	if ((int)b < 0)
		handle_error("A negative char was found", FATAL);
	return b_gp_table[(unsigned char)b];
}

static void handle_regular_byte(struct file_buf *f_buf, struct token *token)
{
	if (!f_buf || !token)
		handle_error("One of the pointers passed to handle_regular_byte is null", FATAL);
	
	if (token->len == 0) token->start_off = f_buf->offset;

	token->len++;
	token->last_b_gp = REGULAR_B;
	advance_file_buffer_offset(f_buf);
}

static void handle_delimiter_byte(struct file_buf *f_buf, struct token *token, bool *tok_end)
{
	if (token->len != 0)
		*tok_end = true;

	enum byte_gp current_b_gp = DELIMITER_B;
	
	do {
		advance_file_buffer_offset(f_buf);
		current_b_gp = get_byte_group(f_buf->buf[f_buf->offset]);
	} while (current_b_gp == DELIMITER_B);
}

static void handle_byte(const enum byte_gp b_gp, struct file_buf *f_buf, struct token *token, bool *tok_end)
{
	if (!f_buf)
		handle_error("The pointer to f_buf passed to handle_byte is null", FATAL);

	if (!token)
		handle_error("The pointer to token passed to handle_byte is null", FATAL);

	if (!tok_end)
		handle_error("The pointer to tok_end passed to handle_byte is null", FATAL);

	switch (b_gp) {
	case REGULAR_B:
		handle_regular_byte(f_buf, token);
		return;
	case DELIMITER_B:
		handle_delimiter_byte(f_buf, token, tok_end);
		return;
	default:
		return;
	}
}

struct token *get_next_token(Arena *arena, struct file_buf *f_buf, struct token *token)
{
	if (!arena) handle_error("The pointer to the arena provided to tokenize_next_line func is null", FATAL);
	if (!f_buf) handle_error("The pointer to the file buffer provided to tokenize_next_line func is a null pointer", FATAL);

	if (!token) {
		token = tiltyard_calloc(arena, sizeof(struct token));
	} else {
		clean_token(token);
	}

	char b = f_buf->buf[f_buf->offset];
	enum byte_gp b_gp = get_byte_group(b);
	bool tok_end = false;
	
	do {
		b = f_buf->buf[f_buf->offset];
		b_gp = get_byte_group(b);

		handle_byte(b_gp, f_buf, token, &tok_end);
	} while (!tok_end &&  b_gp != EOF_B);

	return token;
}

