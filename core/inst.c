#include "inst.h"
#include "types.h"

#include <stdlib.h>

void register_instproc(struct cpu *cpu, struct instproc *proc)
{
	struct instproc *s = find_instproc(cpu, proc->piece);
	if (!s) {
		struct instproc *b = malloc(sizeof(struct instproc)), *p;
		b->next = cpu->instvec;

		for (p = b; p != NULL && p->next != NULL; p = p->next) {}

		p->next = proc;
		cpu->instvec = b->next;
		free(b);
	} else {
		proc->sibling = s->sibling;
		s->sibling = proc;
	}
}

instpiece_t fetch_inst(struct hart *hart, uint8_t *mem)
{
	inst_t ret = *(inst_t *)(mem + hart->pc);
	printf("inst:\t%08x\n", ret);

	struct instproc *s = find_instproc(hart->cpu, (instpiece_t)ret);
	printf("op:\t%s\n", s->mnemonic);

	return (instpiece_t)ret;
}

void execute_inst(struct hart *hart, instpiece_t piece)
{
	struct instproc *s = find_instproc(hart->cpu, piece);

	if (s) {
		((int (*)(struct hart*, instpiece_t))(s->op))(hart, piece);
	}
}

struct instproc *find_instproc(struct cpu *cpu, instpiece_t piece)
{
	struct instproc *s, *p;
	s = NULL;

	for (p = cpu->instvec; p; p = p->next) {
		if (p->piece.x.opcode == piece.x.opcode) {
			s = p;
			break;
		}
	}

	for (p = s; p; p = p->sibling) {
		if (
			p->type == INSTTYPE_R && p->piece.r.funct3 == piece.r.funct3 && p->piece.r.funct7 == piece.r.funct7 ||
			p->type == INSTTYPE_I && p->piece.i.funct3 == piece.i.funct3 ||
			p->type == INSTTYPE_S && p->piece.s.funct3 == piece.s.funct3 ||
			p->type == INSTTYPE_B && p->piece.b.funct3 == piece.b.funct3
		) {
			s = p;
			break;
		}
	}

	return s;
}
