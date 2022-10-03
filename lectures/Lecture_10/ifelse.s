################################################################################
## Data segment
################################################################################
.data 
  oneszeros:    .word   1, 0, 1, 0, 1

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

  # We're going to flip our bits using loops and the power if if-else

  # set length of array
  li  $t0, 5

  # base address of array
  la  $t1, oneszeros

  # loop counter
  li  $t2, 0

loop:
  slt $t3, $t2, $t0 # t3 = 1 if t2 < t0, else t3 = 0
  beq $t3, $0, exit # if t3 == 0, goto exit

  # current value at current index -> t3
  # note that we can keep re-using the same temp register
  sll $t3, $t2, 2
  add $t3, $t3, $t1
  lw  $t4, 0($t3)

  # if t3 == 0 goto, else continue on
  beq $t4, $0, equal
  li  $t4, 0
  sw  $t4, 0($t3)
  j done
equal:
  li  $t4, 1
  sw  $t4, 0($t3)
done:

  # update counter
  add $t2, $t2, 1
  j loop
exit:

  # output new array
  li  $v0, 1
  lw  $a0, 0($t1)
  syscall
  lw  $a0, 4($t1)
  syscall
  lw  $a0, 8($t1)
  syscall
  lw  $a0, 12($t1)
  syscall
  lw  $a0, 16($t1)
  syscall

  # restore $ra, free stack space, and return
  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr  $ra
