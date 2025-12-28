#ifndef __typeChecker_h__
#define __typeChecker_h__

AST_Type checkExpr(Hash_table,Expr);
unsigned checkBepr(Hash_table,Bexpr);
unsigned checkStrExpr(Hash_table,Str_Expr);
unsigned checkStm(Hash_table,Stm);

#endif
