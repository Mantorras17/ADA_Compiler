#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

void removeQuotes(char *s) {
	int len = strlen(s);
	if (len <= 2) {
		s[0] = '\0';
		return;
	}
	memmove(s,s+1,len-1);
	s[len-2] = '\0';
}

Stm mk_compound(Stm s1,Stm s2) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_COMPOUND_STM;
	stm->attr.compound.fst = s1;
	stm->attr.compound.snd = s2;
	return stm;
}

Stm mk_assign(char *id,Expr e3) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_ASSIGN_STM;
	stm->attr.assign.ident = strdup(id);
	stm->attr.assign.expr = e3;
	return stm;
}

Stm mk_while(Bexpr b2,Stm s4) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_WHILE_STM;
	stm->attr.while_stm.bexpr = b2;
	stm->attr.while_stm.stm = s4;
	return stm;
}

Stm mk_branch(Bexpr b2,Stm s4,Stm s6) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_BRANCH_STM;
	stm->attr.branch.bexpr = b2;
	stm->attr.branch.stm1 = s4;
	stm->attr.branch.stm2 = s6;
	return stm; 
}

Stm mk_put_line(Str_Expr str_expr) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_PUT_LINE_STM;
	stm->attr.str_expr = str_expr;
	return stm;
}

Stm mk_put(Expr e) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_PUT_STM;
	stm->attr.put.expr = e;
	return stm;
}

Stm mk_declaration(char *id, AST_Type ty, Expr init) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_DECL_STM;
	stm->attr.decl.ident = strdup(id);
	stm->attr.decl.type = ty;
	stm->attr.decl.init = init;
	return stm;
}

Stm mk_declaration_string(char* id,char *s) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_STR_DECL_STM;
	stm->attr.str_decl.type_decl = AST_STR_EXPR_DECL;
	stm->attr.str_decl.ident = strdup(id);
	removeQuotes(s);
	stm->attr.str_decl.str_attr_decl.s = strdup(s); 
	return stm;
}

Stm mk_declaration_get_line_string(char* id) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_STR_DECL_STM;
	stm->attr.str_decl.type_decl = AST_GET_LINE_DECL;
	stm->attr.str_decl.ident = strdup(id);
	return stm;
}

Stm mk_declaration_buf_string(char* id,int l,int r) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_STR_DECL_STM;
	stm->attr.str_decl.type_decl = AST_BUF_DECL;
	stm->attr.str_decl.ident = strdup(id);
	stm->attr.str_decl.str_attr_decl.buf.left = l; 
	stm->attr.str_decl.str_attr_decl.buf.right = r; 
	return stm;
}

Stm mk_get_line(char *id1,char *id2) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_GET_LINE_STM;
	stm->attr.get_line.ident1 = strdup(id1);
	stm->attr.get_line.ident2 = strdup(id2);
	return stm;
}

Stm mk_get(char *id) {
	Stm stm = (Stm)malloc(sizeof(struct _stm));
	stm->tag = AST_GET_STM;
	stm->attr.get.ident = strdup(id);
	return stm;
}

Expr mk_int(int v) {
	Expr e = (Expr)malloc(sizeof(struct _expr));
	e->tag = AST_EXPR_INT;
	e->attr.val = v;
	return e;
}

Expr mk_float(double v) {
	Expr e = (Expr)malloc(sizeof(struct _expr));
	e->tag = AST_EXPR_FLOAT;
	e->attr.fval = v;
	return e;
}

Expr mk_ident(char *txt) {
	Expr e = (Expr)malloc(sizeof(struct _expr));
	e->tag = AST_EXPR_ID;
	e->attr.id = strdup(txt);
	return e;
}

Expr mk_op(AST_ExprOp op,Expr e1,Expr e3) {
	Expr e = (Expr)malloc(sizeof(struct _expr));
	e->tag = AST_EXPR_OP;
	e->attr.binop.op = op;
	e->attr.binop.left = e1;
	e->attr.binop.right = e3;
	return e;
}

Str_Expr mk_image(AST_Type ty, Expr arg) {
	Str_Expr str = (Str_Expr)malloc(sizeof(struct _str_expr));
	str->tag = AST_STR_IMAGE;
	str->attr.image.type = ty;
	str->attr.image.arg = arg;
	return str;
}

Str_Expr mk_string(char *s) {
	Str_Expr str = (Str_Expr)malloc(sizeof(struct _str_expr));
	str->tag = AST_STR_STRING;
	removeQuotes(s);
	str->attr.sval = strdup(s);
	return str;
}

