#ifndef _CPU_H
#define _CPU_H

#include <stdio.h>
#include "types.h"

struct hart {
	reg_t pc;
	reg_t pcimm;
	reg_t ignr;
	reg_t mdbg;
	reg_t gprs[32];
	reg_t csrs[NCSR];

#ifdef RV64F
	reg_t fprs[32];
#endif
};

struct cpu {
	struct hart harts[NCPU];
	uint8_t *mem;
	struct instproc *instvec;
};

void register_instproc(struct cpu *, struct instproc *);

void run_cpu(struct cpu *, uint8_t *, addr_t);

#endif
