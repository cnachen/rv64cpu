#include "cpu.h"
#include "kits.h"
#include "inst.h"
#include "name.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static int ecall(struct hart *hart, instpiece_t piece)
{
	switch (hart->gprs[a7]) {
	case 64: // SYS_write
		*wgpr(hart, a0) = write(hart->gprs[a0], (char *)(hart->mem + hart->gprs[a1]), hart->gprs[a2]);
		break;
	case 1024: // SYS_open
		*wgpr(hart, a0) = open((char *)(hart->mem + hart->gprs[a0]), hart->gprs[a1], hart->gprs[a2]);
		break;
	}

	return 0;
}
EXPORT(ecall, INSTTYPE_I, 0x73)
