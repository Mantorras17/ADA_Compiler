	.data
str0:	.asciiz "Hello, Ada!\n"
str1:	.asciiz "Hello, stranger!\n"

	.text
	.globl main
main:
	li $v0, 5
	syscall
	move $t0, $v0
	move $t1, $t0
	li $t2, 19
	bne $t1, $t2, label1
label0:
	la $a0 str0
	li $v0 4
	syscall
	j label2
label1:
	la $a0 str1
	li $v0 4
	syscall
label2:
