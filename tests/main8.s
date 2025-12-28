	.data
str0:	.space 255
str1:	.asciiz "Type something:\n"

	.text
	.globl main
main:
	la $a0 str1
	li $v0 4
	syscall
	li $t0, 50
	la $a0 str0
	move $a1 $t0
	li $v0 8
	syscall
	la $a0 str0
	li $v0 4
	syscall
