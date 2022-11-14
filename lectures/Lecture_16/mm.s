# X = X + Y × Z        (initialize X to all zeros...)
# All 32 × 32 matrices, 64-bit double-precision elements
#void mm (double x[][],
#         double y[][], double z[][]) {
#  int i, j, k;
#  for (i = 0; i != 32; i = i + 1)
#    for (j = 0; j != 32; j = j + 1)
#      for (k = 0; k != 32; k = k + 1)
#        x[i][j] = x[i][j]
#                  + y[i][k] * z[k][j];
#}


        .data
newline:.asciiz "\n"
tab:    .asciiz "\t"
l_brckt:.asciiz "["
r_brckt:.asciiz "]"
zero:   .double 0.0

        # global parameter n, the size of matrices
n:      .word 2

txt1:   .asciiz "X = X + Y × Z\n"
txt2:   .asciiz "Please enter values for matrix Y ("
txt3:   .asciiz "Please enter values for matrix Z ("
txt4:   .asciiz "x"
txt5:   .asciiz "):\n"
txt6:   .asciiz "X = \n"
txt7:   .asciiz "Y = \n"
txt8:   .asciiz "Z = \n"

################################################################################

        .text
        .globl main
        .globl matrix_multiply
        .globl matrix_print
        .globl matrix_ask

################################################################################

matrix_zero:
        # Initizlize matrix values to zeros to store in
        # the memory address indicated by the $a0 register
        # Total number of elements is in $a1
        li 		$t0, 0        # loop counter

mz_head:
        # if the loop counter is less than $a1, go to ma_body
        #  otherwise go to ma_exit
        blt 	$t0, $a1, mz_body
        j 		mz_exit

mz_body:
        l.d 	$f0, zero
        sdc1	$f0, 0($a0)

mz_latch:
        addi 	$a0, $a0, 8
        addi 	$t0, $t0, 1
        j 		mz_head

mz_exit:
        jr $ra

################################################################################

matrix_ask:
        # Ask the user for the matrix values to store in
        # the memory address indicated by the $a0 register
        # Total numbers to ask for is in $a1
        li 		$t0, 0        # loop counter

ma_head:
        # if the loop counter is less than $a1, go to ma_body
        #  otherwise go to ma_exit
        blt 	$t0, $a1, ma_body
        j 		ma_exit

ma_body:
        li 		$v0, 7        # read_double
        syscall
        sdc1	$f0, 0($a0)

ma_latch:
        addi 	$a0, $a0, 8
        addi 	$t0, $t0, 1
        j 		ma_head

ma_exit:
        jr $ra

################################################################################

main:
        # Initialize stack as necessary
        addi	$sp, $sp, -4
        sw 		$ra, 0($sp)

        # Allocate space for matrices
        la 		$t0, n
        lw 		$s0, 0($t0)

        mul		$a0, $s0, $s0		# space for matrix X (n x n)
        sll 	$a0, $a0, 3 		# multiply by 8 to get bytes from double words
        li		$v0, 9
        syscall
        move	$s1, $v0				# location of matrix X

        mul		$a0, $s0, $s0		# space for matrix Y (n x n)
        sll 	$a0, $a0, 3 		# multiply by 8 to get bytes from double words
        li		$v0, 9
        syscall
        move	$s2, $v0				# location of matrix Y

        mul		$a0, $s0, $s0		# space for matrix Z (n x n)
        sll 	$a0, $a0, 3 		# multiply by 8 to get bytes from double words
        li		$v0, 9
        syscall
        move	$s3, $v0				# location of matrix Z

        # Initialize matrix X
        move 	$a0, $s1
        mul		$a1, $s0, $s0
        jal matrix_zero

        # Get input for matrix Y
        la 		$a0, txt2
        li 		$v0, 4        # print_str
        syscall

        move 	$a0, $s0
        li 		$v0, 1        # print_int
        syscall

        la 		$a0, txt4
        li 		$v0, 4        # print_str
        syscall

        move 	$a0, $s0
        li 		$v0, 1        # print_int
        syscall

        la 		$a0, txt5
        li 		$v0, 4        # print_str
        syscall

        move 	$a0, $s2
        mul		$a1, $s0, $s0
        jal matrix_ask

        # Get input for matrix Z
        la 		$a0, txt3
        li 		$v0, 4        # print_str
        syscall

        move 	$a0, $s0
        li 		$v0, 1        # print_int
        syscall

        la 		$a0, txt4
        li 		$v0, 4        # print_str
        syscall

        move 	$a0, $s0
        li 		$v0, 1        # print_int
        syscall

        la 		$a0, txt5
        li 		$v0, 4        # print_str
        syscall

        move 	$a0, $s3
        mul		$a1, $s0, $s0
        jal matrix_ask

        # Output X
        la 		$a0, txt6     # "X = \n"
        li 		$v0, 4        # print_str
        syscall
        move 	$a0, $s1
        move	$a1, $s0
        move	$a2, $s0
        jal matrix_print

        # Output Y
        la 		$a0, txt7     # "Y = \n"
        li 		$v0, 4        # print_str
        syscall
        move 	$a0, $s2
        move	$a1, $s0
        move	$a2, $s0
        jal matrix_print

        # Output Z
        la 		$a0, txt8     # "Z = \n"
        li 		$v0, 4        # print_str
        syscall
        move 	$a0, $s3
        move	$a1, $s0
        move	$a2, $s0
        jal matrix_print

        # Perform addition and  multiplication to get matrix X
        move 	$a0, $s1
        move 	$a1, $s2
        move 	$a2, $s3
        jal matrix_multiply

        # Output result
        la 		$a0, txt1     # "X = X + Y × Z\n"
        li 		$v0, 4        # print_str
        syscall

        # Output X
        la 		$a0, txt6     # "X = \n"
        li 		$v0, 4        # print_str
        syscall
        move 	$a0, $s1
        move	$a1, $s0
        move	$a2, $s0
        jal matrix_print

        # Cleanup stack and return
        lw 		$ra, 0($sp)
        addi 	$sp, $sp, 4

        jr $ra


##############################################################################

matrix_multiply:
        # Compute X = X + Y × Z for matrix X (address $a0), matrix Y (address $a1),
        # and matrix Z (address $a2)

        addi 	$sp, $sp, -12
        sw 		$s2, 0($sp)
        sw 		$s1, 4($sp)
        sw 		$s0, 8($sp)

        la 		$t1, n           # $t1 = n (row size/loop end)
        lw 		$t1, 0($t1)      #
        li 		$s0, 0           # i = 0; initialize 1st for loop
    L1: li 		$s1, 0           # j = 0; restart 2nd for loop
    L2: li 		$s2, 0           # k = 0; restart 3rd for loop
        mul 	$t2, $s0, $t1    # $t2 = i * n (size of row of x)
        addu 	$t2, $t2, $s1    # $t2 = i * size(row) + j
        sll 	$t2, $t2, 3      # $t2 = byte offset of [i][j]
        addu 	$t2, $a0, $t2    # $t2 = byte address of x[i][j]
        l.d 	$f4, 0($t2)      # $f4 = 8 bytes of x[i][j]
    L3: mul 	$t0, $s2, $t1    # $t0 = k * n (size of row of z)
        addu 	$t0, $t0, $s1    # $t0 = k * size(row) + j
        sll 	$t0, $t0, 3      # $t0 = byte offset of [k][j]
        addu 	$t0, $a2, $t0    # $t0 = byte address of z[k][j]
        l.d 	$f16, 0($t0)     # $f16 = 8 bytes of z[k][j]

        mul 	$t0, $s0, $t1    # $t0 = i*n (size of row of y)
        addu 	$t0, $t0, $s2    # $t0 = i*size(row) + k
        sll 	$t0, $t0, 3      # $t0 = byte offset of [i][k]
        addu 	$t0, $a1, $t0    # $t0 = byte address of y[i][k]
        l.d 	$f18, 0($t0)     # $f18 = 8 bytes of y[i][k]
        mul.d $f16, $f18, $f16 # $f16 = y[i][k] * z[k][j]
        add.d $f4, $f4, $f16   # $f4=x[i][j] + y[i][k]*z[k][j]
        addiu $s2, $s2, 1      # k = k + 1
        bne 	$s2, $t1, L3     # if (k != n) go to L3
        s.d 	$f4, 0($t2)      # x[i][j] = $f4
        addiu $s1, $s1, 1      # j = j + 1
        bne 	$s1, $t1, L2     # if (j != n) go to L2
        addiu $s0, $s0, 1      # i = i + 1
        bne 	$s0, $t1, L1     # if (i != n) go to L1

        lw 		$s0, 8($sp)     # restore $s0
        lw 		$s1, 4($sp)	     # restore $s1
        lw 		$s2, 0($sp)	     # restore $s2
        addi 	$sp, $sp, 12

        jr $ra

################################################################################

matrix_print:
        # print matrix (address $a0) with # rows ($a1) and # columns ($a2)
        move 	$t0, $a0      # save $a0 to $t0
        move 	$t1, $a1      # save $a1 to $t1
        move 	$t2, $a2      # save $a2 to $t2
        li 		$t3, 0        # loop row counter

mp_row_head:
        # if the loop row counter is less than $t1, go to mp_row_body
        #  otherwise go to mp_row_exit
        blt 	$t3, $t1, mp_row_body
        j 		mp_row_exit

mp_row_body:
        la 		$a0, l_brckt		# "["
        li 		$v0, 4        # print_str
        syscall
        li 		$t4, 0        # loop column counter

mp_col_head:
        # if the loop column counter is less than $t2, go to mp_col_body
        #  otherwise go to mp_col_exit
        blt 	$t4, $t2, mp_col_body
        j 		mp_col_exit

mp_col_body:
        l.d 		$f12, 0($t0)
        li 		$v0, 3        # print_double
        syscall
        la 		$a0, tab		# "\t"
        li 		$v0, 4        # print_str
        syscall

mp_col_latch:
        addi 	$t0, $t0, 8
        addi 	$t4, $t4, 1
        j 		mp_col_head

mp_col_exit:
        la 		$a0, r_brckt		# "]"
        li 		$v0, 4        # print_str
        syscall
        la 		$a0, newline		# "\n"
        li 		$v0, 4        # print_str
        syscall

mp_row_latch:
        addi 	$t3, $t3, 1
        j 		mp_row_head

mp_row_exit:
        jr $ra
