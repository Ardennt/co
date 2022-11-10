# 9. Write a MIPS program that asks the user for a positive integer n, then 
# builds a right triangle as shown in the example below. Implement this 
# using nested for loops.

# What is n? 4
# *******
# *****
# ***
# *

# Implement a MIPS function that prints out the above given an input argument for n in the a0 register. You can assume there exists in the .data segment
.data
    star:    .asciiz "*"
    newline: .asciiz "\n"

main:
    li $a0, 4 # assume that this is our n
    li $s0, 1

    move $t0, $a0 # int i = 4
    sll $t0, $t0, 1
    addi $t0, $t0, -1 # int i = 2 * i - 1

#     for1:
#         move $t1, $zero # int j = 0
#         for2:
#             la $a0, star
#             li $v0, 4
#             syscall

#             addi $t1, $t1, 1
#             blt $t1, $t0, for2

#         addi $t0, $t0, -2 # subtract 2 from the stars each print
#         bge $t0, $s0, for1
    
    li $v0, 10                                                                                                                                                               
    syscall

