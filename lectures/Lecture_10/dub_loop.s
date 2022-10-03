################################################################################
## Data segment
################################################################################
.data
  # our matrix is a 4x2 matrix
  matrix:       .word   1, 2, 3, 4, 5, 6, 7, 8
  num_rows:     .word   4
  num_cols:     .word   2
  newline:      .asciiz "\n"

################################################################################
## Text segment
################################################################################
.text         
  .align 2        # instructions must be on word boundaries
  .globl main     # main is a global label

################################################################################
# Our main donkey
################################################################################
main:
  sub $sp, $sp, 4   # allocate stack space to store $ra (return address pointer)
  sw  $ra, 0($sp)   # store $ra onto the stack ($sp is stack pointer)


  li  $s1, 5  # If we use a saved register, it should stay the same through
              # a function call. Even if the callee uses the same saved 
              # register. It's the callee's job to ensure consistency through
              # use of the stack.

  # We're going to print out our matrix
  jal print_matrix

  li    $v0, 1    # going to print out s1 to make sure it has the same value
  move  $a0, $s1
  syscall  

  # restore $ra, free stack space, and return
  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr  $ra


################################################################################
# Print function
# Note: We're going to use s0-s2 to save the matrix variables
# - We need to save them on the stack!
################################################################################
print_matrix:
  sub $sp, $sp, 16  # allocate stack space to store $ra (return address pointer)
  sw  $ra, 0($sp)   # store $ra onto the stack ($sp is stack pointer)
  sw  $s0, 4($sp)   # Store the saved registers - per MIPS convention, we need
  sw  $s1, 8($sp)   #  to restore them to their original values on return. 
  sw  $s2, 12($sp)  # the calling function should have a consistent view of them


  la  $s0, matrix   # matrix base address
  la  $s1, num_rows # num rows of matrix
  lw  $s1, 0($s1)
  la  $s2, num_cols # num cols of matrix
  lw  $s2, 0($s2)

  li  $t0, 0  # loop counter for num rows
loop_row:
  beq $t0, $s1, done_row

  li  $t1, 0  # loop counter for num cols
loop_col:
  beq $t1, $s2, done_col

  # address = base + offset
  # get address as s0 + 4*(num_cols*t0 + t1)
  # base = address in s0
  # offset = sizeof(int)*(row_length*row_counter + col_counter)
  # Note: row_length == num_cols
  mul $t2, $t0, $s2   # row_length*row_counter
  add $t2, $t2, $t1   # row_length*row_counter + col_counter
  sll $t2, $t2, 2     # sizeof(int)*(row_length*row_counter + col_counter)
  add $t2, $t2, $s0   # base + offset

  # print value
  li  $v0, 1
  lw  $a0, 0($t2)
  syscall

  # increment counter
  add $t1, $t1, 1
  j loop_col

done_col:
  # at end of row  - print new line
  li  $v0, 4
  la  $a0, newline
  syscall

  add $t0, $t0, 1
  j loop_row

done_row:  
  # finished - restore stack and return
  lw  $ra, 0($sp)
  lw  $s0, 4($sp)
  lw  $s1, 8($sp)
  lw  $s2, 12($sp)
  add $sp, $sp, 16 
  jr  $ra
