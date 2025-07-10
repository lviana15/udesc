.text
.globl main

main:
loop:
    li $v0, 5
    syscall
    move $s0, $v0
    beqz $s0, end

    li $v0, 5
    syscall
    move $s1, $v0

    move $a0, $s0
    move $a1, $s1
    jal count_digits

    move $a0, $v0
    li $v0, 1
    syscall

    li $v0, 11
    li $a0, 10
    syscall

    j loop

end:
    li $v0, 10
    syscall

count_digits:
    addi $sp, $sp, -12
    sw $a0, 0($sp)
    sw $a1, 4($sp)
    sw $ra, 8($sp)

    beqz $a0, return_zero

    li $t0, 10
    rem $t1, $a0, $t0
    div $a0, $a0, $t0
    mflo $a0

    lw $a1, 4($sp)
    jal count_digit

    lw $a0, 0($sp)
    li $t0, 10
    rem $t1, $a0, $t0
    lw $a1, 4($sp)

    move $t2, $v0
    bne $t1, $a1, return_count

    addi $v0, $t2, 1
    j return_count

return_zero:
    li $v0, 0

return_count:
    lw $ra, 8($sp)
    addi $sp, $sp, 12
    jr $ra
