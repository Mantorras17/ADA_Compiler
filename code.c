#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"

static int temp = 0, label = 0, str_label = 0;

char* new_temp() {
	char *t = (char*)malloc(16);
	sprintf(t,"t%d",temp);
	temp++;
	return t;
}

void pop_temp(int k) {
	temp -= k;
}

char* new_label() {
	char *l = (char*)malloc(16);
	sprintf(l,"label%d",label);
	label++;
	return l;
}

char* new_str_label() {
	char *sl = (char*)malloc(16);
	sprintf(sl,"str%d",str_label);
	str_label++;
	return sl;
}

Instr mk_instr_attr_num(char* var,int num) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_ATTR;
	instr->type.attr.var1 = strdup(var);
	instr->type.attr.atom_tag = IR_INT;
	instr->type.attr.atom.num = num;
	return instr;
}

Instr mk_instr_attr_var(char* var1, char* var2) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_ATTR;
	instr->type.attr.var1 = strdup(var1);
	instr->type.attr.atom_tag = IR_VAR;
	instr->type.attr.atom.var2 = strdup(var2);
	return instr;
}

Instr mk_instr_op_attr_var_int(char* var1,AST_ExprOp op,char* var2,int num) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_OP_ATTR;
	instr->type.op_attr.var1 = strdup(var1);
	instr->type.op_attr.binop = op;
	instr->type.op_attr.atom_tag_right = IR_INT;
	instr->type.op_attr.var2 = strdup(var2);
	instr->type.op_attr.atom_right.num = num;
	return instr;
}

Instr mk_instr_op_attr_var_var(char* var1,AST_ExprOp op,char *var2,char *var3) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_OP_ATTR;
	instr->type.op_attr.var1 = strdup(var1);
	instr->type.op_attr.binop = op;
	instr->type.op_attr.atom_tag_right = IR_VAR;
	instr->type.op_attr.var2 = strdup(var2);
	instr->type.op_attr.atom_right.var3 = strdup(var3);
	return instr;
}


Instr mk_instr_jump(char *label) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_JUMP;
	instr->type.jump.label = strdup(label);
	return instr;
}

Instr mk_branch_atom_int(char *var,AST_BexprOp relop,int atom,char *label_true,char *label_false) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_BRANCH;
	instr->type.branch.var1 = strdup(var);
	instr->type.branch.relop = relop;
	instr->type.branch.atom_tag = IR_INT;
	instr->type.branch.atom.num = atom;
	instr->type.branch.label_true = strdup(label_true);
	instr->type.branch.label_false = strdup(label_false);
	return instr;
}

Instr mk_branch_atom_var(char *var,AST_BexprOp relop,char *atom,char *label_true,char *label_false) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_BRANCH;
	instr->type.branch.var1 = strdup(var);
	instr->type.branch.relop = relop;
	instr->type.branch.atom_tag = IR_VAR;
	instr->type.branch.atom.var2 = strdup(atom);
	instr->type.branch.label_true = strdup(label_true);
	instr->type.branch.label_false = strdup(label_false);
	return instr;
}

Instr mk_label(char *label) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_LABEL;
	instr->type.label_start.label = strdup(label);
	return instr;
}

Instr mk_print_int_num(int num) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_PRINT_INT;
	instr->type.print_int.atom_tag = IR_INT;
	instr->type.print_int.atom.num = num;
	return instr;
}

Instr mk_print_int_var(char *var) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_PRINT_INT;
	instr->type.print_int.atom_tag = IR_VAR;
	instr->type.print_int.atom.var1 = strdup(var);
	return instr;
}

Instr mk_read_int(char *var) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_READ_INT;
	instr->type.read_int.var1 = strdup(var);
	return instr;
}

Instr mk_print_string(char *var1) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_PRINT_STRING;
	instr->type.print_string.var1 = strdup(var1);
	return instr;
}

Instr mk_read_string(char *var1,char *var2) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = IR_READ_STRING;
	instr->type.read_string.var1 = strdup(var1);
	instr->type.read_string.var2 = strdup(var2);
	return instr;
}

Instr mk_data_alloc_space(char *var1,int nbytes) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = DATA_ALLOC_SPACE;
	instr->type.data_alloc_space.sl = strdup(var1);
	instr->type.data_alloc_space.nbytes = nbytes;
	return instr;
}

Instr mk_data_alloc_str(char *var1, char *str) {
	Instr instr = (Instr)malloc(sizeof(struct _Instr));
	instr->tag = DATA_ALLOC_STR;
	instr->type.data_alloc_str.sl = strdup(var1);
	instr->type.data_alloc_str.str = strdup(str);
	return instr;
}


