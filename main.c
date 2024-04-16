#include "cpu.h"

#include <stdlib.h>
#include <string.h>

#define M (1024 * 1024)

void mapping(uint8_t **mem, const char path[])
{
	FILE *f;
	int c;
	int i, size;

	f = fopen(path, "r");
	size = 8 * M;
	*mem = malloc(size);

	for (i = 0; (c = fgetc(f)) != EOF; i++) {
		if (i >= size - 1)
			*mem = realloc(*mem, size *= 2);
		*(*mem + i) = (c & 0xff);
	}
}

struct cpu *cpu;
static uint8_t *mem;

static void cleanup()
{
	free(mem);
	free(cpu);
}

int main()
{
	mapping(&mem, "payload/payload.bin");
	// *(inst_t *)(mem + 0) = 0x13;
	// *(inst_t *)(mem + 4) = 0x600293;
	// *(inst_t *)(mem + 8) = 0x428293;

	cpu = malloc(sizeof(struct cpu));
	memset(cpu, 0, sizeof(struct cpu));
	cpu->mem = mem;
	cpu->instvec = NULL;

	atexit(cleanup);
	run_cpu(cpu, mem, 0x0);

	return 0;
}
