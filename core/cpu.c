#include "cpu.h"
#include "inst.h"
#include "dl.h"

#include <stdlib.h>
#include <string.h>

static void print_regs(struct hart *hart)
{
	int i;
	int d = 5;
	printf("pc:\t%016llx ", hart->pc);
	printf("ra:\t%016llx ", hart->gprs[1]);
	printf("sp:\t%016llx ", hart->gprs[2]);
	printf("fp:\t%016llx\n", hart->gprs[8]);
	for (i = 0; i < 3; i++) {
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
