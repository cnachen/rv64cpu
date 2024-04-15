CC = clang
MAKE = make
NAME = rv64cpu

all:
	$(MAKE) -C payload
	$(MAKE) -C core
	$(MAKE) -C isa

clean:
	$(MAKE) -C payload clean
	$(MAKE) -C core clean
	$(MAKE) -C isa clean
