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

	reg_t sstatus;
	reg_t sie;
	reg_t stvec;
	reg_t sepc;
	reg_t scause;
	reg_t stval;
	reg_t sip;

	reg_t mstatus;
	reg_t misa;
	reg_t mie;
	reg_t mtvec;
	reg_t mepc;
	reg_t mcause;
	reg_t mip;

	reg_t mcycle;
	reg_t minstret;

	uint8_t *mem;
	struct cpu *cpu;

#ifdef RV64F
	reg_t fprs[32];
#endif
};

struct cpu {
	struct hart harts[NCPU];
	uint8_t *mem;
	struct instproc *instvec;
};

void run_cpu(struct cpu *, uint8_t *, addr_t);

#endif
