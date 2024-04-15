#include "cpu.h"

#include <dlfcn.h>

typedef void (*subprog)(struct cpu *);

int install_extension(struct cpu *cpu)
{
	void *handle;

	handle = dlopen("rvi.so", RTLD_GLOBAL | RTLD_LAZY);
	((subprog)dlsym(handle, "register_extension"))(cpu);

	handle = dlopen("rv64i.so", RTLD_GLOBAL | RTLD_LAZY);
	((subprog)dlsym(handle, "register_extension"))(cpu);
	return 0;
}

int remove_extension() {
	return 0;
}
