.equ STACK, 0x3000000

.global _entry
.section .text
_entry:
	la sp, STACK
	li t0, 0xf123456789abcdef
	call start
	mv t0, a0
	j 1f

_main:
	auipc t1, 0xab
	li t1, 0x12345678

	################
	li t1, 0xfff
	addi t0, zero, 0
	addi t1, zero, 3
	bge t1, t0, 1f
	nop
1:
	beq t0, t1, 2f
	addi t0, t0, 1
	j 1b
2:
	la t0, _entry
	lw t1, 0(t0)
	srli t0, t1, 12
	addi t0, t0, 1
	slli t0, t0, 12
	li t2, 0xfff
	and t1, t1, t2 
	or t0, t1, t0
	la t1, _entry
	sw t0, 0(t1)
	addi t0, zero, 0
	j _entry

nothing:
	.skip 64

.section .rodata
msg:
	.ascii "Hello, World!\n"
