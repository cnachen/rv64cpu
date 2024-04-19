#include "cpu.h"
#include "kits.h"
#include "inst.h"
#include "name.h"
#include "syscall.h"
#include "ecall.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static int ecall(struct hart *hart, instpiece_t piece)
{
	switch (hart->gprs[a7]) {
	case SYS_read:
		*wgpr(hart, a0) = read(hart->gprs[a0], M(a1), hart->gprs[a2]);
		break;
	case SYS_write:
		*wgpr(hart, a0) = write(hart->gprs[a0], M(a1), hart->gprs[a2]);
		break;
	case SYS_open:
		*wgpr(hart, a0) = open(M(a0), hart->gprs[a1], hart->gprs[a2]);
		break;
	}

	return 0;
}
EXPORT(ecall, INSTTYPE_I, 0x73)
