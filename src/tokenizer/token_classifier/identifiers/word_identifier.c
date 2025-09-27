#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../../../../include/tokenizer/header/identifiers/word_identifier.h"
#include "../../../../include/tokenizer/structs/keyword.h"
#include "../../../../include/error/handle_error.h"

enum token_t identify_word(struct file_buf *f_buf, struct token *tok)
{
	#define KEYWORD_AMOUNT 26
	#define MAX_KEYWORD_LEN 3

	static const struct keyword keywords[KEYWORD_AMOUNT] =
		{
			{.word = "JE", .len = 2, .type = JE},
			{.word = "R8", .len = 2, .type = R8},
			{.word = "R9", .len = 2, .type = R9},
			{.word = "MOV", .len = 3, .type = MOV},
			{.word = "ADD", .len = 3, .type = ADD},
			{.word = "SUB", .len = 3, .type = SUB},
			{.word = "JMP", .len = 3, .type = JMP},
			{.word = "JNE", .len = 3, .type = JNE},
			{.word = "CMP", .len = 3, .type = CMP},
			{.word = "RAX", .len = 3, .type = RAX},
			{.word = "RCX", .len = 3, .type = RCX},
			{.word = "RDX", .len = 3, .type = RDX},
			{.word = "RBX", .len = 3, .type = RBX},
			{.word = "RSI", .len = 3, .type = RSI},
			{.word = "RDI", .len = 3, .type = RDI},
			{.word = "RSP", .len = 3, .type = RSP},
			{.word = "RBP", .len = 3, .type = RBP},
			{.word = "R10", .len = 3, .type = R10},
			{.word = "R11", .len = 3, .type = R11},
			{.word = "R12", .len = 3, .type = R12},
			{.word = "R13", .len = 3, .type = R13},
			{.word = "R14", .len = 3, .type = R14},
			{.word = "R15", .len = 3, .type = R15},
			{.word = ".STR",.len = 3, .type = STR},
			{.word = ".SIZE", .len = 4, .type = SIZE},
			{.word = ".TEXT", .len = 4, .type = TEXT},
		};

	if (tok->len > MAX_KEYWORD_LEN)
		return (f_buf->buf[tok->start_off] == '.') ? LOCAL_LABEL : IDENTIFIER;

	if (f_buf->len < tok->start_off + tok->len)
		handle_error("Token overflows f_buf in identify_word", FATAL);
	
	size_t i = 0;
	for (i = 0; i < KEYWORD_AMOUNT; i++) {
		if (tok->len > keywords[i].len) continue;
		if (tok->len < keywords[i].len) break;

		if (strncmp(f_buf->buf + tok->start_off, keywords[i].word, tok->len) == 0)
			return keywords[i].type;
	}

	
	return IDENTIFIER;
}
