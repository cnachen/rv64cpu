PREFIX = riscv64-unknown-elf
NAME = payload

all:
	$(PREFIX)-gcc -march=rv64i -mabi=lp64 -O0 -nostdlib -T link.ld -o $(NAME).elf $(shell find -E . -iregex  ".*\.(c|s)")
	$(PREFIX)-objcopy -O binary $(NAME).elf $(NAME).bin

clean:
	rm -f $(NAME).elf $(NAME).bin

dump: all
	$(PREFIX)-objdump -m riscv:rv64 -b binary -D $(NAME).bin

dumpA: all
	$(PREFIX)-objdump -m riscv:rv64 -b binary -Mno-aliases -D $(NAME).bin

hex: all
	xxd -c 16 -g 4 $(NAME).bin
