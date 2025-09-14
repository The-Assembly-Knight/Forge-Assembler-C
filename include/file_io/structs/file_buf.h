#pragma once

#include <stddef.h>

struct file_buf {
	char* buf;
	size_t len;
	size_t offset;
};
