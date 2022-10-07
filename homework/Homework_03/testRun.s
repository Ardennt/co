.data
    myMessage: .asciiz "hello my guy\n"
.text
    li $v0 4
    la $a0, myMessage
    syscall