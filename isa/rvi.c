#include "kits.h"
#include "types.h"
#include "cpu.h"
#include "inst.h"
#include <stdlib.h>
#include <string.h>

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

	reg_t t = hart->pc + 4;
	hart->pc = (hart->gprs[rs1] + sext(imm12, 12)) & ~mask(1);
	hart->pcimm = 0;
	*wgpr(hart, rd) = t;

	return 0;
}
EXPORT(jalr, INSTTYPE_I, 0x67)

static int beq(struct hart *hart, instpiece_t piece)
{
	PLACE4(b, rs1, rs2, bimm12hi, bimm12lo);

	if (hart->gprs[rs1] == hart->gprs[rs2]) {
		hart->pc += sext(from_bimm12hilo(bimm12hi, bimm12lo), 12);
		hart->pcimm = 0;
	}

	return 0;
}
EXPORT(beq, INSTTYPE_B, 0x63)

static int bne(struct hart *hart, instpiece_t piece)
{
	PLACE4(b, rs1, rs2, bimm12hi, bimm12lo);

	if (hart->gprs[rs1] != hart->gprs[rs2]) {
		hart->pc += sext(from_bimm12hilo(bimm12hi, bimm12lo), 12);
		hart->pcimm = 0;
	}

	return 0;
}
EXPORT(bne, INSTTYPE_B, 0x1063)

static int blt(struct hart *hart, instpiece_t piece)
{
	PLACE4(b, rs1, rs2, bimm12hi, bimm12lo);

	if ((ireg_t)hart->gprs[rs1] < (ireg_t)hart->gprs[rs2]) {
		hart->pc += sext(from_bimm12hilo(bimm12hi, bimm12lo), 12);
		hart->pcimm = 0;
	}

	return 0;
}
EXPORT(blt, INSTTYPE_B, 0x4063)

static int bge(struct hart *hart, instpiece_t piece)
{
	PLACE4(b, rs1, rs2, bimm12hi, bimm12lo);

	if ((ireg_t)hart->gprs[rs1] >= (ireg_t)hart->gprs[rs2]) {
		hart->pc += sext(from_bimm12hilo(bimm12hi, bimm12lo), 12);
		hart->pcimm = 0;
	}

	return 0;
}
EXPORT(bge, INSTTYPE_B, 0x5063)

static int bltu(struct hart *hart, instpiece_t piece)
{
	PLACE4(b, rs1, rs2, bimm12hi, bimm12lo);

	if (hart->gprs[rs1] < hart->gprs[rs2]) {
		hart->pc += sext(from_bimm12hilo(bimm12hi, bimm12lo), 12);
		hart->pcimm = 0;
	}

	return 0;
}
EXPORT(bltu, INSTTYPE_B, 0x6063)

static int bgeu(struct hart *hart, instpiece_t piece)
{
	PLACE4(b, rs1, rs2, bimm12hi, bimm12lo);

	if (hart->gprs[rs1] >= hart->gprs[rs2]) {
		hart->pc += sext(from_bimm12hilo(bimm12hi, bimm12lo), 12);
		hart->pcimm = 0;
	}

	return 0;
}
EXPORT(bgeu, INSTTYPE_B, 0x7063)

static int lb(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = sext(*(uint8_t *)(hart->mem + hart->gprs[rs1] + sext(imm12, 12)), 8);

	return 0;
}
EXPORT(lb, INSTTYPE_I, 0x3)

static int lh(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = sext(*(uint16_t *)(hart->mem + hart->gprs[rs1] + sext(imm12, 12)), 16);

	return 0;
}
EXPORT(lh, INSTTYPE_I, 0x1003)


static int lw(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = sext(*(uint32_t *)(hart->mem + hart->gprs[rs1] + sext(imm12, 12)), 32);

	return 0;
}
EXPORT(lw, INSTTYPE_I, 0x2003)

static int lbu(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = *(uint8_t *)(hart->mem + hart->gprs[rs1] + sext(imm12, 12));

	return 0;
}
EXPORT(lbu, INSTTYPE_I, 0x4003)

