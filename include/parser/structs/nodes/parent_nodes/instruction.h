#pragma once

#include <stddef.h>

#include "../child_nodes/reg.h"
#include "../child_nodes/identifier.h"
#include "../../../enums/instruction/mnemonic_t.h"
#include "../../../enums/instruction/op_t.h"

#define INSTRUCTION_MAX_ARG_C 4

struct instruction {
	union operand {
		struct identifier id;
		struct reg reg;
	};

	enum mnemonic_t mnemonic;
	size_t operand_c;
	
	enum op_t operands_t[INSTRUCTION_MAX_ARG_C];
	union operand operands[INSTRUCTION_MAX_ARG_C];
};
