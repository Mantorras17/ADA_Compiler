	.data
str0:	.asciiz "More than a thousand!\n"
str1:	.asciiz "Not Negative\n"
str2:	.asciiz "Negative\n"

	.text
	.globl main
main:
	li $v0, 5
	syscall
	move $t0, $v0
	move $t1, $t0
	li $t2, 1000
	ble $t1, $t2, label1
label0:
	la $a0 str0
	li $v0 4
	syscall
label1:
	move $t1, $t0
	li $t2, 0
	blt $t1, $t2, label3
label2:
	la $a0 str1
	li $v0 4
	syscall
	j label4
label3:
	la $a0 str2
	li $v0 4
	syscall
label4:
