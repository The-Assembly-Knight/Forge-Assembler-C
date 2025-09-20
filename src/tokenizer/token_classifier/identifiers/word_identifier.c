#include <stddef.h>
#include <string.h>

#include "../../../../include/tokenizer/header/identifiers/word_identifier.h"
#include "../../../../include/tokenizer/structs/keyword.h"
#include "../../../../include/error/handle_error.h"

enum token_t identify_word(struct file_buf *f_buf, struct token *tok)
{
	#define KEYWORD_AMOUNT 7
	#define MAX_KEYWORD_LEN 3

	//static c *keywords[KEYWORD_AMOUNT] = {"MOV", "ADD", "SUB", "JMP", "JE", "JNE", "CMP"};
	static const struct keyword keywords[KEYWORD_AMOUNT] =
		{
			{.word = "JE",	.len = 2},
			{.word = "MOV", .len = 3},
			{.word = "ADD", .len = 3},
			{.word = "SUB", .len = 3},
			{.word = "JMP", .len = 3},
			{.word = "JNE", .len = 3},
			{.word = "CMP", .len = 3},
		};

	if (tok->len > MAX_KEYWORD_LEN)
		return IDENTIFIER;

	if (f_buf->len < tok->start_off + tok->len)
		handle_error("Token overflows f_buf in identify_word", FATAL);
	
	size_t i = 0;
	for (i = 0; i < KEYWORD_AMOUNT; i++) {
		if (tok->len > keywords[i].len) continue;
		if (tok->len < keywords[i].len) break;

		if (strncmp(f_buf->buf + tok->start_off, keywords[i].word, tok->len) == 0)
			return INSTRUCTION;
	}

      return IDENTIFIER;
}
