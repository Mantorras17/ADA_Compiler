	.data
str0:	.asciiz "B is less than 100\n"
str1:	.asciiz "B is large\n"
str2:	.asciiz "A is not less than B\n"

	.text
	.globl main
main:
	li $v0, 5
	syscall
	move $t0, $v0
	li $v0, 5
	syscall
	move $t1, $v0
	move $t2, $t0
	move $t3, $t1
	bge $t2, $t3, label1
label0:
	move $t2, $t1
	li $t3, 100
	bge $t2, $t3, label4
label3:
	la $a0 str0
	li $v0 4
	syscall
	j label5
label4:
	la $a0 str1
	li $v0 4
	syscall
label5:
	j label2
label1:
	la $a0 str2
	li $v0 4
	syscall
label2:
