# for (x = 0; x < 5; ++x)
#   print x

      .text
      .globl main
main: li   $s0, 0             # x = 0

Loop: slti $t0, $s0, 5        # $t0 = 1 if x < 5
      beq  $t0, $zero, Done   # goto done if $t0 == 0, or x !< 5
      li   $v0, 1             # set up print_int system call
      move $a0, $s0
      syscall
      addi $s0, $s0, 1        # ++x
      j    Loop               # jump back to start of loop
      
Done: jr $ra                  # return to caller
