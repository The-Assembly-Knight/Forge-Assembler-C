#include "../../include/parser/header/line_processor.h"
#include "../../include/error/handle_error.h"
#include <stdbool.h>

static bool is_tok_instruction(const enum token_t tok_t)
{
	return tok_t >= INSTRUCTION_START && tok_t < INSTRUCTION_END;
}

static bool is_arg_identifier(const enum token_t tok_t)
{
	return tok_t == IDENTIFIER;
}

static bool is_arg_register(const enum token_t tok_t)
{
	return tok_t >= REGISTER_START && tok_t < REGISTER_END;
}

static void init_instruction_node(struct instruction *instruction_node)
{
	instruction_node->operand_c = 0;
	instruction_node->mnemonic = 0;
}

static struct token *peek_next_token(struct token *cur_tok)
{
	if (!cur_tok)
		handle_error("cur_tok pointer passed to peek_next_token is NULL", FATAL);

	return cur_tok->next_tok;
}

static void consume_token(struct token **tok)
{
	if (!tok)
		handle_error("tok pointer passed to consume_token is NULL", FATAL);

	*tok = (*tok)->next_tok;
}

static void update_token_t(enum token_t *tok_t, struct token *tok)
{
	*tok_t = tok->type;
}

static void consume_and_update(struct token **tok, enum token_t *tok_t)
{
	consume_token(tok);
	update_token_t(tok_t, *tok);
}

static bool get_reg_size(struct token *reg_tok)
{
	if (!reg_tok)
		handle_error("reg_tok passed to get_reg_size is NULL", FATAL);

	struct token *next_tok = peek_next_token(reg_tok);
	if (!next_tok || next_tok->type != REG_SIZE_SPECIFIER)
		return UNKNOWN_S;

	next_tok = peek_next_token(next_tok);
	if (!next_tok || next_tok->type != INTEGER_LITERAL)
		return UNKNOWN_S;

	return UNKNOWN_S;
}


bool process_instruction_line(struct ast_node *node, struct token *tok)
{
	const size_t MAX_INSTRUCTION_ARG_C = 4;

	enum token_t cur_tok_t = tok->type;
	
	if (!(is_tok_instruction(cur_tok_t)))
		return false;

	node->ast_node_t = INSTRUCTION_NODE;
	struct instruction *instruction_node = &node->node.instr;
	init_instruction_node(&node->node.instr);
	instruction_node->mnemonic = cur_tok_t;
	
	consume_and_update(&tok, &cur_tok_t);

	bool expecting_arg = true;

	size_t *instruction_op_c = &instruction_node->operand_c;
	while (cur_tok_t != LINE_END) {
		if (expecting_arg) {
			enum op_t *arg_t = &instruction_node->operands_t[*instruction_op_c];
			if (is_arg_register(cur_tok_t)) {
				expecting_arg = false;
				struct reg *reg = &instruction_node->operands[*instruction_op_c].reg;

				(*instruction_op_c)++;
				*arg_t = REG;
				reg->type = cur_tok_t;
				reg->size = get_reg_size(tok);
					
				consume_token(&tok);
				if (reg->size != UNKNOWN_S) {
					consume_token(&tok);
					consume_token(&tok);
				}

			} else if (is_arg_identifier(cur_tok_t)) {
				expecting_arg = false;
				struct identifier *id = &instruction_node->operands[*instruction_op_c].id;

				(*instruction_op_c)++;
				*arg_t = ID;			
			} else {
				handle_error("an instruction has one or more arguments that are neither identifiers nor registers", WARNING);
				return false;
			}
		} else {
			if (*instruction_op_c == MAX_INSTRUCTION_ARG_C) {
				handle_error("an instruction has over 4 arguments", WARNING);
				return false;
			}

			if (cur_tok_t != ARG_SEPARATOR) {
				handle_error("instruction arguments are not being separated by ','", WARNING);
				return false;
			}

			expecting_arg = true;
			consume_token(&tok);
		}
		update_token_t(&cur_tok_t, tok);
	}

	return true;
}
