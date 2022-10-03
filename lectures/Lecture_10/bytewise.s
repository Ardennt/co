################################################################################
## Data segment
################################################################################
.data 
  string:       .asciiz "I am a string!"
  stringlen:    .word   14
  newline:      .asciiz "\n"

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

  # We're going to flip our string

  # get length
  la  $t0, stringlen  # need to get address of data first
  lw  $t0, 0($t0)     # then load it

  # set memory pointers to start and end bytes of string
  la  $t1, string   # start pointer
  add $t2, $t1, $t0 # end pointer
  sub $t2, $t2, 1   # make sure we're actually pointing at last index

loop:
  li  $v0, 4
  la  $a0, string
  syscall
  la  $a0, newline
  syscall

  slt $t3, $t2, $t1 # t3 = 1 if t2 < t1, else t3 = 0
  bne $t3, $0, exit # if t3 != 0, goto exit

  # swap bytes at t1 and t2
  lbu $t4, 0($t1)
  lbu $t5, 0($t2)
  sb  $t5, 0($t1)
  sb  $t4, 0($t2)

  # updated pointers
  add $t1, $t1, 1
  add $t2, $t2, -1
  j loop
exit:

  # output new string
  li  $v0, 4
  la  $a0, string
  syscall
  la  $a0, newline
  syscall

  # restore $ra, free stack space, and return
  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr  $ra
