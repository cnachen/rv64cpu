#ifndef _INST_H
#define _INST_H 1

#include "cpu.h"

void register_inst(struct cpu *cpu, struct instproc *proc);

instpiece_t fetch_inst(struct hart *, uint8_t *);

void execute_inst(struct hart *, instpiece_t);

struct instproc *find_instproc(struct cpu *cpu, instpiece_t piece);

#endif
