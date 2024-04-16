#include "cpu.h"
#include "inst.h"
#include "dl.h"
#include "colors.h"

#include <stdlib.h>
#include <string.h>

static void print_regs(struct hart *hart)
{
	printf(GREEN);
	printf("pc:\t%016llx ", hart->pc);
	printf("ra:\t%016llx ", hart->gprs[1]);
	printf("sp:\t%016llx\n", hart->gprs[2]);
	printf(RESET);
	printf("gp:\t%016llx ", hart->gprs[3]);
	printf("tp:\t%016llx ", hart->gprs[4]);
	printf("fp:\t%016llx\n", hart->gprs[8]);
	printf(GREEN);
	printf("t0:\t%016llx ", hart->gprs[5]);
	printf("t1:\t%016llx ", hart->gprs[6]);
	printf("t2:\t%016llx\n", hart->gprs[7]);
	printf(RESET);
	printf("a0:\t%016llx ", hart->gprs[10]);
	printf("a1:\t%016llx ", hart->gprs[11]);
	printf("a2:\t%016llx\n", hart->gprs[12]);
}

static void single_step(struct hart * hart)
{
	int i;
	char cmd[32];
	fgets(cmd, 31, stdin);

	for (i = 0; cmd[i] != '\n'; i++) {}
	cmd[i] = 0;

	if (!strcmp(cmd, "q"))
		exit(0);
	if (!strcmp(cmd, "n"))
		return;
	if (!strcmp(cmd, "c")) {
		hart->mdbg = 0;
		return;
	}
}

void run_cpu(struct cpu *cpu, uint8_t *mem, addr_t entry)
{
	instpiece_t piece;

	struct hart *hart0 = &cpu->harts[0];

	hart0->pc = entry;
	hart0->mem = cpu->mem;
	hart0->cpu = cpu;
	hart0->pcimm = 4;
	hart0->mdbg = -1;

	install_extension(cpu);

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
