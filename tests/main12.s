	.data
str0:	.asciiz "\n"

	.text
	.globl main
main:
	li $t0, 1
	li $v0, 5
	syscall
	move $t1, $v0
label0:
	move $t2, $t0
	move $t3, $t1
	bgt $t2, $t3, label2
label1:
	move $t2, $t0
	move $a0, $t2
	li $v0, 1
	syscall
	la $a0 str0
	li $v0 4
	syscall
	move $t3, $t0
	li $t4, 1
	add $t0, $t3, $t4
	j label0
label2:
