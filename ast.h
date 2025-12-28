#ifndef __ast_h__
#define __ast_h__

typedef enum ast_type { AST_TYPE_STRING, AST_TYPE_FLOAT, AST_TYPE_INT, AST_NO_TYPE } AST_Type;

struct _stm {
	enum { 
		AST_COMPOUND_STM, AST_ASSIGN_STM, AST_WHILE_STM,
		AST_BRANCH_STM, AST_PUT_LINE_STM, AST_GET_LINE_STM,
		AST_DECL_STM, AST_STR_DECL_STM, AST_GET_STM, AST_PUT_STM
	} tag;
	union {
		struct {
			struct _stm *fst, *snd;
		} compound;
		struct {
			char *ident;
			struct _expr *expr;
		} assign;
		struct {
			struct _bexpr *bexpr;
			struct _stm *stm;
		} while_stm;
		struct {
			struct _bexpr *bexpr;
			struct _stm *stm1, *stm2;
		} branch;
		struct {
			char *ident1, *ident2;
		} get_line;
		struct {
			char *ident;
		} get;
		struct _str_expr *str_expr; // put line
		struct {
			struct _expr *expr;
		} put;
		struct {
			char *ident;
			AST_Type type;
			struct _expr *init;
		} decl;
		struct {
			char *ident;
			enum { AST_STR_EXPR_DECL, AST_GET_LINE_DECL, AST_BUF_DECL } type_decl;
			union {
				char *s;
				struct {
					int left, right;
				} buf;
			} str_attr_decl;
		} str_decl;
	} attr;
};
typedef struct _stm *Stm;



typedef enum ast_expr_op { AST_PLUS, AST_MINUS, AST_MULT, AST_DIV } AST_ExprOp;

struct _expr {
	enum { AST_EXPR_INT, AST_EXPR_FLOAT, AST_EXPR_ID, AST_EXPR_OP } tag;
	union {
		int val;
		double fval;
		char *id;
		struct {
			AST_ExprOp op;
			struct _expr *left, *right;
		} binop;
	} attr;
};
typedef struct _expr *Expr;



struct _str_expr {
	enum { AST_STR_STRING, AST_STR_ID, AST_STR_IMAGE, AST_STR_CONCAT} tag;
	union {
		char *sval;
		char *id;
		struct {
			AST_Type type;
			struct _expr *arg;
		} image;
		struct {
			struct _str_expr *left, *right;
		} concat;
	} attr;
};
typedef struct _str_expr *Str_Expr;



typedef enum ast_b_lit { AST_TRUE, AST_FALSE } AST_BLit;
typedef enum ast_c_bexpr_op { AST_AND, AST_OR, AST_XOR }  AST_C_BexprOp;
typedef enum ast_bexpr_op { AST_NOT_EQUAL, AST_EQUAL, AST_LESS, AST_E_LESS, AST_GREAT, AST_E_GREAT } AST_BexprOp;

struct _bexpr {
	enum {AST_BOP, AST_BCOMPOUND, AST_BNOT, AST_BVALUE} tag;
	union {
		struct {
			AST_BexprOp op;
			struct _expr *left, *right; 
		} bbinop;
		struct {
			AST_C_BexprOp op;
			struct _bexpr *left, *right;
		} compound;
		struct _bexpr *negate;
		AST_BLit value;
	} attr;
};
typedef struct _bexpr *Bexpr;


Stm mk_compound(Stm,Stm);
Stm mk_assign(char*,Expr);
Stm mk_while(Bexpr,Stm);
Stm mk_branch(Bexpr,Stm,Stm);
Stm mk_put_line(Str_Expr);
Stm mk_put(Expr);
Stm mk_declaration(char*,AST_Type,Expr);
Stm mk_declaration_string(char*,char*);
Stm mk_declaration_get_line_string(char*);
Stm mk_declaration_buf_string(char*,int,int);
Stm mk_get_line(char*,char*);
Stm mk_get(char*);

Expr mk_int(int);
Expr mk_float(double);
Expr mk_ident(char*);
Expr mk_op(AST_ExprOp,Expr,Expr);


Str_Expr mk_image(AST_Type, Expr);
Str_Expr mk_string(char*);
Str_Expr mk_ident_string(char*);
Str_Expr mk_concat(Str_Expr,Str_Expr);

Bexpr mk_bool(AST_BLit);
Bexpr mk_compound_bbinop(AST_C_BexprOp,Bexpr,Bexpr);
Bexpr mk_not_boolean(Bexpr);
Bexpr mk_bbinop(AST_BexprOp,Expr,Expr);

void ident(int);
void print_bexpr(Bexpr,int);
void print_expr(Expr,int);
void print_str_expr(Str_Expr,int);
void print_stm(Stm,int);

#endif
