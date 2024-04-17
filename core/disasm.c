#include "types.h"
#include "disasm.h"
#include "name.h"
#include "kits.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 128

static char *rn(int x)
{
	if (x < 32)
		return regname[x];
	return "unknown";
}

char *disasm(const char *mnemonic, insttype_t type, instpiece_t piece)
{
	static char buf[BUFSIZE];
	switch (type) {
	case INSTTYPE_R:
		if (piece.x.opcode == 0x13)
			snprintf(buf, BUFSIZE, "[R] %s %s, %s, 0x%x",
				mnemonic, rn(piece.r.rd), rn(piece.r.rs1), piece.r.rs2);
		else
			snprintf(buf, BUFSIZE, "[R] %s %s, %s, %s",
				mnemonic, rn(piece.r.rd), rn(piece.r.rs1), rn(piece.r.rs2));
		break;
	case INSTTYPE_I:
		snprintf(buf, BUFSIZE, "[I] %s %s, %s, 0x%x",
			mnemonic, rn(piece.i.rd), rn(piece.i.rs1), piece.i.imm12);
		break;
	case INSTTYPE_S:
		snprintf(buf, BUFSIZE, "[S] %s %s, %s, 0x%llx",
			mnemonic, rn(piece.s.rs1), rn(piece.s.rs2), from_imm12hilo(piece.s.imm12hi, piece.s.imm12lo));
		break;
	case INSTTYPE_B:
		snprintf(buf, BUFSIZE, "[B] %s %s, %s, 0x%llx",
			mnemonic, rn(piece.b.rs1), rn(piece.r.rs2), from_bimm12hilo(piece.b.bimm12hi, piece.b.bimm12lo));
		break;
	case INSTTYPE_U:
		snprintf(buf, BUFSIZE, "[U] %s %s, 0x%x",
			mnemonic, rn(piece.u.rd), piece.u.imm20);
		break;
	case INSTTYPE_J:
		snprintf(buf, BUFSIZE, "[J] %s %s, 0x%llx",
			mnemonic, rn(piece.j.rd), from_jimm20(piece.j.jimm20));
		break;
	default:
		buf[0] = 0;
	}
	return buf;
}
