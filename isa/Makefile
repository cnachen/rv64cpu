INCLUDE = -I. -I../include -I../isa
CFLAGS = -shared -Wunused -fpic

all:
	cc rvi.c kits.c ../core/disasm.c ../core/inst.c $(CFLAGS) $(INCLUDE) -o ../rvi.so
	cc rv64i.c kits.c ../core/disasm.c ../core/inst.c $(CFLAGS) $(INCLUDE) -o ../rv64i.so

clean:
	rm -f ../rvi.so ../rv64i.so
