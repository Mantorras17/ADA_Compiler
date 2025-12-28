#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genMIPS.h"
#include "code.h"

void print_mips(FILE* f,InstrList icode) {
	fprintf(f,"	.data\n");
	for (InstrList il = icode; il != NULL; il=il->next_instr) {
		Instr instr = il->instr;
		if (il->instr->tag == DATA_ALLOC_SPACE) {
			fprintf(f,"%s:	.space %d\n", instr->type.data_alloc_space.sl, instr->type.data_alloc_space.nbytes);
		}
		else if (il->instr->tag == DATA_ALLOC_STR) {
			fprintf(f,"%s:	.asciiz \"%s\\n\"\n", instr->type.data_alloc_str.sl, instr->type.data_alloc_str.str);
		}
	}

	fprintf(f,"\n");
	fprintf(f,"	.text\n");
	fprintf(f,"	.globl main\n");
	fprintf(f,"main:\n");
	for (InstrList il = icode; il != NULL; il=il->next_instr) {
		Instr instr = il->instr;
		switch (il->instr->tag) {
			case IR_ATTR:
				if (instr->type.attr.atom_tag == IR_INT) {
					fprintf(f,"	li $%s, %d\n", instr->type.attr.var1, instr->type.attr.atom.num);
				}
				else {
					fprintf(f,"	move $%s, $%s\n", instr->type.attr.var1, instr->type.attr.atom.var2);
				}
				break;
			case IR_OP_ATTR:
				switch (instr->type.op_attr.binop) {
					case AST_PLUS:
						if (instr->type.op_attr.atom_tag_right == IR_INT) {
							fprintf(f,"	addi $%s, $%s, $%d\n", instr->type.op_attr.var1, instr->type.op_attr.var2, instr->type.op_attr.atom_right.num);
						}
						else {
							fprintf(f,"	add $%s, $%s, $%s\n", instr->type.op_attr.var1, instr->type.op_attr.var2, instr->type.op_attr.atom_right.var3);
						}
						break;
					case AST_MINUS:
						fprintf(f,"	sub $%s, $%s, $%s\n", instr->type.op_attr.var1, instr->type.op_attr.var2, instr->type.op_attr.atom_right.var3);
						break;
					case AST_DIV:
						fprintf(f,"	div $%s, $%s, $%s\n", instr->type.op_attr.var1, instr->type.op_attr.var2, instr->type.op_attr.atom_right.var3);
						break;
					case AST_MULT:
						fprintf(f,"	mul $%s, $%s, $%s\n", instr->type.op_attr.var1, instr->type.op_attr.var2, instr->type.op_attr.atom_right.var3);
						break;
				}
				break;
			case IR_JUMP:
				fprintf(f,"	j %s\n", instr->type.jump.label);
				break;
			case IR_BRANCH:
				char op1[5], op2[5];
				switch (instr->type.branch.relop) {
					case AST_EQUAL:
						strcpy(op1,"beq");
						strcpy(op2,"bne");
						break;
					case AST_NOT_EQUAL:
						strcpy(op1,"bne");
						strcpy(op2,"beq");
						break;
					case AST_LESS:
						strcpy(op1,"blt");
						strcpy(op2,"bge");
						break;
					case AST_GREAT:
						strcpy(op1,"bgt");
						strcpy(op2,"ble");
						break;
					case AST_E_LESS:
						strcpy(op1,"ble");
						strcpy(op2,"bgt");
						break;
					case AST_E_GREAT:
						strcpy(op1,"bge");
						strcpy(op2,"blt");
						break;
				}
				if (il->next_instr != NULL && il->next_instr->instr->tag == IR_LABEL) {
					if (strcmp(instr->type.branch.label_false,il->next_instr->instr->type.label_start.label) == 0) {
						fprintf(f,"	%s $%s, $%s, %s\n", op1, instr->type.branch.var1, instr->type.branch.atom.var2, instr->type.branch.label_true);
					        fprintf(f,"%s:\n", instr->type.branch.label_false);
						il = il->next_instr;
					}
					else if (strcmp(instr->type.branch.label_true,il->next_instr->instr->type.label_start.label) == 0) {
						fprintf(f,"	%s $%s, $%s, %s\n", op2, instr->type.branch.var1, instr->type.branch.atom.var2, instr->type.branch.label_false);
						fprintf(f,"%s:\n", instr->type.branch.label_true);
						il = il->next_instr;
					}
					else {
						fprintf(f,"	%s $%s, $%s, %s\n", op1, instr->type.branch.var1, instr->type.branch.atom.var2, instr->type.branch.label_true);
						fprintf(f,"	j %s\n", instr->type.branch.label_false);
					}
				}
				else {
					fprintf(f,"	%s %s, %s, %s\n", op1, instr->type.branch.var1, instr->type.branch.atom.var2, instr->type.branch.label_true);
					fprintf(f,"	j %s\n", instr->type.branch.label_false);
				}
				break;
			case IR_LABEL:
				fprintf(f,"%s:\n", instr->type.label_start.label);
				break;
			case IR_PRINT_INT:
				if (instr->type.print_int.atom_tag == IR_INT) {
					fprintf(f,"	li $a0, %d\n", instr->type.print_int.atom.num);
				}
				else {
					fprintf(f,"	move $a0, $%s\n", instr->type.print_int.atom.var1);
				}
				fprintf(f,"	li $v0, 1\n");
				fprintf(f,"	syscall\n");
				break;
			case IR_READ_INT:
				fprintf(f,"	li $v0, 5\n");
				fprintf(f,"	syscall\n");
				fprintf(f,"	move $%s, $v0\n", instr->type.read_int.var1);
				break;
			case IR_PRINT_STRING:
				fprintf(f,"	la $a0 %s\n", instr->type.print_string.var1);
				fprintf(f,"	li $v0 4\n");
				fprintf(f,"	syscall\n");
				break;
			case IR_READ_STRING:
				fprintf(f,"	la $a0 %s\n", instr->type.read_string.var1);
				fprintf(f,"	move $a1 $%s\n", instr->type.read_string.var2);
				fprintf(f,"	li $v0 8\n");
				fprintf(f,"	syscall\n");
				break;
			case DATA_ALLOC_SPACE:
				break;
			case DATA_ALLOC_STR:
				break;
		}
	}
}
