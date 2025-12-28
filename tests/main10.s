	.data

	.text
	.globl main
main:
	li $t1, 0
	li $t2, 1
	li $v0, 5
	syscall
	move $t0, $v0
	move $t5, $t0
	li $t6, 0
	beq $t5, $t6, label0
label3:
	move $t5, $t0
	li $t6, 1
	bne $t5, $t6, label1
label0:
	move $t5, $t0
	move $a0, $t5
	li $v0, 1
	syscall
	j label2
label1:
	li $t4, 2
label4:
	move $t6, $t4
	move $t7, $t0
	bgt $t6, $t7, label6
label5:
	move $t6, $t4
	li $t7, 1
	add $t4, $t6, $t7
	move $t6, $t1
	move $t7, $t2
	add $t3, $t6, $t7
	move $t1, $t2
	move $t2, $t3
	j label4
label6:
	move $t6, $t3
	move $a0, $t6
	li $v0, 1
	syscall
label2:
