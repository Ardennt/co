      .data
fahr: .float 21.5
cel:  .float -32.749
freez:
      .float 0.0
diver:
      .asciiz "\n-----\n"
txt1: .asciiz "\nCold!\n"
txt2: .asciiz "\nNot too bad\n"
const5:
      .float 5.0
const9:
      .float 9.0
const32:
      .float 32.0

      .text
      .globl main

main: addi  $sp, $sp, -4    # store current $ra
      sw    $ra, 0($sp)

      la $a0, fahr
      lwc1 $f12, 0($a0)
      li $v0, 2
      syscall

      la $a0, fahr
      lwc1 $f12, 0($a0)
      jal f2c
      la $a0, cel
      swc1 $f0, 0($a0)

      la $a0, diver
      li $v0, 4
      syscall

      la $a0, cel
      lwc1 $f12, 0($a0)
      li $v0, 2
      syscall

      la $a0, cel
      lwc1 $f0, 0($a0)
      la $a0, freez
      lwc1 $f1, 0($a0)
      c.lt.s $f0, $f1
      bc1t prn1
      la $a0, txt2
      li $v0, 4
      syscall
      j cont
prn1: la $a0, txt1
      li $v0, 4
      syscall

cont: lw    $ra, 0($sp)     # restore $ra
      addi  $sp, $sp, 4
      jr    $ra             # return

f2c:  lwc1  $f16, const5
      lwc1  $f18, const9
      div.s $f16, $f16, $f18
      lwc1  $f18, const32
      sub.s $f18, $f12, $f18
      mul.s $f0,  $f16, $f18
      jr    $ra
