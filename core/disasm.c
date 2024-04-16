#include "types.h"
#include "disasm.h"
#include "kits.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 128

static char *rn(int x)
{
	switch (x) {
	case 0:
		return "zero";
	case 1:
		return "ra";
	case 2:
		return "sp";
	case 3:
		return "gp";
	case 4:
		return "tp";
	case 5:
		return "t0";
	case 6:
		return "t1";
	case 7:
		return "t2";
	case 8:
		return "fp";
	case 9:
		return "s1";
	case 10:
		return "a0";
	case 11:
		return "a1";
	case 12:
		return "a2";
	case 13:
		return "a3";
	case 14:
		return "a4";
	case 15:
		return "a5";
	case 16:
		return "a6";
	case 17:
		return "a7";
	case 18:
		return "s2";
	case 19:
		return "s3";
	case 20:
		return "s4";
	case 21:
		return "s5";
	case 22:
		return "s6";
	case 23:
		return "s7";
	case 24:
		return "s8";
	case 25:
		return "s9";
	case 26:
		return "s10";
	case 27:
		return "s11";
	case 28:
		return "t3";
	case 29:
		return "t4";
	case 30:
		return "t5";
	case 31:
		return "t6";
	}
	return "unknown";
}

char *disasm(insttype_t type, instpiece_t piece)
{
	static char buf[BUFSIZE];
	switch (type) {
	case INSTTYPE_R:
		snprintf(buf, BUFSIZE, "%s, %s, %s", rn(piece.r.rd), rn(piece.r.rs1), rn(piece.r.rs2));
		break;
	case INSTTYPE_I:
		snprintf(buf, BUFSIZE, "%s, %s, 0x%x", rn(piece.i.rd), rn(piece.i.rs1), piece.i.imm12);
		break;
	case INSTTYPE_S:
		snprintf(buf, BUFSIZE, "%s, %s, 0x%llx", rn(piece.s.rs1), rn(piece.s.rs2), from_imm12hilo(piece.s.imm12hi, piece.s.imm12lo));
		break;
	case INSTTYPE_B:
		snprintf(buf, BUFSIZE, "%s, %s, 0x%llx", rn(piece.b.rs1), rn(piece.r.rs2), from_bimm12hilo(piece.b.bimm12hi, piece.b.bimm12lo));
		break;
	case INSTTYPE_U:
		snprintf(buf, BUFSIZE, "%s, 0x%x", rn(piece.u.rd), piece.u.imm20);
		break;
	case INSTTYPE_J:
		snprintf(buf, BUFSIZE, "%s, 0x%llx", rn(piece.j.rd), from_jimm20(piece.j.jimm20));
		break;
	default:
		buf[0] = 0;
	}
	return buf;
}
