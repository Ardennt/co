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
  move $s3 $ra
  # get N
  li $v0, 5
  syscall
  move $t3, $v0
  
  # get M
  li $v0, 5
  syscall
  move $t4, $v0
  
  # Setup up arguments and call mm_alloc - v0 is returned as base address
  move $a0, $t3
  move $a1, $t4
  jal mm_alloc # return address will change here
  move $ra, $s3
  
  # do nested loops to read in values
  sw $v0, 0($sp) # save "memory address" in t0
  lw $t0, 0($sp) # t0 will point at the address of $sp

  move $t1, $zero # int i = 0
  For1:
  	move $t2, $zero # int j = 0
  	For2:
      li $v0, 5
      syscall # read in integer
  		sw $v0, 0($t0) # save the integer into the address

      # li $v0, 1
      # move $a0, $t0
      # syscall # print out address
    
  		addi $t2, $t2, 1 # int j += 1
      addi $t0, $t0, 4 # increment memory address
  		blt $t2, $t4, For2

  	addi $t1, $t1, 1 # int i += 1
  	blt $t1, $t3, For1
  
  
  # setup up return values
  move $v0, $t3
  move $v1, $t4
  # Note: third return value goes on the stack *after* restoration below
  # restore stack, ra, and any saved registers, if necessary
  # return to main
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
  # Allocate sufficient space
  # set return value
  # restore stack, ra, and any saved registers, if necessary
  # return to main
  mul $t0, $a0, $a1
  sll $t0, $t0, 2 # size of bits to allocate

  move $a0, $t0
  li $v0, 9
  syscall
  
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
  move $t0, $a2
  move $t1, $zero # int i = 0
  ForP1:
  	move $t2, $zero # int j = 0
  	ForP2:
      li $v0, 1
      move $t3, $a0
      lw $a0, 0($t0)
      syscall
      li $v0, 4
      la $a0, tab
      syscall
      move $a0, $t3

  		addi $t2, $t2, 1 # int j += 1
      addi $t0, $t0, 4 # increment memory address
  		blt $t2, $a1, ForP2
    move $t3, $a0
    li $v0, 4
    la $a0, newline
    syscall
    move $a0, $t3
  	addi $t1, $t1, 1 # int i += 1
  	blt $t1, $a0, ForP1
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

  # #print out values to show that it is working
  # li $v0 1
  # syscall
  # move $a0 $a1
  # syscall
  # move $a0 $a2
  # syscall

  # move $a0 $a3
  # syscall

  # move $a0 $sp
  # syscall
  

  # save return address and any saved registers on the stack, if necessary
  move $t3, $ra # save return address

  # set up and call mm_alloc for result matrix
  move $t6, $a0
  move $t4, $a1 # save $a1 in $t4
  move $a1, $a3 # borrow a3 to do the call
  jal mm_alloc #v0 contains the address of the result matrix
  move $ra, $t3 # move return address back
  move $a1, $t4 # revert back the values
  move $a0, $t6

  # three nested loops for matrix-matrix multiplication
  move $t1, $zero # int i = 0
  ForMM1:
    move $t2, $zero # int j = 0
    
    ForMM2:
      move $t4, $zero # sum of the slot
      
      move $t3, $zero # int k = 0
      ForMM3:
        # getting mat1->data[i][k]
        move $t0, $a2 # $t0 contains the base address for matrix 1
        move $t6, $t1 # t6 = i
        mul $t6, $t6, $a3 # i times a3
        sll $t6, $t6, 2 # times 4
        add $t0, $t0, $t6 # t0 = $a2 + 4 x $a3 x $t1

        move $t6, $t3
        sll $t6, $t6, 2 # $t6 = 4 x $t3
        add $t0, $t0, $t6 # t0 = $a2 + 4 x $a3 x $t1 + 4 x $t3
        # $s6 now contains the address of data[i][k]
        move $s6, $t0
        
        # getting mat2->data[k][j]
        lw $t0, 0($sp)
        move $t6, $t3
        mul $t6, $t6, $a3 # times a3
        sll $t6, $t6, 2 # times 4
        add $t0, $t0, $t6

        move $t6, $t2
        sll $t6, $t6, 2
        add $t0, $t0, $t6
        move $s7, $t0 #$s7 contains the address of data[k][j]

        # get value stored at $s6 -> store at $t0
        lw $t0, 0($s6)

        # get value stored at $s7 -> store at $t6
        lw $t6, 0($s7)

        # multiply the two
        mul $t0, $t0, $t6
        add $t4, $t4, $t0 # add the value onto the sum

        addi $t3, $t3, 1
        blt $t3, $a1, ForMM3
      # get address of result_matrix->data[i][j]

      move $t0, $v0 # address for the result_matrix
      move $t6, $t1
      mul $t6, $t6, $a3
      sll $t6, $t6, 2
      add $t0, $t0, $t6 # data[i]

      move $t6, $t2
      sll $t6, $t6, 2
      add $t0, $t0, $t6 # data[i][j]

      sw $t4, 0($t0) # data[i][j] = sum
      addi $t2, $t2, 1
      blt $t2, $a3, ForMM2

    addi $t1, $t1, 1
    blt $t1, $a0, ForMM1
  # set return value

  # restore stack, ra, and any saved registers, if necessary

  # return to main
  jr  $ra
