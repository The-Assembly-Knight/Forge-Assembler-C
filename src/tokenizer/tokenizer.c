#include <stdbool.h>

#include "../../include/tokenizer/header/tokenizer.h"
#include "../../include/error/handle_error.h"
#include "../../include/tokenizer/enums/byte_t.h"
#include "../../include/tokenizer/table/b_gp.h"
#include "../../include/tokenizer/structs/scope.h"
#include "../../include/tokenizer/header/classifier.h"

static void clean_token(struct token *token)
{
	static struct token clean_tok = {
	.start_off = 0,
	.len = 0,
	.last_b_gp = 0,
	.type = 0,
	};
	*token = clean_tok;
}

static void advance_file_buffer_offset(struct file_buf *f_buf)
{
	if (!f_buf)
		handle_error("The pointer to f_buf passed to advance_file_buffer_offset is null", FATAL);

	if (f_buf->offset > f_buf->len - 1)
		handle_error("Overflow of f_buf in advance_file_buffer_offset", FATAL);

	f_buf->offset++;
}

static void increase_token_length(struct token *tok)
{
	if (!tok)
		handle_error("The pointer to tok passed to increase_token_length is null", FATAL);

	if (tok->len >= MAX_TOKEN_LEN)
		handle_error("The length of the token is greater than MAX_TOKEN_LENGTH", FATAL);

	tok->len++;
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

	increase_token_length(token);
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

static void handle_standalone_byte(struct file_buf *f_buf, struct token *token, bool *tok_end)
{
	if (token->len > 0) {
		*tok_end = true;
		return;
	}

	token->start_off = f_buf->offset;
	increase_token_length(token);
	advance_file_buffer_offset(f_buf);
	*tok_end = true;
}

static void handle_scope_byte(struct file_buf *f_buf, struct token *token, bool *tok_end, struct scope *scope, enum scope_t scope_t)
{
	if (!f_buf || !token || !tok_end || !scope)
		handle_error("One of the pointers passed to handle_scope_byte is null", FATAL);
	
	if (token->len > 0 && scope->active == false) {
		*tok_end = true;
		return;
	}
	
	if (token->len == 0) {
		scope->active = true;
		scope->type = scope_t;
		increase_token_length(token);
		advance_file_buffer_offset(f_buf);
		return;
	}

	if (scope->type == scope_t && scope->continuous_back_slash_count % 2 == 0) {
		scope->type = NO_SCOPE;
		scope->active = false;
		increase_token_length(token);
		advance_file_buffer_offset(f_buf);
		*tok_end = true;
		return;
	} else {
		increase_token_length(token);
		advance_file_buffer_offset(f_buf);
		return;
	}
}

static void handle_comment_byte(struct file_buf *f_buf, struct token *token, bool *tok_end)
{
	if (token->len != 0) {
		*tok_end = true;
		return;
	}
	
	enum byte_gp current_b_gp = COMMENT_B;



	do {
		advance_file_buffer_offset(f_buf);
		current_b_gp = get_byte_group(f_buf->buf[f_buf->offset]);
	} while (current_b_gp != NEW_LINE_B && current_b_gp != EOF_B);
}

static void handle_byte(const enum byte_gp b_gp, struct file_buf *f_buf, struct token *token, bool *tok_end, struct scope *scope)
{
	if (!f_buf)
		handle_error("The pointer to f_buf passed to handle_byte is null", FATAL);

	if (!token)
		handle_error("The pointer to token passed to handle_byte is null", FATAL);

	if (!tok_end)
		handle_error("The pointer to tok_end passed to handle_byte is null", FATAL);

	if (!scope)
		handle_error("The pointer to scope passed to handle_byte is null", FATAL);
	
	if (scope->active && b_gp != SINGLE_QUOTE_B && b_gp != DOUBLE_QUOTE_B) {
		if (f_buf->buf[f_buf->offset] == '\\') {
			scope->continuous_back_slash_count++;
		} else {
			scope->continuous_back_slash_count = 0;
		}
		
		increase_token_length(token);
		advance_file_buffer_offset(f_buf);
		return;
	}
	
	switch (b_gp) {
	case REGULAR_B:
		handle_regular_byte(f_buf, token);
		return;
	case DELIMITER_B:
		handle_delimiter_byte(f_buf, token, tok_end);
		return;
	case STANDALONE_B:
	case NEW_LINE_B:
		handle_standalone_byte(f_buf, token, tok_end);
		return;
	case SINGLE_QUOTE_B:
		handle_scope_byte(f_buf, token, tok_end, scope, SINGLE_QUOTE_SCOPE);
		return;
	case DOUBLE_QUOTE_B:
		handle_scope_byte(f_buf, token, tok_end, scope, DOUBLE_QUOTE_SCOPE);
		return;
	case COMMENT_B:
		handle_comment_byte(f_buf, token, tok_end);
		return;
	case EOF_B: return;
	default:
		handle_error("A byte type not supported was found in handle_byte", WARNING);
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

	char b = 0;
	enum byte_gp b_gp = 0;
	bool tok_end = false;
	struct scope scope = { .type = NO_SCOPE, .active = false, };

	do {
		if (f_buf->offset > f_buf->len)
			handle_error("Overflow of f_buf in get_next_token", FATAL);

		b = f_buf->buf[f_buf->offset];
		b_gp = get_byte_group(b);
		handle_byte(b_gp, f_buf, token, &tok_end, &scope);
	} while (!tok_end && b_gp != EOF_B && b_gp != NEW_LINE_B && f_buf->offset < f_buf->len);

	if (tok_end) token->type = get_token_type(f_buf, token);

	return token;
}
