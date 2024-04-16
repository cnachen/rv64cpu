INCLUDE = -I. -I../include -I../isa
CFLAGS = -shared -Wunused

all:
	cc rvi.c kits.c ../core/inst.c $(CFLAGS) $(INCLUDE) -o ../rvi.so
	cc rv64i.c kits.c ../core/inst.c $(CFLAGS) $(INCLUDE) -o ../rv64i.so

clean:
	rm -f ../rvi.so ../rv64i.so
