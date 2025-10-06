#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "../../../include/parser/header/line_parsers/instruction_line_parser.h"
#include "../../../include/error/handle_error.h"

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

static void handle_id_op(struct token **tok, struct identifier *id, struct file_buf *f_buf)
{
	if (!tok || !(*tok) || !id || !f_buf)
		handle_error("One of the pointers passed to handle_id_op is NULL", FATAL);
	
	if ((*tok)->type != IDENTIFIER)
		handle_error("A token that is not an identifier was passed to handle_id_op", WARNING);

	if ((*tok)->len > MAX_IDENTIFIER_LEN)
		handle_error("Identifier surpasses MAX_IDENTIFIER_LEN", FATAL);
	
	strncpy(id->name, f_buf->buf + (*tok)->start_off, (*tok)->len);
	id->name[(*tok)->start_off] = '\0';

	consume_token(tok);
}

static void parse_instr_line_mnemonic(struct token **tok, struct instruction *node)
{
	if (!tok || !(*tok) || !node)
		handle_error("One of the pointers passed to parse_instr_line_mnemonic is NULL", FATAL);

	node->mnemonic = (*tok)->type;
	consume_token(tok);
}

static void parse_instr_line_ops(struct token **tok, struct instruction *node, struct file_buf *f_buf)
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
				handle_id_op(tok, id, f_buf);
			} else {
				struct reg *reg = &node->operands[*op_c].reg;
				node->operands_t[*op_c] = REG;
				handle_reg_op(tok, reg);
			}
			(*op_c)++;
		} else {
			if (expecting_op)
				handle_error("received something that was not an operator when an operator was expected", FATAL);

			if (*op_c == MAX_INSTRUCTION_ARG_C)
				handle_error("instruction received more than 4 operators", FATAL);

			if (cur_tok_t != ARG_SEPARATOR)
				handle_error("operators are being separated by something that is not an ','", FATAL);

			consume_token(tok);
			expecting_op = true;
		}
		update_token_t(&cur_tok_t, *tok);
	}
}

bool process_instruction_line(struct ast_node *node, struct token *tok, struct file_buf *f_buf)
{
	enum token_t cur_tok_t = tok->type;
	
	if (is_tok_instruction(cur_tok_t)) {
		node->ast_node_t = INSTRUCTION_NODE;
	} else {
		return false;
	}


	struct instruction *instruction_node = &node->node.instr;
	init_instruction_node(&node->node.instr);

	parse_instr_line_mnemonic(&tok, instruction_node);
	parse_instr_line_ops(&tok, instruction_node, f_buf);

	return true;
}
