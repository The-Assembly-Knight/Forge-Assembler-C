#include "include/file_io/header/file_i.h"
#include "include/error/handle_error.h"
#include "include/file_io/structs/file_buf.h"
#include "include/parser/header/parser.h"
#include "libs/tiltyard/include/tiltyard_API.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		handle_error("A path for the file must be specified", FATAL);

	Arena *arena = tiltyard_create(1000); 
	if (!arena)
		handle_error("Arena with the specified size could not be created", FATAL);

	struct file_buf *file_buf = read_input_file(arena, argv[1]);
	parse_program(arena, file_buf);

	return 0;
}

