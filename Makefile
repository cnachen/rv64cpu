CC = clang
MAKE = make
NAME = rv64cpu

all:
	$(MAKE) -C core
	$(MAKE) -C isa

clean:
	$(MAKE) -C core clean
	$(MAKE) -C isa clean
