#include <stdbool.h>

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

static void ti_init(struct token_iterator *ti, Arena *arena, struct file_buf *f_buf)
{
	ti->arena = arena;
	ti->f_buf = f_buf;
	ti->cur_tok = NULL;
}

static enum line_t identify_first_tok_t(struct token_iterator *ti)
{
	if (!ti)
		handle_error("token iterator pointer passed to dientify_first_tok_t is NULL", FATAL);
	return UNKNOWN_LINE;
}

static struct ast_node *parse_line(struct token_iterator *ti)
{
	struct ast_node *cur_node = tiltyard_calloc(ti->arena, sizeof(*cur_node));

	if (!ti || !ti->arena || !ti->f_buf || !ti->cur_tok)
		handle_error("One of the pointers passed to parse_line in parser.c is NULL", FATAL);
	
	const enum line_t line_t = identify_first_tok_t(ti);

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
		handle_error("An invalid or unknown type of line was found in parse_line func", WARNING);
		return NULL;
	};
}

struct ast_node *parse_program(Arena *arena, struct file_buf *f_buf)
{
	if (!arena || !f_buf)
		handle_error("pointers passed to parse_program are NULL", FATAL);
	
	struct ast_node *root_node = NULL;
	struct ast_node **tail_node = &root_node;

	struct token_iterator ti;
	ti_init(&ti, arena, f_buf);
	ti.cur_tok = get_next_token(ti.arena, ti.f_buf, ti.cur_tok);

	while (1) {
		struct ast_node *node = parse_line(&ti);

		if (!node) break;

		*tail_node = node;
		tail_node = &node->next_node;
	}

	return root_node;
}
