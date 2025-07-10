.text
.globl main
main:
     li $a0, 4
     jal fatorial
     move $a0, $v0
     li $v0, 1
     syscall
end:
    li $v0, 10
    syscall
fatorial:
    blt $a0, 1, fat_parada
    move $s0, $a0
    addi $a0, $a0, -1
    jal fatorial
    mul $v0, $v0, $a0
fat_parada:
    ori $v0, $zero, 1
    jr $ra
