INCLUDE = -I. -I../include -I../isa

all:
	cc cpu.c inst.c dl.c disasm.c ../main.c ../isa/kits.c $(INCLUDE) -o ../rv64

clean:
	rm -f ../rv64
