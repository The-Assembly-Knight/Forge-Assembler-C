#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>

#include "../../../../include/tokenizer/header/identifiers/num_identifier.h"
#include "../../../../include/error/handle_error.h"


#define HEX_DIGITS_AMOUNT 22

static bool is_hex_digit(const char b)
{
	return	(b >= '0' && b <= '9') ||
		(b >= 'a' && b <= 'f') ||
		(b >= 'A' && b <= 'F');
}

static bool is_num_hex(const char *buf, const size_t tok_start, const size_t tok_len)
{
	size_t offset = 0;
	char current_b = buf[tok_start + offset];
	
	if (tok_len < 3) return false;
	if (current_b != '0') return false;

	offset++;
	current_b = buf[tok_start + offset];

	if (current_b != 'x' && current_b != 'X') return false;

	while (offset < tok_len - 1) {
		offset++;
		current_b = buf[tok_start + offset];

		if (!is_hex_digit(current_b)) {
			return false;
		}
	}

	return true;
}

static bool is_num_int(const char *buf, const size_t tok_start, const size_t tok_len)
{
	if (tok_len == 1) return true;

	size_t offset = 0;
	char current_b = buf[tok_start + offset];

	if (current_b == '0') return false;


	while (offset < tok_len - 1) {
		offset++;
		current_b = buf[tok_start + offset];
		if (!isdigit(current_b)) return false;
	}
	return true;
}

enum token_t identify_number(struct file_buf *f_buf, struct token *tok)
{
	if (!f_buf || !tok)
		handle_error("One of the pointers passed to identify_number is null", FATAL);

	if (is_num_hex(f_buf->buf, tok->start_off, tok->len))
		return HEXADECIMAL_LITERAL;

	if (is_num_int(f_buf->buf, tok->start_off, tok->len))
		return INTEGER_LITERAL;

	return INVALID;
}