InstrList mk_instr_list(Instr instr) {
	InstrList instr_list = (InstrList)malloc(sizeof(struct _InstrList));
	instr_list->instr = instr;
	instr_list->next_instr = NULL;
	return instr_list;
}

Instr getFirst(InstrList list_instr) {
	return list_instr->instr;
}

InstrList nextInstrs(InstrList list_instr) {
	return list_instr->next_instr;
}

InstrList append(InstrList left_list,InstrList right_list) {
	if (left_list == NULL) return right_list;
	InstrList new_list = (InstrList)malloc(sizeof(struct _InstrList));
	new_list->instr = getFirst(left_list);
	new_list->next_instr = append(nextInstrs(left_list),right_list);
	return new_list;
}



void printInstr(Instr instr) {
	switch (instr->tag) {
		case IR_ATTR:
			printf("%s := ", instr->type.attr.var1);
			switch (instr->type.attr.atom_tag) {
				case IR_INT:
					printf("%d", instr->type.attr.atom.num);
					break;
				case IR_VAR:
					printf("%s", instr->type.attr.atom.var2);
					break;
			}
			break;
		case IR_OP_ATTR:
			printf("%s := ", instr->type.op_attr.var1);
			printf("%s ", instr->type.op_attr.var2);
			switch (instr->type.op_attr.binop) {
				case AST_PLUS:
					printf("+");
					break;
				case AST_MINUS:
					printf("-");
					break;
				case AST_DIV:
					printf("/");
					break;
				case AST_MULT:
					printf("*");
					break;
			}
			switch (instr->type.op_attr.atom_tag_right) {
				case IR_INT:
					printf(" %d", instr->type.op_attr.atom_right.num);
					break;
				case IR_VAR:
					printf(" %s", instr->type.op_attr.atom_right.var3);
					break;
			}
			break;
		case IR_JUMP:
			printf("JUMP %s", instr->type.jump.label);
			break;
		case IR_BRANCH:
			printf("COND %s", instr->type.branch.var1);
			switch (instr->type.branch.relop) {
				case AST_EQUAL:
					printf(" == ");
					break;
				case AST_NOT_EQUAL:
					printf(" /= ");
					break;
				case AST_LESS:
					printf(" < ");
					break;
				case AST_GREAT:
					printf(" > ");
					break;
				case AST_E_LESS:
					printf(" <= ");
					break;
				case AST_E_GREAT:
					printf(" >= ");
					break;
			}
			switch (instr->type.branch.atom_tag) {
				case IR_INT:
					printf("%d ", instr->type.branch.atom.num);
					break;
				case IR_VAR:
					printf("%s ", instr->type.branch.atom.var2);
					break;
			}
			printf("THEN %s ELSE %s", instr->type.branch.label_true, instr->type.branch.label_false);
			break;
		case IR_LABEL:
			printf("LABEL %s", instr->type.label_start.label);
			break;
		case IR_PRINT_INT:
			switch (instr->type.print_int.atom_tag) {
				case IR_INT:
					printf("Print_Int %d", instr->type.print_int.atom.num);
					break;
				case IR_VAR:
					printf("Print_Int %s", instr->type.print_int.atom.var1);
					break;
			}
			break;
		case IR_READ_INT:
			printf("Read_Int %s", instr->type.read_int.var1);
			break;
		case IR_PRINT_STRING:
			printf("Print_String %s", instr->type.print_string.var1);
			break;
		case IR_READ_STRING:
			printf("Read_String %s %s", instr->type.read_string.var1, instr->type.read_string.var2);
			break;
		case DATA_ALLOC_SPACE:
			printf("%s[%d]", instr->type.data_alloc_space.sl, instr->type.data_alloc_space.nbytes);
			break;
		case DATA_ALLOC_STR:
			printf("%s = \"%s\"", instr->type.data_alloc_str.sl, instr->type.data_alloc_str.str);
			break;
	}
}

void printListInstr(InstrList list_instr) {
	if (list_instr != NULL) {
		printInstr(getFirst(list_instr));
		printf("\n");
		printListInstr(nextInstrs(list_instr));
	}
}



