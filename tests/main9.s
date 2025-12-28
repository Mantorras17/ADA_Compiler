	.data
str0:	.asciiz "Positive\n"
str1:	.asciiz "Negative\n"
str2:	.asciiz "Zero\n"

	.text
	.globl main
main:
	li $v0, 5
	syscall
	move $t0, $v0
	move $t1, $t0
	li $t2, 0
	ble $t1, $t2, label1
label0:
	la $a0 str0
	li $v0 4
	syscall
	j label2
label1:
	move $t1, $t0
	li $t2, 0
	bge $t1, $t2, label4
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
label2:
