#pragma once

enum vague_token_t {
	WORD,
	NUM,
	SYM,
};

enum token_t {
	UNKNOWN,		/* 0 */

	INSTRUCTION_START,	/* 1 */
	JE = INSTRUCTION_START,
	MOV,
	ADD,
	SUB,
	JMP,
	JNE,
	CMP,
	INSTRUCTION_END,	/* 2 */

	REGISTER_START,		/* 3 */
	RAX = REGISTER_START,
	RCX,
	RDX,
	RBX,
	RSI,
	RDI,
	RSP,
	RBP,
	R8,
	R9,
	R10,
	R11,
	R12,
	R13,
	R14,
	R15,
	REGISTER_END,

	DIRECTIVE_START,
	STR = DIRECTIVE_START,
	TEXT,
	SIZE,
	DIRECTIVE_END,

	LINE_END,		/* 2 */
	IDENTIFIER,		/* 3 */
	REGISTER,		/* 4 */

	LOCAL_LABEL,		/* 4 */
	GLOBAL_LABEL,		/* 5 */
	LABEL_BEG,		/* 6 */
	ARG_SEPARATOR,		/* 7 */

	ADD_OP,			/* 8 */
	SUB_OP,			/* 9 */

	HEXADECIMAL_LITERAL,	/* 10 */
	INTEGER_LITERAL,	/* 11 */
	CHAR_LITERAL,		/* 12 */
	STRING_LITERAL,		/* 13 */

	DIRECTIVE,
	INVALID,		/* 15 */
};
