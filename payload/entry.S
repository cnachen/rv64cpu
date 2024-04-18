.equ STACK, 0x3000000
.equ SYS_open, 1024
.equ SYS_write, 64

.global _entry
.section .text
_entry:
	la sp, STACK
	li t0, 0
	li t1, 6

	li a7, SYS_open
	la a0, stdout
	li a1, 0x2
	ecall

	addi sp, sp, -16
	sd a0, 8(sp)

1:
	li a7, SYS_write
	ld a0, 8(sp)
	la a1, msg
	li a2, 14
	ecall

	addi t0, t0, 1
	bne t0, t1, 1b

	addi sp, sp, 16
	call start

1:
	j 1b

nothing:
	.skip 64

.section .rodata
stdout:
	.asciz "/dev/stdout"
msg:
	.asciz "Hello, World!\n"
