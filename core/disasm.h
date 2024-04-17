#ifndef _DISASM_H
#define _DISASM_H

#include "types.h"

char *disasm(const char * mnemonic, insttype_t type, instpiece_t piece);

#endif
