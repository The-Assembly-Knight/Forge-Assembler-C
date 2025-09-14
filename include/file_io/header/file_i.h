#pragma once

#include "../../../libs/tiltyard/include/tiltyard_API.h"
#include "../structs/file_buf.h"

struct file_buf *read_input_file(Arena *arena, const char *path);
