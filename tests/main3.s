	.data
str0:	.asciiz "\n"

	.text
	.globl main
main:
	li $t0, 0
label0:
	move $t1, $t0
	li $t2, 5
	bge $t1, $t2, label2
label1:
	move $t1, $t0
	li $t2, 1
	add $t0, $t1, $t2
	move $t1, $t0
	move $a0, $t1
	li $v0, 1
	syscall
	la $a0 str0
	li $v0 4
	syscall
	j label0
label2:
