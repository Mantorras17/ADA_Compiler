	.data
str0:	.asciiz "check\n"
str1:	.asciiz "Half\n"
str2:	.asciiz "More Than Half\n"

	.text
	.globl main
main:
	li $t0, 20
	li $t1, 0
label0:
	move $t2, $t1
	move $t3, $t0
	bge $t2, $t3, label2
label1:
	move $t4, $t1
	li $t5, 2
	mul $t2, $t4, $t5
	move $t3, $t0
	bgt $t2, $t3, label4
label3:
	la $a0 str1
	li $v0 4
	syscall
	j label5
label4:
	la $a0 str2
	li $v0 4
	syscall
label5:
	la $a0 str0
	li $v0 4
	syscall
	move $t2, $t1
	li $t3, 1
	add $t1, $t2, $t3
	j label0
label2:
