#ifndef _TYPES_H
#define _TYPES_H 1

#include <stdint.h>
#include "conf.h"

typedef int64_t ireg64_t;
typedef uint64_t reg64_t;
typedef uint32_t inst_t;
typedef uint16_t cinst_t;

#ifdef RV64
	typedef uint64_t addr_t;
	typedef uint64_t reg_t;
	typedef int64_t ireg_t;

#else
	typedef uint32_t addr_t;
	typedef uint32_t reg_t;

#endif

typedef void (*instop_t)();

typedef enum {
	INSTTYPE_R,
	INSTTYPE_I,
	INSTTYPE_S,
	INSTTYPE_B,
	INSTTYPE_U,
	INSTTYPE_J,
} insttype_t;

typedef union {
	struct {
		inst_t opcode: 7;
		inst_t rd: 5;
		inst_t funct3: 3;
		inst_t rs1: 5;
		inst_t rs2: 5;
		inst_t funct7: 7;
	} r;
	struct {
		inst_t opcode: 7;
		inst_t rd: 5;
		inst_t funct3: 3;
		inst_t rs1: 5;
		inst_t imm12: 12;
	} i;
	struct {
		inst_t opcode: 7;
		inst_t imm12lo: 5;
		inst_t funct3: 3;
		inst_t rs1: 5;
		inst_t rs2: 5;
		inst_t imm12hi: 7;
	} s;
	struct {
		inst_t opcode: 7;
		inst_t bimm12lo: 5;
		inst_t funct3: 3;
		inst_t rs1: 5;
		inst_t rs2: 5;
		inst_t bimm12hi: 7;
	} b;
	struct {
		inst_t opcode: 7;
		inst_t rd: 5;
		inst_t imm20: 20;
	} u;
	struct {
		inst_t opcode: 7;
		inst_t rd: 5;
		inst_t jimm20: 20;
	} j;
	struct {
		inst_t opcode: 7;
		inst_t other: 25;
	} x;
	inst_t conv;
} instpiece_t;

struct instproc {
	char mnemonic[16];
	insttype_t type;
	instpiece_t piece;
	instop_t op;
	struct instproc *next;
	struct instproc *sibling;
};

#endif