static int lhu(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = *(uint16_t *)(hart->mem + hart->gprs[rs1] + sext(imm12, 12));

	return 0;
}
EXPORT(lhu, INSTTYPE_I, 0x5003)

static int sb(struct hart *hart, instpiece_t piece)
{
	PLACE4(s, rs1, rs2, imm12hi, imm12lo);

	*(uint8_t *)(hart->mem + hart->gprs[rs1] + sext(from_imm12hilo(imm12hi, imm12lo), 12)) = hart->gprs[rs2] & mask(8);

	return 0;
}
EXPORT(sb, INSTTYPE_S, 0x23)

static int sh(struct hart *hart, instpiece_t piece)
{
	PLACE4(s, rs1, rs2, imm12hi, imm12lo);

	*(uint16_t *)(hart->mem + hart->gprs[rs1] + sext(from_imm12hilo(imm12hi, imm12lo), 12)) = hart->gprs[rs2] & mask(16);

	return 0;
}
EXPORT(sh, INSTTYPE_S, 0x1023)

static int sw(struct hart *hart, instpiece_t piece)
{
	PLACE4(s, rs1, rs2, imm12hi, imm12lo);

	*(uint32_t *)(hart->mem + hart->gprs[rs1] + sext(from_imm12hilo(imm12hi, imm12lo), 12)) = hart->gprs[rs2] & mask(32);

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


static int slti(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = (ireg_t)hart->gprs[rs1] < (ireg_t)sext(imm12, 12);

	return 0;
}
EXPORT(slti, INSTTYPE_I, 0x2013)

static int sltiu(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = hart->gprs[rs1] < sext(imm12, 12);

	return 0;
}
EXPORT(sltiu, INSTTYPE_I, 0x3013)

static int xori(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = hart->gprs[rs1] ^ sext(imm12, 12);

	return 0;
}
EXPORT(xori, INSTTYPE_I, 0x4013)

static int ori(struct hart *hart, instpiece_t piece)
{
	PLACE3(i, rd, rs1, imm12);

	*wgpr(hart, rd) = hart->gprs[rs1] | sext(imm12, 12);

	return 0;
}
EXPORT(ori, INSTTYPE_I, 0x6013)

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

static int srai(struct hart *hart, instpiece_t piece)
{
	PLACE3(r, rd, rs1, rs2);

	*wgpr(hart, rd) = sext(hart->gprs[rs1] >> rs2, 64 - rs2);

	return 0;
}
EXPORT(srai, INSTTYPE_R, 0x40005013)

static int add(struct hart *hart, instpiece_t piece)
{
	PLACE3(r, rd, rs1, rs2);

	*wgpr(hart, rd) = hart->gprs[rs1] + hart->gprs[rs2];

	return 0;
}
EXPORT(add, INSTTYPE_R, 0x33)

static int sub(struct hart *hart, instpiece_t piece)
{
	PLACE3(r, rd, rs1, rs2);

	*wgpr(hart, rd) = hart->gprs[rs1] - hart->gprs[rs2];

	return 0;
}
EXPORT(sub, INSTTYPE_R, 0x40000033)

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

void register_extension(struct cpu *cpu)
{
	USE(lui);
	USE(auipc);
	USE(jal);
	USE(jalr);
	USE(beq);
	USE(bne);
	USE(blt);
	USE(bge);
	USE(bltu);
	USE(bgeu);
	USE(lb);
	USE(lh);
	USE(lw);
	USE(lbu);
	USE(lhu);
	USE(sb);
	USE(sh);
	USE(sw);
	USE(addi);
	USE(slti);
	USE(sltiu);
	USE(xori);
	USE(ori);
	USE(andi);
	USE(slli);
	USE(srli);
	USE(srai);
	USE(add);
	USE(sub);
	/*
	USE(sll);
	USE(slt);
	USE(sltu);
	USE(xor);
	USE(srl);
	USE(sra);
	*/
	USE(or);
	USE(and);
	/*
	USE(fence);
	USE(fence_i);
	USE(ecall);
	USE(ebreak);
	USE(csrrw);
	USE(csrrs);
	USE(csrrc);
	USE(csrrwi);
	USE(csrrsi);
	USE(csrrci);
	*/
}