InstrList compileExpr(Hash_table symbol_table,Expr e,char *r) {
	InstrList list_instr = NULL;
	Instr instr;
	switch (e->tag) {
		case AST_EXPR_INT:
			instr = mk_instr_attr_num(r,e->attr.val);
			list_instr = mk_instr_list(instr);
			break;
		case AST_EXPR_ID:
			char *temp = (char*)lookup(symbol_table,e->attr.id);
			instr = mk_instr_attr_var(r,temp);
			list_instr = mk_instr_list(instr);
			break;
		case AST_EXPR_OP:
			char *t1 = new_temp();
			char *t2 = new_temp();
			InstrList left_list_instr = compileExpr(symbol_table,e->attr.binop.left,t1);
			InstrList right_list_instr = compileExpr(symbol_table,e->attr.binop.right,t2);
			list_instr = append(left_list_instr,right_list_instr);
			instr = mk_instr_op_attr_var_var(r,e->attr.binop.op,t1,t2);
			list_instr = append(list_instr,mk_instr_list(instr));
			pop_temp(2);
			break;
		case AST_EXPR_FLOAT:
			break;
	}
	return list_instr;
}


InstrList compileBool(Hash_table symbol_table,Bexpr b,char *labelTrue,char *labelFalse) {
	InstrList list_instr = NULL;
	char *l2;
	InstrList code1, code2;

	switch (b->tag) {
		case AST_BOP:
			char *t1 = new_temp(), *t2 = new_temp();
			code1 = compileExpr(symbol_table,b->attr.bbinop.left,t1), code2 = compileExpr(symbol_table,b->attr.bbinop.right,t2);
			list_instr = append(append(code1,code2),mk_instr_list(mk_branch_atom_var(t1,b->attr.bbinop.op,t2,labelTrue,labelFalse)));
			pop_temp(2);
			break;
		case AST_BCOMPOUND:
			switch (b->attr.compound.op) {
				case AST_AND:
					l2 = new_label();
					code1 = compileBool(symbol_table,b->attr.compound.left,l2,labelFalse);
					code2 = compileBool(symbol_table,b->attr.compound.right,labelTrue,labelFalse);
					list_instr = append(code1,append(mk_instr_list(mk_label(l2)),code2));
					break;
				case AST_OR:
					l2 = new_label();
					code1 = compileBool(symbol_table,b->attr.compound.left,labelTrue,l2);
					code2 = compileBool(symbol_table,b->attr.compound.right,labelTrue,labelFalse);
					list_instr = append(code1,append(mk_instr_list(mk_label(l2)),code2));
					break;
				case AST_XOR:
					break;
			}

			break;
		case AST_BNOT:
			list_instr = compileBool(symbol_table,b,labelFalse,labelTrue);
			break;
		case AST_BVALUE: 
			switch (b->attr.value) {
				case AST_TRUE:
					list_instr = mk_instr_list(mk_instr_jump(labelTrue));
					break;
				case AST_FALSE:
					list_instr = mk_instr_list(mk_instr_jump(labelFalse));
					break;
			}
			break;
	}

	return list_instr;
}

InstrList compileStr(Hash_table symbol_table, Str_Expr str_expr) {
	InstrList list_instr = NULL, code1, code2;
	char *sl;
	if (str_expr == NULL) {
		sl = new_str_label();
		list_instr = mk_instr_list(mk_data_alloc_str(sl,""));
		return list_instr;
	}
	switch (str_expr->tag) {
		case AST_STR_STRING: 
			sl = new_str_label();
			code1 = mk_instr_list(mk_data_alloc_str(sl,str_expr->attr.sval));
			code2 = mk_instr_list(mk_print_string(sl));
			list_instr = append(code1,code2);
			break;
		case AST_STR_ID:
			sl = (char*)lookup(symbol_table,str_expr->attr.id);
			list_instr = mk_instr_list(mk_print_string(sl));
			break;
		case AST_STR_IMAGE:
			/*
			if (str_expr->attr.image.type == AST_TYPE_INT) {
				t = new_temp(); 
			        code1 = compileExpr(symbol_table,stm->attr.put.expr,t);
			        instr1 = mk_instr_list(mk_print_int_var(t));
				list_instr = append(code1,instr1);
			}
			else {
				// TO DO AST_TYPE_FLOAT
			}
			*/
			break;
		case AST_STR_CONCAT:
			break;
	}
	return list_instr;
}

