addi $sp, $zero, 6000   # Assume Stack memory starts at 6000. Do not modify.

# Procedure Main (Do not modify)
Main:
      add $a0, $zero, $s0
      add $a1, $zero, $s1
      
      jal Sum
      
      add $s2, $s0, $s1
      add $s2, $s2, $v0
      
      j End

# Procedure Sum
Sum:
      # Type your code here.
      # m = a0
      # n = a1
      move $t0, $ra # store address
      move $t1, $a0 # store m
      move $t2, $a1 # store n
      
      addi $a0, $t2, 1 # value of n + 1
      addi $a1, $t1, -1 # value of m - 1
      jal Dif
      move $t3, $v0 # contains the value of Dif(n+1, m-1);
      
      addi $a1, $t2, -1 # n - 1
      addi $a0, $t1, 1 # m + 1
      jal Dif
      move $t4, $v0 # contains the value of Dif(m+1, n-1);

      add $v0, $t3, $t4
      move $ra, $t0 # restore address
      jr $ra
      

# Procedure Dif (Do not modify)
Dif:
      sub $v0, $a1, $a0
      jr $ra

End:
