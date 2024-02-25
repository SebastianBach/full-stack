# Linux x86_64 AMD64
# AT&T syntax

.section .data

input: .string "Input: "
input_len = . - input  

output: .string "Output: "
output_len = . - output  

new_line: .string "\n"
new_line_len = . - new_line  

.section .text

.global _start

_start:
    # todo: exit if no second command line arg given

    # print "Input: "
    call print_input

    # Load the address of argv[1] into rsi
    mov 16(%rsp), %rsi

    # Calculate the length of argv[1], result in rax
    call string_length

    # todo: exit if length is zero

    # store length in preserved register
    mov %rax, %r12

    mov 16(%rsp), %rsi      # ptr to text
    mov %rax, %rdx      # length of text
    call print_stdout

    call print_new_line

    # Prepare the write syscall to print argv[1]
    # mov $1, %rax        # syscall number for write
    # mov $1, %rdi        # file descriptor 1 = stdout
    # mov 16(%rsp), %rsi  
    # rdx contains the length of the string
    # syscall             # perform the write syscall

    mov 16(%rsp), %rdi          # address of the input
    mov %r12, %rsi              # length of the input
    call text_conversion_c      # call


    
    call print_output

    mov 16(%rsp), %rsi      # ptr to text
    mov %r12, %rdx          # length of text
    call print_stdout

    call print_new_line

    # mov $1, %rax        # syscall number for write
    # mov $1, %rdi        # file descriptor 1 = stdout

    # syscall             # perform the write syscall

   

    # Exit the program
    # mov $60, %rax       # syscall number for exit
    xor %rdi, %rdi      # exit code 0
    #  syscall             # exit
    jmp exit

# Function to calculate the length of a string
# Input: rsi = pointer to string
# Output: rax = length of the string
string_length:
    xor %rcx, %rcx    # Clear rcx, which will hold the length
    xor %rax, %rax    # Clear rax, which will be used for the null terminator comparison

.next_char:
    cmpb $0, (%rsi, %rcx) # Compare the current byte to null terminator
    je .done          # If we've hit the null terminator, we're done
    inc %rcx          # Increment the length counter
    jmp .next_char    # Go to the next character

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

# arguments are
# rsi: ptr to text
# rdx: length of text
print_stdout:
    mov $1, %rax                # syscall number for sys_write
    mov $1, %rdi                # stdout
    syscall                     # call
    ret

# arguments are
# rdi: return code
exit:
    mov $60, %rax       # syscall number for exit
    syscall             # call

