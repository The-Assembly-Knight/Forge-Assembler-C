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
	INSTRUCTION_END,	/* 8 */

	REGISTER_START,		/* 9 */
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
	REGISTER_END,		/* 25 */

	DIRECTIVE_START,	/* 26 */
	STR = DIRECTIVE_START,
	TEXT,
	SIZE,
	DIRECTIVE_END,		/* 29 */

	LINE_END,		/* 30 */

	LOCAL_LABEL,		/* 31 */
	GLOBAL_LABEL,		/* 32 */
	LABEL_BEG,		/* 33 */
	ARG_SEPARATOR,		/* 34 */

	BIN_OP_START,		/* 35 */
	ADD_OP = BIN_OP_START,
	SUB_OP,
	BIN_OP_END,		/* 37 */

	HEXADECIMAL_LITERAL,	/* 38 */
	INTEGER_LITERAL,	/* 39 */
	CHAR_LITERAL,		/* 40 */
	STRING_LITERAL,		/* 41 */

	IDENTIFIER,		/* 42 */

	INVALID,		/* 43 */
};