Str_Expr mk_ident_string(char *txt) {
	Str_Expr str = (Str_Expr)malloc(sizeof(struct _str_expr));
	str->tag = AST_STR_ID;
	str->attr.id = strdup(txt);
	return str;
}

Str_Expr mk_concat(Str_Expr a, Str_Expr b) {
	Str_Expr str = (Str_Expr)malloc(sizeof(struct _str_expr));
	str->tag = AST_STR_CONCAT;
	str->attr.concat.left = a;
	str->attr.concat.right = b;
	return str;
}


Bexpr mk_bool(AST_BLit value) {
	Bexpr b = (Bexpr)malloc(sizeof(struct _bexpr));
	b->tag = AST_BVALUE;
	b->attr.value = value;
	return b;
}

Bexpr mk_compound_bbinop(AST_C_BexprOp op,Bexpr b1,Bexpr b3) {
	Bexpr b = (Bexpr)malloc(sizeof(struct _bexpr));
	b->tag = AST_BCOMPOUND;
	b->attr.compound.op = op;
	b->attr.compound.left = b1;
	b->attr.compound.right = b3;
	return b;
}

Bexpr mk_not_boolean(Bexpr b2) {
	Bexpr b = (Bexpr)malloc(sizeof(struct _bexpr));
	b->tag = AST_BNOT;
	b->attr.negate = b2;
	return b;
}

Bexpr mk_bbinop(AST_BexprOp op,Expr e1, Expr e2) {
	Bexpr b = (Bexpr)malloc(sizeof(struct _bexpr));
	b->tag = AST_BOP;
	b->attr.bbinop.op = op;
	b->attr.bbinop.left = e1;
	b->attr.bbinop.right = e2;
	return b;
}


void ident(int d) {
	for (int i=0; i<d; i++) printf(" ");
}

void print_bexpr(Bexpr bexpr,int d) {
	ident(d);
	switch (bexpr->tag) {
		case AST_BOP:
			printf("mk_bbinop(\n"); 
			ident(d+2);
			switch (bexpr->attr.bbinop.op) {
				case AST_NOT_EQUAL:
					printf("NOT_EQUAL");
					break;
				case AST_EQUAL:
					printf("EQUAL");
					break;
				case AST_LESS:
					printf("LESS");
					break;
				case AST_E_LESS:
					printf("E_LESS");
					break;
				case AST_GREAT:
					printf("GREAT");
					break;
				case AST_E_GREAT:
					printf("E_GREAT");
					break;
			}
			printf(",\n");
			print_expr(bexpr->attr.bbinop.left,d+2);
			printf(",\n");
			print_expr(bexpr->attr.bbinop.right,d+2);
			printf("\n"); ident(d); printf(")");
			break;
		case AST_BCOMPOUND:
			printf("mk_compound_bbinop(\n"); 
			ident(d+2);
			switch (bexpr->attr.compound.op) {
				case AST_AND:
					printf("AND");
					break;
				case AST_OR:
					printf("OR");
					break;
				case AST_XOR:
					printf("XOR");
					break;
			}
			printf(",\n");
			print_bexpr(bexpr->attr.compound.left,d+2);
			printf(",\n");
			print_bexpr(bexpr->attr.compound.right,d+2);
			printf("\n"); ident(d); printf(")");
			break;
		case AST_BNOT:
			printf("mk_not_boolean(\n");
			print_bexpr(bexpr->attr.negate,d+2);
			printf("\n"); ident(d); printf(")");
			break;
		case AST_BVALUE:
			printf("mk_bool(");
			switch (bexpr->attr.value) {
				case AST_TRUE:
					printf("True");
					break;
				case AST_FALSE:
					printf("False");
					break;
			}
			printf(")");
			break;
		default: perror("Unknown tag!");
	}
}

void print_expr(Expr expr,int d) {
	ident(d);
	switch (expr->tag) {
		case AST_EXPR_INT:
			printf("mk_int(%d)", expr->attr.val);
			break;
		case AST_EXPR_FLOAT:
			printf("mk_float(%f)", expr->attr.fval);
			break;
		case AST_EXPR_ID:
			printf("mk_ident(%s)", expr->attr.id);
			break;
		case AST_EXPR_OP:
			printf("mk_op(\n");
			ident(d+2);
			switch (expr->attr.binop.op) {
				case AST_PLUS:
					printf("PLUS");
					break;
				case AST_MINUS:
					printf("MINUS");
					break;
				case AST_MULT:
					printf("MULT");
					break;
				case AST_DIV:
					printf("DIV");
					break;
			}
			printf(",\n");
			print_expr(expr->attr.binop.left,d+2);
			printf(",\n");
			print_expr(expr->attr.binop.right,d+2);
			printf("\n"); ident(d); printf(")");
			break;
		default: perror("Unknown tag!");
	}
}

