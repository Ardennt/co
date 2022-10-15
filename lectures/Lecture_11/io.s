################################################################################
## Data segment
################################################################################
.data 
  value:        .asciiz "Our value is: "
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

  # We're going to read in an integer from stdin, then print it out to stdout
  # We'll also be working with our nice strings given above

  # Read in an integer
  li    $v0, 5      # syscall value for 'read integer'
  syscall           # note: syscall will overwrite v0 with value read
  move  $t0, $v0    # store the value so we can print it out

  # print it out
  li    $v0, 4      # syscall for 'print string'
  la    $a0, value  # set argument for print string to 'value' in data segment
  syscall           # do the business

  li    $v0, 1      # syscall for 'print integer'
  move  $a0, $t0    # set argument as integer we read in
  syscall           # business time

  li    $v0, 4        # syscall for 'print string'
  la    $a0, newline  # set argument for print string to 'newline'
  syscall             # once more

  # restore $ra, free stack space, and return
  lw  $ra, 0($sp)
  add $sp, $sp, 4
  jr  $ra
