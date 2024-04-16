#include "kits.h"

reg_t *wgpr(struct hart *hart, inst_t rd)
{
	if (rd == 0)
		return &hart->ignr;
	return &hart->gprs[rd];
}

reg_t mask(int n)
{
	return ((reg_t)1 << n) - 1;
}

reg_t sext(reg_t reg, int n)
{
	reg_t m = ~(mask(n));
	reg_t sign = (reg >> (n - 1)) & 1;
	return (sign ? reg | m : reg);
}

reg_t zext(reg_t reg, int n)
{
	reg_t m = mask(n);
	return reg & m;
}

reg_t from_jimm20(inst_t jimm20)
{
	reg_t r = (reg_t)span(jimm20, 19, 19);
	r <<= 8;
	r |= span(jimm20, 7, 0);
	r <<= 1;
	r |= span(jimm20, 8, 8);
	r <<= 10;
	r |= span(jimm20, 18, 9);
	r <<= 1;
	return r;
}

reg_t from_imm12hilo(inst_t imm12hi, inst_t imm12lo)
{
	reg_t r = imm12hi;
	r <<= 5;
	r |= imm12lo;
	return r;
}

reg_t from_bimm12hilo(inst_t bimm12hi, inst_t bimm12lo)
{
	reg_t r = (reg_t)span(bimm12hi, 6, 6);
	r <<= 1;
	r |= span(bimm12lo, 0, 0);
	r <<= 6;
	r |= span(bimm12hi, 5, 0);
	r <<= 4;
	r |= span(bimm12lo, 4, 1);
	r <<= 1;
	return r;
}

inst_t span(inst_t inst, int end, int begin)
{
	int m = mask(end - begin + 1);
	return (inst >> begin) & m;
}
