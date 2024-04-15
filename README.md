# rv64cpu
An ISA simulator for 64-bit RISC-V.

To build core and supported isa extensions, apply
```
make -C core
make -C isa
```

To build test files, apply
```
$(PREFIX)-gcc -march=rv64i -mabi=lp64 -O0 -nostdlib -T link.ld -o $(NAME).elf $(shell find -E . -iregex  ".*\.(c|s)")
$(PREFIX)-objcopy -O binary $(NAME).elf $(NAME).bin
```
