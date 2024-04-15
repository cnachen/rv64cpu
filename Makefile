CC = clang
MAKE = make
NAME = rv64cpu

all: core isa

core:
	$(MAKE) -C core

isa:
	$(MAKE) -C isa

clean:
	$(MAKE) -C core clean
	$(MAKE) -C isa clean
