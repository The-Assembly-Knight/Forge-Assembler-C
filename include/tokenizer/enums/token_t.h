#pragma once

enum vague_token_t {
	WORD,
	NUM,
	SYM,
};

enum token_t {
	UNKNOWN,		/* 0 */

	INSTRUCTION,		/* 1 */
	INSTRUCTION_END,	/* 2 */
	IDENTIFIER,		/* 3 */

	LOCAL,			/* 4 */
	GLOBAL,			/* 5 */
	LABEL_BEG,		/* 6 */
	ARG_SEPARATOR,		/* 7 */

	ADD_OP,			/* 8 */
	SUB_OP,			/* 9 */

	HEXADECIMAL_LITERAL,	/* 10 */
	INTEGER_LITERAL,	/* 11 */
	CHAR_LITERAL,		/* 12 */
	STRING_LITERAL,		/* 13 */

	INVALID,		/* 14 */
};
