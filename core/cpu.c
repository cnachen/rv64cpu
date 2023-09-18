#include "cpu.h"
#include "inst.h"
#include "isa.h"

#include <stdlib.h>
#include <string.h>

static void print_regs(struct hart *hart)
{
	int i;
	int d = 5;
	printf("pc:\t%016llx\n", hart->pc);
	for (i = 0; i < 2; i++) {
		printf("x%d:\t%016llx ", i + d, hart->gprs[i + d]);
		if (i % 3 == 2)
			printf("\n");
	}
	if (i % 3 != 0)
		printf("\n");
}

static void single_step(struct hart * hart)
{
	int i;
	char cmd[32];
	fgets(cmd, 31, stdin);

	for (i = 0; cmd[i] != '\n'; i++) {}
	cmd[i] = 0;

	if (!strcmp(cmd, "n"))
		return;
	if (!strcmp(cmd, "q"))
		exit(0);
	if (!strcmp(cmd, "c")) {
		hart->mdbg = 0;
		return;
	}
}

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

void run_cpu(struct cpu *cpu, uint8_t *mem, addr_t entry)
{
	instpiece_t piece;

	struct hart *hart0 = &cpu->harts[0];

	hart0->pc = entry;
	hart0->pcimm = 4;
	hart0->mdbg = -1;

	register_rvi();
	register_rv64i();

	while (1) {
		piece = fetch_inst(hart0, mem);
		print_regs(hart0);
		if (hart0->mdbg)
			single_step(hart0);
		execute_inst(hart0, piece);
		hart0->pc += hart0->pcimm;
		hart0->pcimm = 4;
	}
}
