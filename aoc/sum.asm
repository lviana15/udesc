.data
	error: .asciiz "ERRO"
.text
.globl main
main:
	li $s0, 0
	li $s1, 0
	li $s2, 0
while:
	li $v0, 5
	syscall
	move $s0, $v0
	beq $s0, -1, sum
	addi $s1, $s1, 1
	addu $s2, $s2, $s0 
	bne $s0, -1, while
zero:
	move $a0, $s1
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 10
	syscall
	li $v0, 4
	la $a0, error
	syscall
	j end
sum:
	beqz $s1, zero
	move $a0, $s2
	li $v0, 1
	syscall
	li $v0, 11
	li $a0, 10
    	syscall
	div $s2, $s2, $s1
	move $a0, $s2
	li $v0, 1
	syscall 	
	j end
end:
	li $v0, 10
	syscall