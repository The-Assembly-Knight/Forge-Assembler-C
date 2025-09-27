#include <stdio.h>

#include "include/file_io/header/file_i.h"
#include "include/error/handle_error.h"
#include "include/file_io/structs/file_buf.h"
#include "include/tokenizer/structs/token.h"
#include "libs/tiltyard/include/tiltyard_API.h"
#include "include/tokenizer/header/tokenizer.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		handle_error("A path for the file must be specified", FATAL);

	Arena *arena = tiltyard_create(1000); 
	if (!arena)
		handle_error("Arena with the specified size could not be created", FATAL);

	struct file_buf *file_buf = read_input_file(arena, argv[1]);
	
	struct token *root_tok = tokenize_file(arena, file_buf);
	
	if (!root_tok) {
		handle_error("root_tok is null", WARNING);
		return 1;
	}

	printf("this is the len of root_tok: %zu\n", root_tok->len);
	printf("this is the type of root_tok: %i\n", root_tok->type);

	struct token *cur_tok = root_tok;
	int tok_c = 0;

	while (1) {
		tok_c++;
		cur_tok = cur_tok->next_tok;
		if (!cur_tok) break;
	}

	printf("Amount of tok: %i\n", tok_c);
	

	return 0;
}

