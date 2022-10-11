# Type your code here.
# Do not initialize memory here.
# Use the + button under the Memory display to initialize memory at address 5000.

addi $t0, $t0, 5000 # load 5000 as base address
addi $t1, $t1, 5004 # load 5004, store in here the value of N x 8
addi $t2, $t2, 5008 # load 5008, store in here the value of N / 16

lw $t3, 0($t0) # store the value in address 5000 here

sll $t4, $t3, 3
srl $t5, $t3, 4

sw $t4, 0($t1)
sw $t5, 0($t2)