void print_str_expr(Str_Expr str,int d) {
	ident(d);
	switch (str->tag) {
		case AST_STR_STRING:
			printf("mk_string(\"%s\")", str->attr.sval);
			break;
		case AST_STR_ID:
			printf("mk_ident_string(%s)", str->attr.id);
			break;
		case AST_STR_IMAGE:
			printf("mk_image(\n");
			ident(d+2); printf("%s,\n", str->attr.image.type == AST_TYPE_FLOAT ? "Float" : "Integer");
			print_expr(str->attr.image.arg,d+2);
			printf("\n"); ident(d); printf(")");
			break;
		case AST_STR_CONCAT:
			printf("mk_concat(\n");
			print_str_expr(str->attr.concat.left,d+2);
			printf(",\n");
			print_str_expr(str->attr.concat.right,d+2);
			printf("\n"); ident(d); printf(")");
			break;
		default: perror("Unknown tag!");
	}
}

void print_stm(Stm stm,int d) {
	ident(d);
	switch (stm->tag) {
		case AST_COMPOUND_STM:
			printf("mk_compound(\n");
			print_stm(stm->attr.compound.fst,d+2); 
			printf(",\n");
			print_stm(stm->attr.compound.snd,d+2);
			printf("\n"); ident(d); printf(")");
			break;
		case AST_ASSIGN_STM:
			printf("mk_assign(\n");
			ident(d+2); printf("%s",stm->attr.assign.ident);
			printf(",\n");
			print_expr(stm->attr.assign.expr,d+2);
			printf("\n"); ident(d); printf(")");
			break;
		case AST_WHILE_STM:
			printf("mk_while(\n");
			print_bexpr(stm->attr.while_stm.bexpr,d+2);
			printf(",\n");
			print_stm(stm->attr.while_stm.stm,d+2);
			printf("\n"); ident(d); printf(")");
			break;
		case AST_BRANCH_STM:
			printf("mk_branch(\n");
			print_bexpr(stm->attr.branch.bexpr,d+2);
			printf(",\n");
			print_stm(stm->attr.branch.stm1,d+2);
			printf(",\n");
			if (stm->attr.branch.stm2) {
				print_stm(stm->attr.branch.stm2,d+2);
			}
			else {
				ident(d+2); printf("NULL");
			}
			printf("\n"); ident(d); printf(")");
			break;
		case AST_PUT_LINE_STM:
			printf("mk_put_line(");
			if (stm->attr.str_expr == NULL) {
				printf(")");
			}
			else {
				printf("\n");
				print_str_expr(stm->attr.str_expr,d+2);
				printf("\n"); ident(d); printf(")");
			}
			break;
		case AST_DECL_STM:
			printf("mk_declaration(");
			printf("\n"); ident(d+2); printf("%s,", stm->attr.decl.ident);
			printf("\n"); ident(d+2); printf("%s", stm->attr.decl.type == AST_TYPE_FLOAT ? "Float" : "Integer");
			printf(",\n");
			if (stm->attr.decl.init) {
				print_expr(stm->attr.decl.init,d+2);
			}
			else {
				ident(d+2); printf("NULL");
			}
			printf("\n"); ident(d); printf(")");
			break;
		case AST_GET_LINE_STM:
			printf("mk_get_line(%s,%s)", stm->attr.get_line.ident1, stm->attr.get_line.ident2);
			break;
		case AST_STR_DECL_STM:
			switch(stm->attr.str_decl.type_decl) {
				case AST_STR_EXPR_DECL:
					printf("mk_declaration_string(%s,\"%s\"", stm->attr.str_decl.ident, stm->attr.str_decl.str_attr_decl.s);
					break;
				case AST_GET_LINE_DECL:
					printf("mk_declaration_get_line_string(%s)", stm->attr.str_decl.ident);
					break;
				case AST_BUF_DECL:
					printf("mk_declaration_buf_string(%s,%d,%d)", stm->attr.str_decl.ident,stm->attr.str_decl.str_attr_decl.buf.left, stm->attr.str_decl.str_attr_decl.buf.right);
					break;
			}
			break;
		case AST_GET_STM:
			printf("mk_get(%s)", stm->attr.get.ident);
			break;
		case AST_PUT_STM:
			printf("mk_put(\n");
			print_expr(stm->attr.put.expr,d+2);
			printf("\n"); ident(d); printf(")");
			break;
		default: perror("Unknown tag!");
	}
}

