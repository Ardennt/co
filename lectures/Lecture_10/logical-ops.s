# x = 9 == 1001 binary
# z = x << 4
# print z
# x = x >> 2
# print x
# y = 255 == 11111111 binary
# z = x & y
# print z
# z = x | y
# print z
# z = ~(x | 0) + 1

      .data
str:  .asciiz "\n"

      .text
      .globl main
main: li    $s0, 9
      
      # saving return address -- don't worry about this yet
      addi  $sp, $sp, -4
      sw    $ra, 0($sp)      

      sll   $s2, $s0, 4   # z = x << 4
      jal   prnt
      srl   $s2, $s0, 2   # z = x >> 2
      jal   prnt
      li    $s1, 255      # y = 255      
      and   $s2, $s0, $s1 # z = x & y
      jal   prnt
      or    $s2, $s0, $s1 # z = x | y
      jal   prnt
      nor   $s2, $s0, $zero # z = ~(x | 0) + 1, 2's complement
      addi  $s2, $s2, 1
      jal   prnt

      # restore original return address
      lw    $ra, 0($sp)    
      addi  $sp, $sp, 4
      jr    $ra           # return to caller

prnt: li    $v0, 1        # setup print_int syscall
      move  $a0, $s2      # print z
      syscall
      li    $v0, 4        # setup print_str syscall
      la    $a0, str      # print newline
      syscall

      jr $ra              # go back
