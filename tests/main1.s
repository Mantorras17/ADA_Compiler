	.data
str0:	.asciiz "\n"

	.text
	.globl main
main:
	li $t2, 2
	li $t3, 3
	add $t0, $t2, $t3
	move $t2, $t0
	li $t3, 4
	mul $t1, $t2, $t3
	move $t2, $t1
	move $a0, $t2
	li $v0, 1
	syscall
	la $a0 str0
	li $v0 4
	syscall
