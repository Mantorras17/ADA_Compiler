	.data
str0:	.space 256
str1:	.asciiz "Hello: \n"

	.text
	.globl main
main:
	li $t0, 256
	la $a0 str0
	move $a1 $t0
	li $v0 8
	syscall
	la $a0 str1
	li $v0 4
	syscall
	la $a0 str0
	li $v0 4
	syscall
