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
	USE(sret);
	USE(mret);
	USE(wfi);

	USE(sfence_vma);
	USE(sinval_vma);
	USE(sfence_w_inval);
	USE(sfence_inval_ir);

	USE(hfence_vvma);
	USE(hfence_gvma);
	USE(hinval_vvma);
	USE(hinval_gvma);

	USE(hlv_b);
	USE(hlv_bu);
	USE(hlv_h);
	USE(hlv_hu);
	USE(hlvx_hu);
	USE(hlv_w);
	USE(hlvx_wu);
	USE(hsv_b);
	USE(hsv_h);
	USE(hv_w);
	*/
}
