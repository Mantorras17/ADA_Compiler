#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "hashTable.h"
#include "typeChecker.h"

AST_Type checkExpr(Hash_table t,Expr expr) {
	switch (expr->tag) {
		case AST_EXPR_INT:
			return AST_TYPE_INT;
			break;
		case AST_EXPR_FLOAT:
			return AST_TYPE_FLOAT;
			break;
		case AST_EXPR_ID:
			AST_Type *type_var = (AST_Type *)lookup(t,expr->attr.id);
			if (type_var == NULL) {
				printf("Variable %s was not declared\n", expr->attr.id);
				return AST_NO_TYPE;
			}
			return *type_var;
			break;
		case AST_EXPR_OP:
			AST_Type type_left = checkExpr(t,expr->attr.binop.left), type_right = checkExpr(t,expr->attr.binop.right);
			if (type_left == AST_NO_TYPE || type_right == AST_NO_TYPE) return AST_NO_TYPE;
			else if (type_left != type_right) {
				printf("Two sides of the operation do not have the same type\n");
				return AST_NO_TYPE;
			}
			return type_left;
			break;
	}
	return AST_NO_TYPE;
}

unsigned checkBexpr(Hash_table t,Bexpr bexpr) {
	switch (bexpr->tag) {
		case AST_BOP:
			AST_Type type_left = checkExpr(t,bexpr->attr.bbinop.left), type_right = checkExpr(t,bexpr->attr.bbinop.right);
			if (type_left == AST_NO_TYPE || type_right == AST_NO_TYPE) return 0;
			else if ( type_left == type_right)
				return 1;
			else {
				printf("Two sides of the operation do not have the same type");
				return 0;
			}
			break;
		case AST_BCOMPOUND:
			if (checkBexpr(t,bexpr->attr.compound.left) && checkBexpr(t,bexpr->attr.compound.right))
				return 1;
			else return 0;
			break;
		case AST_BNOT:
			if (checkBexpr(t,bexpr->attr.negate)) return 1;
			else return 0;
			break;
		case AST_BVALUE:
			if (bexpr->attr.value == AST_TRUE || bexpr->attr.value == AST_FALSE) 
				return 1;
			else return 0;
			break;
	}
	return 0;
}

unsigned checkStrExpr(Hash_table t,Str_Expr str) {
	switch (str->tag) {
		case AST_STR_STRING:
			return 1;
			break;
		case AST_STR_ID:
			AST_Type *type_var = (AST_Type *)lookup(t,str->attr.id);
			if (*type_var == AST_TYPE_STRING)
				return 1;
			else {
				printf("Variable not declared or it is not of type String\n");
				return 0;
			}
			break;
		case AST_STR_IMAGE:
			AST_Type type_expr = checkExpr(t,str->attr.image.arg);
			if (type_expr == str->attr.image.type)
				return 1;
			else 
				return 0;
			break;
		case AST_STR_CONCAT:
			if (checkStrExpr(t,str->attr.concat.left) && checkStrExpr(t,str->attr.concat.right))
				return 1;
			else return 0;
			break;
	}
	return 0;
}

unsigned checkStm(Hash_table t,Stm stm) {
	AST_Type *type_var;
	switch (stm->tag) {
		case AST_COMPOUND_STM:
			if (checkStm(t,stm->attr.compound.fst) && checkStm(t,stm->attr.compound.snd)) 
				return 1;
			else return 0;
			break;
		case AST_ASSIGN_STM:
			type_var = (AST_Type *)lookup(t,stm->attr.assign.ident);
			if (type_var == NULL) {
				printf("Variable %s undeclared\n", stm->attr.assign.ident);
				return 0;
			}
			if (checkExpr(t,stm->attr.assign.expr) == *type_var)
				return 1;
			else return 0;
			break;
		case AST_WHILE_STM:
			if (checkBexpr(t,stm->attr.while_stm.bexpr) && checkStm(t,stm->attr.while_stm.stm)) 
				return 1;
			else return 0;
			break;
		case AST_BRANCH_STM:
			if (checkStm(t,stm->attr.branch.stm1) && checkBexpr(t,stm->attr.branch.bexpr) && (stm->attr.branch.stm2 == NULL || checkStm(t,stm->attr.branch.stm2)))
				return 1;
			else return 0;
			break;
		case AST_PUT_LINE_STM:
			if (stm->attr.str_expr == NULL || checkStrExpr(t,stm->attr.str_expr)) 
				return 1;
			else return 0;
			break;
		case AST_GET_LINE_STM:
			AST_Type *type_var1 = (AST_Type *)lookup(t,stm->attr.get_line.ident1), *type_var2 = (AST_Type *)lookup(t,stm->attr.get_line.ident2);
			if (type_var1 == NULL) {
				printf("Variable %s used undeclared\n", stm->attr.get_line.ident1);
				return 0;
			}
			if (type_var2 == NULL) {
				printf("Variable %s used undeclared\n", stm->attr.get_line.ident2);
				return 0;
			}
			if (*type_var1 == AST_TYPE_STRING && *type_var2 == AST_TYPE_INT) 
				return 1;
			else return 0;
			break;
		case AST_DECL_STM:
			type_var = malloc(sizeof(AST_Type));
			*type_var = stm->attr.decl.type;
			addEntry(t,stm->attr.decl.ident,type_var);
			if (stm->attr.decl.init != NULL) {
				if (stm->attr.decl.type == checkExpr(t,stm->attr.decl.init)) return 1;
				else return 0;
			}
			return 1;
			break;
		case AST_STR_DECL_STM:
			type_var = malloc(sizeof(AST_Type));
			*type_var = AST_TYPE_STRING;
			addEntry(t,stm->attr.str_decl.ident,type_var);
			return 1;
			break;
		case AST_GET_STM:
			type_var = (AST_Type *)lookup(t,stm->attr.assign.ident);
			if (type_var == NULL) {
				printf("Variable %s undeclared\n", stm->attr.assign.ident);
				return 0;
			}
			if (*type_var == AST_TYPE_INT)
				return 1;
			else return 0;
			break;
		case AST_PUT_STM:
			if (checkExpr(t,stm->attr.put.expr) == AST_TYPE_INT) 
				return 1;
			else return 0;
			break;
	}
	return 0;
}
