################################################################################
## Data segment
################################################################################
.data 

################################################################################
## Text segment
################################################################################
.text         
  .align 2        # instructions must be on word boundaries
  .globl main     # main is a global label

################################################################################
# Our main pup
################################################################################
main:
  sub $sp, $sp, 4   # allocate stack space to store $ra (return address pointer)
  sw  $ra, 0($sp)   # store $ra onto the stack ($sp is stack pointer)

  # read in an integer value
  li    $v0, 5
  syscall
  move  $a0, $v0

  # call factorial
  jal fact

  # output result
  move  $a0, $v0  # v0 holds result from function call
  li    $v0, 1
  syscall

  # restore $ra, free stack space, and return
  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr  $ra

################################################################################
# factorial function
################################################################################
fact:
  addi  $sp, $sp, -8  # adjust stack for 2 items
  sw    $ra, 4($sp)   # save return address
  sw    $a0, 0($sp)   # save argument

  slti  $t0, $a0, 1     # test for n < 1
  beq   $t0, $zero, L1  # branch if not so

  addi  $v0, $zero, 1 # if so, result is 1
  addi  $sp, $sp, 8   # pop 2 items from stack
  jr    $ra           # and return

L1: 
  addi  $a0, $a0, -1  # else decrement n
  jal fact            # recursive call

  lw    $a0, 0($sp)   # restore original n
  lw    $ra, 4($sp)   # and return address
  addi  $sp, $sp, 8   # pop 2 items from stack
  mul   $v0, $a0, $v0 # multiply to get result
  jr    $ra           # and return
