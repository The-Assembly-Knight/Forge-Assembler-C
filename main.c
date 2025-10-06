#include "include/file_io/header/file_i.h"
#include "include/error/handle_error.h"
#include "include/file_io/structs/file_buf.h"
#include "include/parser/structs/ast_node.h"
#include "include/tokenizer/structs/token.h"
#include "libs/tiltyard/include/tiltyard_API.h"
#include "include/tokenizer/header/tokenizer.h"
#include "include/parser/header/parser.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
		handle_error("A path for the file must be specified", FATAL);

	Arena *arena = tiltyard_create(10000); 
	if (!arena)
		handle_error("Arena with the specified size could not be created", FATAL);

	struct file_buf *file_buf = read_input_file(arena, argv[1]);
	
	struct token *root_tok = tokenize_file(arena, file_buf);
	
	if (!root_tok) {
		handle_error("root_tok is null", WARNING);
		return 1;
	}

	struct ast_node *root_node = parse_program(arena, file_buf, root_tok);
	
	printf("root_node type: %i\n", root_node->ast_node_t);

	return 0;
}

