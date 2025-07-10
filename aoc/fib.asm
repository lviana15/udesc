.text
.globl main

main:
    li $v0, 5
    syscall
    move $a0, $v0
    
    jal fib
    
    move $t0, $v0
        
    li $v0, 1
    move $a0, $t0
    syscall
    
end:
    li $v0, 10
    syscall

fib:
    addi $sp, $sp, -12
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
    
    move $s0, $a0

    li $t0, 2
    blt $a0, $t0, case_one
    beq $a0, $t0, case_two

    addi $a0, $s0, -1
    jal fib
    
    move $s1, $v0
    
    addi $a0, $s0, -2
    jal fib
    
    add $v0, $s1, $v0
    j fib_end

case_one:
    ori $v0, $zero, 1
    j fib_end

case_two:
    ori $v0, $zero, 2
    j fib_end

fib_end:
    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    addi $sp, $sp, 12
    
    jr $ra
