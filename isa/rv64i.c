#include "kits.h"
#include "types.h"
#include "cpu.h"
#include "inst.h"
#include <stdlib.h>
#include <string.h>

extern struct cpu *cpu;

static int lwu(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = zext(*(uint32_t *)(hart->mem + hart->gprs[rs1] + sext(imm12, 12)), 32);

	return 0;
}
EXPORT(lwu, INSTTYPE_I, 0x6003)

static int ld(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = *(uint64_t *)(hart->mem + hart->gprs[rs1] + sext(imm12, 12));

	return 0;
}
EXPORT(ld, INSTTYPE_I, 0x3003)

static int sd(struct hart *hart, instpiece_t piece)
{
	PLACE4(s, rs1, rs2, imm12hi, imm12lo);

	*(uint64_t *)(hart->mem + hart->gprs[rs1] + sext(from_imm12hilo(imm12hi, imm12lo), 12)) = hart->gprs[rs2];

	return 0;
}
EXPORT(sd, INSTTYPE_S, 0x3023)

static int slli(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = hart->gprs[rs1] << span(imm12, 5, 0);

	return 0;
}
EXPORT(slli, INSTTYPE_I, 0x1013)

static int srli(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = hart->gprs[rs1] >> span(imm12, 5, 0);

	return 0;
}
EXPORT(srli, INSTTYPE_I, 0x5013)

static int srai(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = sext(hart->gprs[rs1] >> span(imm12, 5, 0), 64 - span(imm12, 5, 0));

	return 0;
}
EXPORT(srai, INSTTYPE_I, 0x40005013)


static int addiw(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = sext(
		(hart->gprs[rs1] + sext(imm12, 12)) & mask(32), 32);

	return 0;
}
EXPORT(addiw, INSTTYPE_I, 0x1b)

static int addw(struct hart *hart, instpiece_t piece)
{
	PLACE3(r, rd, rs1, rs2);

	*wgpr(hart, rd) = sext(
		(hart->gprs[rs1] + hart->gprs[rs2]) & mask(32), 32);

	return 0;
}
EXPORT(addw, INSTTYPE_R, 0x3b)

void register_extension(struct cpu *cpu)
{
	USE(lwu);
	USE(ld);
	USE(sd);
	USE(slli);
	USE(srli);
	USE(srai);
	USE(addiw);
	/*
	USE(slliw);
	USE(srliw);
	USE(sraiw);
	*/
	USE(addw);
	/*
	USE(subw);
	USE(sllw);
	USE(srlw);
	USE(sraw);
	*/
}
