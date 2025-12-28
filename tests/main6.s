	.data

	.text
	.globl main
main:
	li $t0, 1
	li $t1, 1
	li $v0, 5
	syscall
	move $t2, $v0
label0:
	move $t3, $t0
	move $t4, $t2
	bgt $t3, $t4, label2
label1:
	move $t3, $t1
	move $t4, $t0
	mul $t1, $t3, $t4
	move $t3, $t0
	li $t4, 1
	add $t0, $t3, $t4
	j label0
label2:
	move $t3, $t1
	move $a0, $t3
	li $v0, 1
	syscall
