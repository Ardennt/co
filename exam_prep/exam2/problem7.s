
# $a0 = arr1 $a1 = arr2 $a2 = length


swap_array_values:
    move $t0, $zero
    forloop:
        # get address of arr1[i]
        sll $t1, $t0, 2 # address offset
        add $t1, $t1, $a0 # address of arr1[i] in t1
        lw $t2, 0($t1) # get value of arr1[i] in $t2

        # get address of arr2[i]
        sll $t3, $t0, 2 # address offset
        add $t3, $t3, $a1 # address of arr2[i] in t3
        lw $t4, 0($t3) # get value of arr2[i] in $t4

        sw $t4, 0($t1)
        sw $t2, 0($t3)

        addi $t0, $t0, 1
        bne $t0, $a2, forloop
    
    jr $ra