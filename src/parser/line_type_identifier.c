#include <stdbool.h>

#include "../../include/parser/header/line_type_identifier.h"

/*
 * Returns true if the given token represents the start of an instruction line.
 */
static bool is_line_instruction(const enum token_t tok_t)
{
	return (tok_t >= INSTRUCTION_START && tok_t < INSTRUCTION_END);
}

/*
 * Returns true if the given token represents the start of a directive line.
 */
static bool is_line_directive(const enum token_t tok_t)
{
	return (tok_t >= DIRECTIVE_START && tok_t < DIRECTIVE_END);
}

/*
 * Returns true if the first and second token represent the start of a local label line.
 */
static bool is_line_local_label(const enum token_t tok_t, const enum token_t next_tok_t)
{
	return (tok_t == LOCAL_LABEL && next_tok_t == LABEL_BEG);
}

/*
 * Returns true if the first and second token represent the start of a global label line.
 */
static bool is_line_global_label(const enum token_t tok_t, const enum token_t next_tok_t)
{
	return (tok_t == IDENTIFIER && next_tok_t == LABEL_BEG);
}

/*
 * Determines the type of line based on its first or first and second tokens.
 *
 * Returns:
 *	- INSTRUCTION_LINE  if it starts as an instruction.
 *	- DIRECTIVE_LINE    if it starts as a directive.
 *	- LOCAL_LABEL_LINE  if it starts as a local label.
 *	- GLOBAL_LABEL_LINE if it starts as a global label.
 *	- INVALID_LINE if none of the above.
 *
 * Note: Only the first or first and second tokens of the line are taken into account.
 */
enum line_t identify_line_type(const enum token_t first_token_type, const enum token_t second_token_type)
{
	if (is_line_instruction(first_token_type))
		return INSTRUCTION_LINE;

	if (is_line_directive(first_token_type))
		return DIRECTIVE_LINE;

	if (is_line_local_label(first_token_type, second_token_type))
		return LOCAL_LABEL_LINE;

	if (is_line_global_label(first_token_type, second_token_type))
		return GLOBAL_LABEL_LINE;

	return INVALID_LINE;
}
