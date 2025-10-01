#include "../../include/parser/header/line_processor.h"
#include "../../include/error/handle_error.h"
#include <stdbool.h>
#include <stddef.h>

static bool is_tok_instruction(const enum token_t tok_t)
{
	return tok_t >= INSTRUCTION_START && tok_t < INSTRUCTION_END;
}

static bool is_op_identifier(const enum token_t tok_t)
{
	return tok_t == IDENTIFIER;
}

static bool is_op_register(const enum token_t tok_t)
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

static inline void increase_instr_op_c(size_t *c)
{
	if (!c)
		handle_error("the counter pointer passed to inscrease_instr_op_c is NULL", FATAL);
	(*c)++;
}

static void handle_reg_op(struct token **tok, struct reg *reg)
{
	if (!tok || !(*tok) || !reg)
		handle_error("one of the pointer passed to handle_reg_op is NULL", FATAL);

	reg->type = (*tok)->type;
	reg->size = get_reg_size(*tok);
					
	consume_token(tok);
	if (reg->size != UNKNOWN_S) {
		consume_token(tok);
		consume_token(tok);
	}

}

static void handle_id_op(struct token **tok, struct identifier *id)
{
	if (!tok || !(*tok) || !id)
		handle_error("One of the pointers passed to handle_id_op is NULL", FATAL);
}

static void parse_instr_line_ops(struct token **tok, struct instruction *node)
{
	static const size_t MAX_INSTRUCTION_ARG_C = 4;

	if (!tok)
		handle_error("tok pointer passed to parse_instr_line_ops is NULL", FATAL);
	
	size_t *op_c = &node->operand_c;
	enum token_t cur_tok_t = (*tok)->type;
	bool expecting_op = true;

	while (cur_tok_t != LINE_END) {
		if ((expecting_op && is_op_register(cur_tok_t)) ||
		    (expecting_op && is_op_identifier(cur_tok_t))) {		
			expecting_op = false;

			if (is_op_identifier(cur_tok_t)) {
				struct identifier *id = &node->operands[*op_c].id; 
				node->operands_t[*op_c] = ID;
				handle_id_op(tok, id);
			} else {
				struct reg *reg = &node->operands[*op_c].reg;
				node->operands_t[*op_c] = REG;
				handle_reg_op(tok, reg);
			}
			increase_instr_op_c(op_c);
		} else {
			if (expecting_op)
				handle_error("received something that was not an operator when an operator was expected", FATAL);

			if (*op_c == MAX_INSTRUCTION_ARG_C)
				handle_error("instruction received more than 4 operators", FATAL);

			if (cur_tok_t != ARG_SEPARATOR)
				handle_error("operators are being separated by something that is not an ','", FATAL);

			expecting_op = true;
		}
		update_token_t(&cur_tok_t, *tok);
	}
}

bool process_instruction_line(struct ast_node *node, struct token *tok)
{

	enum token_t cur_tok_t = tok->type;
	
	if (!(is_tok_instruction(cur_tok_t)))
		return false;

	node->ast_node_t = INSTRUCTION_NODE;
	struct instruction *instruction_node = &node->node.instr;
	init_instruction_node(&node->node.instr);
	instruction_node->mnemonic = cur_tok_t;
	
	consume_and_update(&tok, &cur_tok_t);

	bool expecting_op = true;

	size_t *instruction_op_c = &instruction_node->operand_c;
	parse_instr_line_ops(&tok, instruction_node);

	return true;
}
