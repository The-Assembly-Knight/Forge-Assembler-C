#include <stdbool.h>
#include <stdio.h>

#include "../../include/parser/header/parser.h"
#include "../../include/error/handle_error.h"
#include "../../include/tokenizer/header/tokenizer.h"
#include "../../include/parser/header/token_type_checker.h"

struct token_iterator {
	Arena *arena;
	struct file_buf *f_buf;
	struct token *cur_tok;
};

enum line_t {
	UNKNOWN_LINE,
	INSTRUCTION_LINE,
	LOCAL_LABEL_LINE,
	GLOBAL_LABEL_LINE,
	DIRECTIVE_LINE,
	INVALID_LINE,
};

static void it_init(struct token_iterator *ti, Arena *arena, struct file_buf *f_buf)
{
	ti->arena = arena;
	ti->f_buf = f_buf;
	ti->cur_tok = NULL;
}

static enum line_t identify_first_tok_t(struct token_iterator *it)
{
	return UNKNOWN_LINE;
}

static struct ast_node *parse_line(struct token_iterator *it)
{
	if (!it || !it->arena || !it->f_buf || !it->cur_tok)
		handle_error("One of the pointers passed to parse_line in parser.c is NULL", FATAL);
	
	const enum line_t line_t = identify_first_tok_t(it);

	switch (line_t) {
	case INSTRUCTION_LINE:
		return NULL;		/* Call parse_instruction_line */
	case LOCAL_LABEL_LINE:
		return NULL;		/* Call parse_label_line */
	case GLOBAL_LABEL_LINE:
		return NULL;		/* Call parse_global_line */
	case DIRECTIVE_LINE:
		return NULL;		/* Call parse_directive_line */
	default:
		handle_error("An invalid or unknown type of line was found in parse_line func", FATAL);
	};

	return NULL;
}

struct ast_node *parse_program(Arena *arena, struct file_buf *f_buf)
{
	if (!arena || !f_buf)
		handle_error("pointers passed to parse_program are NULL", FATAL);
	
	struct ast_node *root_node = NULL;
	struct ast_node *cur_node = NULL;

	struct token_iterator it;
	it_init(&it, arena, f_buf);
	it.cur_tok = get_next_token(it.arena, it.f_buf, it.cur_tok);

	if (root_node == NULL) {
		root_node = parse_line(&it);
		cur_node = root_node;
	} else {
		cur_node = cur_node->next_node;
	}
		
	return NULL;
}
