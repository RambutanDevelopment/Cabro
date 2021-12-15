global _start        
    
section .text
_start:
    mov rax, 'H'
    call _printchr

    mov rdi, 0
    call _exit
_printchr:
    push rsi
    push rax
  
    mov rsi, rsp
    mov rdi, 1
    mov rdx, 1

    call _write

    pop rax
    pop rsi
    ret
; params: rsi, string to print
_print:
    push rdx
    push rsi
    push rdi

    mov rdx, rsi
    push rsi
    cmp byte [rsi], 0
    je print.exit

print.loop:
    inc rsi
    cmp byte [rsi], 0
    jne print.loop 

print.exit:
    sub rsi, rdx
    mov rdx, rsi
    pop rsi
    cmp rsi, message
    mov rdi, 1
    call _write

    pop rdi
    pop rsi
    pop rdx 
    ret
    
; params: rdi, file handle; rsi, string to write; rdx, length of string
_write:
    push rax
    mov  rax, 1              ; system call for write
    syscall                  ; invoking os to write

    pop rax
    ret
; params: rdi, exit code
_exit:
    mov rax, 60             ; sys call for exit
    syscall                 ; invoke os to exit

    ; ##########################
    ; Variables
    ; ##########################

section .data   
message: db "Hello, World", 0xa, 0x0