#include <stddef.h>
#include <stdio.h>

#include "../../../include/file_io/header/file_i.h"
#include "../../../include/error/handle_error.h"

static void *alloc_or_fatal(Arena *arena, size_t size)
{
	void *p = tiltyard_calloc(arena, size);
	if (!p)
		handle_error("Memory allocation failed", FATAL);
	return p;
}

static size_t get_file_size(FILE *f)
{
	if (!f)
		handle_error("File could not be opened", FATAL);

	fseek(f, 0, SEEK_END);
	long f_size = ftell(f);

	if (f_size < 0)
		handle_error("Failed to get file size", FATAL);

	rewind(f);
	return (size_t)f_size;
}

struct file_buf *read_input_file(Arena *arena, const char *path)
{
	if (!arena) handle_error("Arena passed to read_input_file is a null pointer", FATAL);
	if (!path)  handle_error("Path passed to read_input_file is a null pointer" , FATAL);

	FILE *f = fopen(path, "rb");
	if (!f) handle_error("File could not be opened", FATAL);

	const size_t f_size = get_file_size(f);
	if (f_size == 0) handle_error("File is empty", WARNING);
	
	struct file_buf *file_buf = alloc_or_fatal(arena, sizeof(*file_buf));
	file_buf->buf = alloc_or_fatal(arena, f_size + 1);

	file_buf->offset = 0;
	file_buf->len = f_size;

	
	const size_t bytes_read = fread(file_buf->buf, 1, f_size, f);
	file_buf->buf[f_size] = '\0';
	if (bytes_read != f_size) handle_error("The file could not be read entirely", FATAL);

	fclose(f);
	return file_buf;

}
