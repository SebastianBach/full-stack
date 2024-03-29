# Linux x86_64 AMD64
# AT&T syntax

.section .data

input: .string "Input:  "
input_len = . - input  

output: .string "Output: "
output_len = . - output  

new_line: .string "\n"
new_line_len = . - new_line 

invalid_args: .string "Insufficient command line arguments\n"
invalid_args_len = . - invalid_args

empty_arg: .string "\nEmpty argument\n"
empty_arg_len = . - empty_arg  

.section .text

.global _start

# constants

.set SYS_WRITE, 1
.set SYS_EXIT, 60
.set STDOUT, 1
.set EXIT_FAILURE, 1

_start:
 
    # check for at least 2 command line args

    movq (%rsp), %rax                   # number for commmand line args
    cmpq $2, %rax                       # check for 2
    jl exit_failure_invalid_args        # exit failure if less than two


    # print "Input: "
    call print_input

    # adress of argv[1] into rsi
    mov 16(%rsp), %rsi

    # length of argv[1], result in rax
    call string_length

    # check for non empty argument

    cmpq $1, %rax               # check for at least one character
    jl exit_failure_empty_arg   # exit failure


    # store length in preserved register
    mov %rax, %rbx

    # print input

    mov 16(%rsp), %rsi      # ptr to text
    mov %rax, %rdx          # length of text
    call print_stdout

    call print_new_line

    # format to title case

    mov 16(%rsp), %rdi          # address of the input
    mov %rbx, %rsi              # length of the input
    call text_conversion_c      # call
    
    # print result

    call print_output

    mov 16(%rsp), %rsi      # ptr to text
    mov %rbx, %rdx          # length of text
    call print_stdout

    call print_new_line

    # exit program

    xor %rdi, %rdi      # exit code 0
    jmp exit

# arguments are
# rsi: pointer to string
# return:
# rax: length of the string
string_length:
    xor %rcx, %rcx    # clear rcx, which will hold the length

.next_char:
    cmpb $0, (%rsi, %rcx)   # compare to null terminator
    je .done                # null terminator, we're done
    inc %rcx                # increment the length counter
    jmp .next_char          # the next character

.done:
    mov %rcx, %rax    # Move the length into rax
    ret               # Return


print_new_line:
    lea new_line(%rip), %rsi
    mov $new_line_len, %rdx
    jmp print_stdout

print_input:
    lea input(%rip), %rsi
    mov $input_len, %rdx
    jmp print_stdout

print_output:
    lea output(%rip), %rsi
    mov $output_len, %rdx
    jmp print_stdout

print_invalid_args:
    lea invalid_args(%rip), %rsi
    mov $invalid_args_len, %rdx
    jmp print_stdout

print_empty_arg:
    lea empty_arg(%rip), %rsi
    mov $empty_arg_len, %rdx
    jmp print_stdout

# arguments are
# rsi: ptr to text
# rdx: length of text
print_stdout:
    mov $SYS_WRITE, %rax        # syscall number for sys_write
    mov $STDOUT, %rdi           # stdout
    syscall                     # call
    ret

exit_failure_invalid_args:
    call print_invalid_args
    mov $EXIT_FAILURE, %edi 
    jmp exit

exit_failure_empty_arg:
    call print_empty_arg
    mov $EXIT_FAILURE, %edi 
    jmp exit

# arguments are
# rdi: return code
exit:
    mov $SYS_EXIT, %rax         # syscall number for exit
    syscall                     # call
