#ifndef _KITS_H
#define _KITS_H 1

#include "types.h"
#include "cpu.h"

#define EXPORT(_op, _type, _piece) \
static void register_##_op(struct cpu *cpu) \
{ \
	struct instproc *proc = malloc(sizeof(struct instproc)); \
	strcpy(proc->mnemonic, #_op);	\
	proc->type = _type; \
	proc->piece = (instpiece_t)((inst_t)_piece); \
	proc->op = (instop_t)_op; \
	proc->next = NULL; \
	proc->sibling = NULL; \
	register_instproc(cpu, proc); \
}

#define PLACE(_t, _a) \
	inst_t _a = piece._t._a;

#define PLACE2(_t, _a, _b) \
	PLACE(_t, _a) \
	PLACE(_t, _b)

#define PLACE3(_t, _a, _b, _c) \
	PLACE(_t, _a) \
	PLACE2(_t, _b, _c)

#define PLACE4(_t, _a, _b, _c, _d) \
	PLACE(_t, _a) \
	PLACE3(_t, _b, _c, _d)

#define USE(op) register_##op(cpu)

reg_t *wgpr(struct hart *, inst_t);

reg_t mask(int);

reg_t sext(reg_t, int);

reg_t zext(reg_t, int);

reg_t from_jimm20(inst_t);

reg_t from_imm12hilo(inst_t imm12hi, inst_t imm12lo);

reg_t from_bimm12hilo(inst_t bimm12hi, inst_t bimm12lo);

inst_t span(inst_t, int, int);

#endif
