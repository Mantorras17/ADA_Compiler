#ifndef __code_h__
#define __code_h__

#include "ast.h"
#include "hashTable.h"

typedef enum ir_atom_tag { IR_INT, IR_VAR} IR_ATOM_TAG;
struct _Instr {
	enum { IR_ATTR, IR_OP_ATTR, IR_JUMP, 
		IR_BRANCH, IR_LABEL, IR_PRINT_INT, 
		IR_READ_INT, IR_PRINT_STRING, IR_READ_STRING,
		DATA_ALLOC_SPACE, DATA_ALLOC_STR
	} tag;
	union {
		struct {
			char *var1;
			IR_ATOM_TAG atom_tag;
			union {
				int num;
				char *var2;
			} atom;
		} attr;
		struct {
			char *var1;
			AST_ExprOp binop;
			char *var2;
			IR_ATOM_TAG atom_tag_right;
			union {
				int num;
				char *var3;
			} atom_right;
		} op_attr;
		struct {
			char *label;
		} jump;
		struct {
			char *var1;
			AST_BexprOp relop;
			IR_ATOM_TAG atom_tag;
			union {
				int num;
				char *var2;
			} atom;
			char *label_true;
			char *label_false;
		} branch;
		struct {
			char *label;
		} label_start;
		struct {
			IR_ATOM_TAG atom_tag;
			union {
				char *var1;
				int num;
			} atom;
		} print_int;
		struct {
			char *var1;
		} read_int;
		struct {
			char *var1;
		} print_string;
		struct {
			char *var1, *var2;
		} read_string;
		struct {
			char *sl;
			int nbytes;
		} data_alloc_space;
		struct {
			char *sl;
			char *str;
		} data_alloc_str;
	} type;
};
typedef struct _Instr *Instr; 

struct _InstrList {
	Instr instr;
	struct _InstrList *next_instr;
};
typedef struct _InstrList *InstrList;

Instr mk_instr_attr_num(char*,int);
Instr mk_instr_attr_var(char*,char*);

Instr mk_instr_op_attr_var_int(char*,AST_ExprOp,char*,int);
Instr mk_instr_op_attr_var_var(char*,AST_ExprOp,char*,char*);

Instr mk_instr_jump(char*);

Instr mk_branch_atom_int(char*,AST_BexprOp,int,char*,char*);
Instr mk_branch_atom_var(char*,AST_BexprOp,char*,char*,char*);

Instr mk_label(char*);

Instr mk_print_int_num(int);
Instr mk_print_int_var(char*);
Instr mk_read_int(char*);
Instr mk_print_string(char*);
Instr mk_read_string(char*,char*);

Instr mk_data_alloc_space(char*,int);
Instr mk_data_alloc_str(char*,char*);

InstrList mk_instr_list(Instr);

Instr getFirst(InstrList);
InstrList nextInstrs(InstrList);
InstrList append(InstrList,InstrList);

void printInstr(Instr);
void printListInstr(InstrList);

char* new_temp(void);
char* new_label(void);
char* new_str_label(void);
void pop_temp(int);

InstrList compileExpr(Hash_table,Expr,char*);
InstrList compileBool(Hash_table,Bexpr,char*,char*);
InstrList compileStr(Hash_table,Str_Expr);
InstrList compileStm(Hash_table,Stm);

#endif
