.equ STACK, 0x3000000
.equ SYS_open, 1024
.equ SYS_write, 64
.equ SYS_read, 63

.global _entry
.section .text
_entry:
	la sp, STACK

	li a7, SYS_open
	la a0, file
	li a1, 0
	ecall

	addi sp, sp, -16
	sd a0, 8(sp)

	li a7, SYS_read
	ld a0, 8(sp)
	la a1, nothing
	li a2, 64
	ecall

	li a7, SYS_write
	li a0, 1
	la a1, nothing
	li a2, 64
	ecall

	addi sp, sp, 16
	call start

1:
	j 1b

nothing:
	.skip 64

.section .rodata
file:
	.asciz "/etc/hosts"
message:
	.asciz "Hello, World!\n"
