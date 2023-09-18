#include "isa.h"
#include "types.h"
#include "kits.h"
#include "cpu.h"
#include <stdlib.h>
#include <string.h>

extern struct cpu *cpu;

static int lui(struct hart *hart, instpiece_t piece)
{
	PLACE2(u, rd, imm20);

	 *wgpr(hart, rd) = sext(imm20, 20) << 12;

	return 0;
}
EXPORT(lui, INSTTYPE_U, 0x37)

static int auipc(struct hart *hart, instpiece_t piece)
{
	PLACE2(u, rd, imm20);

	*wgpr(hart, rd) = hart->pc + (sext(imm20, 20) << 12);

	return 0;
}
EXPORT(auipc, INSTTYPE_U, 0x17)

static int jal(struct hart *hart, instpiece_t piece)
{
	PLACE2(j, rd, jimm20);

	*wgpr(hart, rd) = hart->pc + 4;
	hart->pcimm = sext(from_jimm20(jimm20), 20);

	return 0;
}
EXPORT(jal, INSTTYPE_J, 0x6f)

static int jalr(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = hart->pc + 4;
	hart->pc = (hart->gprs[rs1] + sext(imm12, 12)) & ~mask(1);
	hart->pcimm = 0;

	return 0;
}
EXPORT(jalr, INSTTYPE_I, 0x67)

static int lw(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = sext(*(uint32_t *)(cpu->mem + hart->gprs[rs1] + sext(imm12, 12)), 32);

	return 0;
}
EXPORT(lw, INSTTYPE_I, 0x2003)

static int sw(struct hart *hart, instpiece_t piece)
{
	PLACE4(s, rs1, rs2, imm12hi, imm12lo);

	*(uint32_t *)(cpu->mem + hart->gprs[rs1] + sext(from_imm12hilo(imm12hi, imm12lo), 12)) = hart->gprs[rs2] & mask(32);

	return 0;
}
EXPORT(sw, INSTTYPE_S, 0x2023)

static int addi(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = hart->gprs[rs1] + sext(imm12, 12);

	return 0;
}
EXPORT(addi, INSTTYPE_I, 0x13)

static int andi(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = hart->gprs[rs1] & sext(imm12, 12);

	return 0;
}
EXPORT(andi, INSTTYPE_I, 0x7013)

static int slli(struct hart *hart, instpiece_t piece)
{
	PLACE3(r, rd, rs1, rs2);

	*wgpr(hart, rd) = hart->gprs[rs1] << rs2;

	return 0;
}
EXPORT(slli, INSTTYPE_R, 0x1013)

static int srli(struct hart *hart, instpiece_t piece)
{
	PLACE3(r, rd, rs1, rs2);

	*wgpr(hart, rd) = hart->gprs[rs1] >> rs2;

	return 0;
}
EXPORT(srli, INSTTYPE_R, 0x5013)

static int or(struct hart *hart, instpiece_t piece)
{
	PLACE3(r, rd, rs1, rs2);

	*wgpr(hart, rd) = hart->gprs[rs1] | hart->gprs[rs2];

	return 0;
}
EXPORT(or, INSTTYPE_R, 0x6033)

static int and(struct hart *hart, instpiece_t piece)
{
	PLACE3(r, rd, rs1, rs2);

	*wgpr(hart, rd) = hart->gprs[rs1] & hart->gprs[rs2];

	return 0;
}
EXPORT(and, INSTTYPE_R, 0x7033)

void register_rvi()
{
	USE(lui);
	USE(auipc);
	USE(jal);
	USE(jalr);
	USE(lw);
	USE(sw);
	USE(addi);
	USE(andi);
	USE(slli);
	USE(srli);
	USE(or);
	USE(and);
}
