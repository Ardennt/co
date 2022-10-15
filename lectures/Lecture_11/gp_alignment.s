.data
  hexprefix:     .asciiz "0x"
  .align 2           # Try commenting out this line
  hexdigits:     .asciiz "0" "1" "2" "3" "4" "5" "6" "7" "8" "9" "A" "B" "C" "D" "E" "F"

.text
  .globl main

main:
  sub  $sp, $sp, 4   # Allocate stack space to store $ra (return address pointer)
  sw   $ra, 0($sp)   # Store $ra onto the stack ($sp is stack pointer)

  #addi $t0, $t0, -32000

  la   $t0, hexdigits
  lw   $t1, hexdigits
  #lw   $t2, 0x8004($gp) # 0x8004($gp)
  #lw   $t2, 0x7fff($gp)
  #lw   $t2, 0x8000($gp)

  # Restore $ra, free stack space, and return (since we're in main - we exit)
  lw   $ra, 0($sp)
  add  $sp, $sp, 4

  # Done, return to caller
  li   $v0, 10
  syscall
