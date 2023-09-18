#include "cpu.h"

#include <stdlib.h>
#include <string.h>

void mapping(uint8_t **mem, const char path[])
{
	FILE *f;
	int c;
	int i, size;

	f = fopen(path, "r");
	size = 1;
	*mem = malloc(size);

	for (i = 0; (c = fgetc(f)) != EOF; i++) {
		if (i >= size - 1)
			*mem = realloc(*mem, size *= 2);
		*(*mem + i) = (c & 0xff);
	}
}

struct cpu *cpu;

int main()
{
	uint8_t *mem;
	mapping(&mem, "assets/payload.bin");
	// *(inst_t *)(mem + 0) = 0x13;
	// *(inst_t *)(mem + 4) = 0x600293;
	// *(inst_t *)(mem + 8) = 0x428293;

	cpu = malloc(sizeof(struct cpu));
	memset(cpu, 0, sizeof(struct cpu));
	cpu->mem = mem;
	cpu->instvec = NULL;

	run_cpu(cpu, mem, 0x0);

	free(mem);
	free(cpu);
	return 0;
}
