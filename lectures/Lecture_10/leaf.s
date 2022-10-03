# int leaf_example (int g, int h, int i, int j)
# { 
#   int f = (g + h) - (i + j);
#   return f;
# }

      .text
      .globl main
main: li    $a0, 1          # g = 1
      li    $a1, 2          # h = 2
      li    $a2, 3          # i = 3
      li    $a3, 4          # j = 4

      addi  $sp, $sp, -4    # store current $ra
      sw    $ra, 0($sp)       

      jal   leaf            # make call

      lw    $ra, 0($sp)     # restore $ra
      addi  $sp, $sp, 4    

      move  $a0, $v0        # print return value
      li    $v0, 1          
      syscall

      jr $ra                # done, return to caller

leaf: addi  $sp, $sp, -4    # save s0 since we'll be overwriting it
      sw    $s0, 0($sp)
      add   $t0, $a0, $a1   # s0 = (a0 + a1) - (a2 + a3)
      add   $t1, $a2, $a3
      sub   $s0, $t0, $t1
      add   $v0, $s0, $zero # copy $s0 to $v0
      lw    $s0, 0($sp)     # restore original $s0
      addi  $sp, $sp, 4
      jr    $ra

