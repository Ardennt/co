################################################################################
# Homework 3: Matrix-matrix multiplication
# CSCI-2500 Fall 2021
################################################################################
## Data segment
################################################################################
.data
  newline:  .asciiz "\n"
  tab:      .asciiz "\t"

################################################################################
## Text segment
################################################################################
.text
# .align 2          # instructions must be on word boundaries
  .globl main       # main is a global label
  .globl mm_read    # read in NxM matrix
  .globl mm_alloc   # allocate space for NxM matrix
  .globl mm_print   # print out formatted NxM matrix
  .globl mm_mult    # multiple two non-square matrices

################################################################################
# Main segment
################################################################################
main:
  # save return address on the stack
  sub $sp, $sp, 4   
  sw  $ra, 0($sp)

  # Read in a matrix 1 of some NxM size
  # Return in $v0 - N
  # Return in $v1 - M
  # Return in 0($sp) - base address of matrix
  sub $sp, $sp, 4   # make space on stack for return value
  jal mm_read

  # save matrix 1 values
  move  $s0, $v0
  move  $s1, $v1
  lw    $s2, 0($sp)
  add   $sp, $sp, 4   # restore stack

  # Setup arguments and print out matrix 1
  move  $a0, $s0
  move  $a1, $s1
  move  $a2, $s2
  jal mm_print

  # Read in matrix 2 of some NxM size
  sub $sp, $sp, 4   # make space on stack for return value
  jal mm_read

  # save matrix 2 values
  move  $s3, $v0
  move  $s4, $v1
  lw    $s5, 0($sp)
  add   $sp, $sp, 4   # restore stack

  # Setup arguments and print out matrix 2
  move  $a0, $s3
  move  $a1, $s4
  move  $a2, $s5
  jal mm_print

  # Setup arguments and call mm_mult
  # Note: 5 arguments, so we need to use stack
  # Note: num cols matrix 1 == num rows matrix 2
  move  $a0, $s0    # num rows matrix1
  move  $a1, $s1    # num cols matrix1
  move  $a2, $s2    # address of matrix 1
  move  $a3, $s4    # num cols matrix2
  sub   $sp, $sp, 4   
  sw    $s5, 0($sp) # address of matrix 2
  jal mm_mult
  add   $sp, $sp, 4

  # print the result
  move $a0, $s0 
  move $a1, $s4
  move $a2, $v0
  jal mm_print

  # restore $ra, free stack space, and return
  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr  $ra

################################################################################
# mm_read: Read in a NxM matrix from standard input
# Note: You will be calling mm_alloc from this function, so you'll need to save 
#       $ra on the stack. Also, you'll be returning 3 values back to main, one
#       value (the matrix base address), will need to be saved on the stack.
#       Matrix format is:
#         First line:  N = num rows
#         Second line: M = num cols
#         Subsequent lines contain one value each, filling each row in turn
#         (same format as hw01, except N,M on separate lines)  
# Input:
#   None
# Return:
#   v0 = N
#   v1 = M
#   0($sp) = base address of matrix
################################################################################
mm_read:
  # save return address and any saved registers on the stack, if necessary
  # get N
  move $t0, $zero
  li $v0, 5
  syscall
  move $t0, $v0
  
  # get M
  move $t1, $zero
  li $v0, 5
  syscall
  move $t1, $v0
  
  # store N and M
  move $s0, $t0
  move $s1, $t1
  
  # Setup up arguments and call mm_alloc - v0 is returned as base address
  move $a0, $s0
  move $a1, $s1

  # addi $a0, $zero, 2
  # addi $v0, $zero, 1
  # syscall
  jr $ra
  jal mm_alloc


  # addi $a0, $zero, 9
  # move $sp, $v0
  # addi $v0, $zero, 1
  # syscall
  
  # do nested loops to read in values
  # move $t1, $zero # int i = 0
  # For1:
  # 	move $t2, $zero # int j = 0
  # 	For2:
  # 		# li $a0, 3
  # 		# addi $v0, $zero, 1
  # 		# syscall
  # 		addi $t2, $t2, 1 # int j += 1
  # 		blt $t2, $s1, For2

  # 	move $a0, $t1
  #   addi $v0, $zero, 1
  #   syscall

  # 	addi $t1, $t1, 1 # int i += 1
  # 	blt $t1, $s0, For1
  
  
  # setup up return values
  # Note: third return value goes on the stack *after* restoration below
  # restore stack, ra, and any saved registers, if necessary
  # return to main

  # just store the value of before calling mm_alloc to jr to
  jr 
  jr  $ra

################################################################################
# mm_alloc: Allocate an NxM matrix
# Note: You can just allocate a single array of length N*M.
# Input:
#   a0 = N
#   a1 = M
# Return:
#   v0 = base address of allocated space
################################################################################
mm_alloc:
  # save return address and any saved registers on the stack, if necessary
  addi  $sp, $sp, -4
  sw    $fp, 0($sp) #store $sp into $fp 
  # Allocate sufficient space
  mul   $t0 $a0 $a1 # t0 = N * M
  sll   $t0, $t0, 2 # t0 = t0 * 2^2 < size in bytes

  sw    $fp 0($sp) # old frame pointer
  move  $fp $sp 
  sub   $sp $sp $t0 # size
  sw $ra -4($fp)  

  # set return value
  # restore stack, ra, and any saved registers, if necessary
  # return to main
  move $a0, $ra
  li $v0, 1
  syscall
  # mul $t0, $a0, $a1
  # addi $t1, $zero, 4
  # mul $t0, $t0, $t1 # size of bits to allocate
  
  # move $a0, $t0
  # li $v0, 9
  # syscall
  
  jr  $ra

################################################################################
# mm_print: Output the formatted contents of NxM matrix
# Note: Within a row, separate each value by tab
#       End each row with a newline
# Input:
#   a0 = N
#   a1 = M
#   a2 = base pointer
# Return:
#   None
################################################################################
mm_print:
  # save return address and any saved registers on the stack, if necessary

  # do nested loops to print out values

  # restore stack, ra, and any saved registers, if necessary

  # return to main
  jr  $ra

################################################################################
# mm_mult: Perform the actual NxM matrix multiplication
# Input:
#   a0 = N for matrix 1
#   a1 = M for matrix 1 <-> N for matrix 2
#   a2 = base address for matrix 1
#   a3 = M for matrix 2
#   0($sp) = base address for matrix 2
# Return:
#   v0 = base address for result matrix
################################################################################
mm_mult:
  # save return address and any saved registers on the stack, if necessary

  # set up and call mm_alloc for result matrix
 
  # three nested loops for matrix-matrix multiplication

  # set return value

  # restore stack, ra, and any saved registers, if necessary

  # return to main
  jr  $ra
