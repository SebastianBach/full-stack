.section .data           

headline: .string "this is some headline in ASM\n" 
headline_len = . - headline   # length

.section .text

.global _start

_start:
    # write input text
    mov $1, %rax                # call number for sys_write
    mov $1, %rdi                # descriptor 1 (stdout)
    lea headline(%rip), %rsi    # pointer to input
    mov $headline_len, %rdx     # length of input
    syscall                     # call

    # call text_conversion_c
    lea headline(%rip), %rdi    # address of the input
    mov $headline_len, %rsi     # length of the input
    call text_conversion_c      # call

    # write result to stdout
    mov $1, %rax                # sys_write
    mov $1, %rdi                # stdout
    lea headline(%rip), %rsi    # pointer to the modified data
    mov $headline_len, %rdx     # length of the modified data
    syscall                     # call

    # exit
    mov $60, %rax            # sys_exit
    xor %rdi, %rdi           # exit code 0
    syscall                  # call
    
