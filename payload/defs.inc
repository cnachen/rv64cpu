.equ SYS_open, 1024
.equ SYS_exit, 93
.equ SYS_write, 64
.equ SYS_read, 63
.equ SYS_close, 57

.equ O_RDONLY, 0
.equ O_WRONLY, 1
.equ O_RDWR, 2
.equ O_APPEND, 8
.equ O_CREAT, 0x200
.equ O_TRUNC, 0x400
.equ O_EXCL, 0x800
.equ O_SYNC, 0x2000
.equ O_NONBLOCK, 0x4000
.equ O_NOCTTY, 0x8000