InstrList compileStm(Hash_table symbol_table,Stm stm) {
	InstrList list_instr = NULL, code1, code2, code3, instr1, instr2, instr3, instr4;
	char *l1, *l2, *l3, *t, *t1, *sl;
	switch (stm->tag) {
		case AST_COMPOUND_STM:
			InstrList left = compileStm(symbol_table,stm->attr.compound.fst);
			InstrList right = compileStm(symbol_table,stm->attr.compound.snd);
			list_instr = append(left,right);
			break;
		case AST_ASSIGN_STM:
			t = (char*)lookup(symbol_table,stm->attr.assign.ident);
			list_instr = compileExpr(symbol_table,stm->attr.assign.expr,t);
			break;
		case AST_WHILE_STM:
			l1 = new_label();
			l2 = new_label();
			l3 = new_label();
			code1 = compileBool(symbol_table,stm->attr.while_stm.bexpr,l2,l3);
			code2 = compileStm(symbol_table,stm->attr.while_stm.stm);
			instr1 = mk_instr_list(mk_label(l1));
			instr2 = mk_instr_list(mk_label(l2));
			instr3 = mk_instr_list(mk_instr_jump(l1));
			instr4 = mk_instr_list(mk_label(l3));
			list_instr = append(append(append(instr1,code1),append(instr2,code2)),append(instr3,instr4));
			break;
		case AST_BRANCH_STM:
			if (stm->attr.branch.stm2 == NULL) {
				l1 = new_label();
				l2 = new_label();
				code1 = compileBool(symbol_table,stm->attr.branch.bexpr,l1,l2);
				code2 = compileStm(symbol_table,stm->attr.branch.stm1);
				instr1 = mk_instr_list(mk_label(l1));
				instr2 = mk_instr_list(mk_label(l2));
				list_instr = append(append(code1,instr1),append(code2,instr2));
			}
			else {
				l1 = new_label();
				l2 = new_label();
			        l3 = new_label();
			        code1 = compileBool(symbol_table,stm->attr.branch.bexpr,l1,l2);
			        code2 = compileStm(symbol_table,stm->attr.branch.stm1);
			        code3 = compileStm(symbol_table,stm->attr.branch.stm2);
			        instr1 = mk_instr_list(mk_label(l1));
			        instr2 = mk_instr_list(mk_instr_jump(l3));
			        instr3 = mk_instr_list(mk_label(l2));
			        instr4 = mk_instr_list(mk_label(l3));
			        list_instr = append(append(append(code1,instr1),append(code2,instr2)),append(instr3,append(code3,instr4)));
			}
			break;
		case AST_PUT_LINE_STM:
			if (stm->attr.str_expr == NULL) {
				sl = new_str_label();
				char *s = strdup("");
				code1 = mk_instr_list(mk_data_alloc_str(sl,s));
				code2 = mk_instr_list(mk_print_string(sl));
				list_instr = append(code1,code2);
			}
			else {
				list_instr = compileStr(symbol_table,stm->attr.str_expr);
			}
			break;
		case AST_GET_LINE_STM:
			t = (char*)lookup(symbol_table,stm->attr.get_line.ident1);
			t1 = (char*)lookup(symbol_table,stm->attr.get_line.ident2);
			list_instr = mk_instr_list(mk_read_string(t,t1));
			break;
		case AST_PUT_STM:
			t = new_temp(); 
			code1 = compileExpr(symbol_table,stm->attr.put.expr,t);
			instr1 = mk_instr_list(mk_print_int_var(t));
			list_instr = append(code1,instr1);
			break;
		case AST_GET_STM:
			t = (char*)lookup(symbol_table,stm->attr.assign.ident);
			list_instr = mk_instr_list(mk_read_int(t));
			break;
		case AST_DECL_STM:
			t = new_temp();
			addEntry(symbol_table,stm->attr.decl.ident,(void*)t);
			if (stm->attr.decl.init != NULL) {
				list_instr = compileExpr(symbol_table,stm->attr.decl.init,t);
			}
			break;
		case AST_STR_DECL_STM:
			sl = new_str_label();
			addEntry(symbol_table,stm->attr.str_decl.ident,(void*)sl);
			switch (stm->attr.str_decl.type_decl) {
				case AST_STR_EXPR_DECL:
					list_instr = mk_instr_list(mk_data_alloc_str(sl,stm->attr.str_decl.str_attr_decl.s));
					break;
				case AST_GET_LINE_DECL:
					code1 = mk_instr_list(mk_data_alloc_space(sl,256));
					t = new_temp();
					code2 = mk_instr_list(mk_instr_attr_num(t,256));
					code3 = mk_instr_list(mk_read_string(sl,t));
					pop_temp(1);
					list_instr = append(code1,append(code2,code3));
					break;
				case AST_BUF_DECL:
					list_instr = mk_instr_list(mk_data_alloc_space(sl,stm->attr.str_decl.str_attr_decl.buf.right));
					break;
			}
			break;
	}
	return list_instr;
}
