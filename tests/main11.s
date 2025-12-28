	.data
str0:	.asciiz "Faster\n"
str1:	.asciiz "Ok\n"
str2:	.asciiz "Slower\n"

	.text
	.globl main
main:
	li $t0, 0
label0:
	move $t1, $t0
	li $t2, 3
	bge $t1, $t2, label2
label1:
	move $t1, $t0
	li $t2, 0
	bne $t1, $t2, label4
label3:
	la $a0 str0
	li $v0 4
	syscall
	j label5
label4:
	move $t1, $t0
	li $t2, 1
	bne $t1, $t2, label7
label6:
	la $a0 str1
	li $v0 4
	syscall
	j label8
label7:
	move $t1, $t0
	li $t2, 2
	bne $t1, $t2, label10
label9:
	la $a0 str2
	li $v0 4
	syscall
label10:
label8:
label5:
	move $t1, $t0
	li $t2, 1
	add $t0, $t1, $t2
	j label0
label2:
