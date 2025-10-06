#include <stdio.h>
#include <stdbool.h>

#include "../../include/parser/header/parser.h"
#include "../../include/error/handle_error.h"
#include "../../include/parser/header/line_type_identifier.h"
#include "../../include/parser/header/line_parsers/instruction_line_parser.h"

struct token_iterator {
	Arena *arena;
	struct file_buf *f_buf;
	struct token *cur_tok;
};


static struct token *peek_next_token(struct token *tok)
{
	if (!tok)
		handle_error("tok pointer passed to peek_next_token is NULL", FATAL);
	
	return tok->next_tok;
}

static void ti_init(struct token_iterator *ti, Arena *arena, struct file_buf *f_buf)
{
	ti->arena = arena;
	ti->f_buf = f_buf;
	ti->cur_tok = NULL;
}

static struct ast_node *parse_line(struct file_buf *f_buf, struct token_iterator *ti)
{
	struct ast_node *cur_node = tiltyard_calloc(ti->arena, sizeof(*cur_node));

	if (!ti || !ti->arena || !ti->f_buf || !ti->cur_tok)
		handle_error("One of the pointers passed to parse_line in parser.c is NULL", FATAL);
	
	const enum line_t line_t = identify_line_t(ti);

	switch (line_t) {
	case INSTRUCTION_LINE:
		printf("line is an instruction\n");
		process_instruction_line(cur_node, ti->cur_tok, f_buf);
		return cur_node;		/* Call parse_instruction_line */
	case LOCAL_LABEL_LINE:
		printf("line is a local label\n");
		return NULL;		/* Call parse_label_line */
	case GLOBAL_LABEL_LINE:
		printf("line is global label\n");
		return NULL;		/* Call parse_global_line */
	case DIRECTIVE_LINE:
		printf("line is directive line\n");
		return NULL;		/* Call parse_directive_line */
	default:
		handle_error("An invalid or unknown type of line was found in parse_line func", WARNING);
		return NULL;
	};
}

struct ast_node *parse_program(Arena *arena, struct file_buf *f_buf, struct token *root_tok)
{
	if (!arena || !f_buf)
		handle_error("pointers passed to parse_program are NULL", FATAL);
	
	struct ast_node *root_node = NULL;
	struct ast_node **tail_node = &root_node;

	struct token_iterator ti;
	ti_init(&ti, arena, f_buf);
	ti.cur_tok = root_tok;

	while (1) {
		struct ast_node *node = parse_line(f_buf, &ti);

		if (!node) break;

		*tail_node = node;
		tail_node = &node->next_node;
	}

	return root_node;
}
