#include "kits.h"
#include "types.h"
#include "cpu.h"
#include "inst.h"
#include <stdlib.h>
#include <string.h>

extern struct cpu *cpu;

static int addiw(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = sext(
		(hart->gprs[rs1] + sext(imm12, 12)) & mask(32), 32);

	return 0;
}
EXPORT(addiw, INSTTYPE_I, 0x1b)

void register_extension(struct cpu *cpu)
{
	/*
	USE(hlv.wu);
	USE(hlv.d);
	USE(hsv.d);
	*/
}
