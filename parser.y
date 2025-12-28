%token
  TK_WITH
  TK_USE
  TK_ADA_TEXT_IO
  TK_ADA_IO_INT
  TK_PROCEDURE
  TK_IS
  TK_BEGIN
  TK_WHILE
  TK_LOOP
  TK_END
  TK_IF
  TK_THEN
  TK_ELSE
  TK_ELSE_IF
  TK_PUT_LINE
  TK_GET_LINE
  TK_GET
  TK_PUT
  TK_ID
  TK_FLOAT
  TK_INT
  TK_STRING
  TK_ASSIGN
  TK_RPAREN
  TK_LPAREN
  TK_AMP
  TK_PLUS
  TK_MINUS
  TK_MULT
  TK_DIV
  TK_AND
  TK_OR
  TK_XOR
  TK_TRUE
  TK_FALSE
  TK_NOT
  TK_TYPE_FLOAT
  TK_TYPE_INTEGER
  TK_TYPE_STRING
  TK_IMAGE
  TK_NOT_EQUAL
  TK_EQUAL
  TK_LESS
  TK_E_LESS
  TK_GREAT
  TK_E_GREAT
  TK_SEMICOLON
  TK_COLON
  TK_COMMA
  TK_DOT

%left TK_SEMICOLON
%left TK_AMP
%left TK_NOT
%left TK_XOR
%left TK_OR
%left TK_AND
%nonassoc TK_NOT_EQUAL TK_EQUAL TK_LESS TK_E_LESS TK_GREAT TK_E_GREAT
%left TK_PLUS TK_MINUS
%left TK_MULT TK_DIV


%start program;


%union {
  int intValue;
  double floatValue;
  char* stringValue;
  Expr exprValue;
  Str_Expr strValue;
  Bexpr bexprValue;
  Stm stmValue;
}

%type <intValue> TK_INT
%type <floatValue> TK_FLOAT
%type <exprValue> expr
%type <strValue> image_expr
%type <bexprValue> bexpr
%type <stmValue> stm
%type <stmValue> decl decls decls_opt
%type <stmValue> else_stm
%type <exprValue> opt_init
%type <stringValue> TK_ID
%type <stringValue> TK_STRING
%type <strValue> str_expr


%code requires {
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern char* yytext;
extern int yyline;
extern FILE* yyin;
extern void yyerror(const char* msg);
extern Stm root;
}


%%
program : 
    TK_WITH TK_ADA_TEXT_IO TK_SEMICOLON TK_USE TK_ADA_TEXT_IO TK_SEMICOLON TK_WITH TK_ADA_IO_INT TK_SEMICOLON TK_USE TK_ADA_IO_INT TK_SEMICOLON TK_PROCEDURE TK_ID TK_IS
    decls_opt
    TK_BEGIN stm TK_SEMICOLON TK_END TK_ID TK_SEMICOLON 
    { 
      if ($14 && strcmp($14,$21)!=0) {
        yyerror("END identifier does not match PROCEDURE name");
      }
      root = $16 ? mk_compound($16, $18) : $18;
    }
    ;

decls_opt :       { $$ = NULL; }
          | decls { $$ = $1; }
          ;

decls : decl        { $$ = $1; }
      | decls decl  { $$ = mk_compound($1, $2); }
      ;

decl : TK_ID TK_COLON TK_TYPE_INTEGER opt_init TK_SEMICOLON                                         { $$ = mk_declaration($1,AST_TYPE_INT,$4); }
     | TK_ID TK_COLON TK_TYPE_FLOAT opt_init TK_SEMICOLON                                           { $$ = mk_declaration($1,AST_TYPE_FLOAT,$4); }
     | TK_ID TK_COLON TK_TYPE_STRING TK_ASSIGN TK_STRING TK_SEMICOLON                               { $$ = mk_declaration_string($1,$5); }
     | TK_ID TK_COLON TK_TYPE_STRING TK_ASSIGN TK_GET_LINE TK_SEMICOLON                             { $$ = mk_declaration_get_line_string($1); }
     | TK_ID TK_COLON TK_TYPE_STRING TK_LPAREN TK_INT TK_DOT TK_DOT TK_INT TK_RPAREN TK_SEMICOLON   { $$ = mk_declaration_buf_string($1,$5,$8); }
     ;

opt_init :             { $$ = NULL; }
         | TK_ASSIGN expr { $$ = $2; }
	       ;

stm : TK_ID TK_ASSIGN expr                                       { $$ = mk_assign($1,$3); }
    | TK_WHILE bexpr TK_LOOP stm TK_SEMICOLON TK_END TK_LOOP     { $$ = mk_while($2,$4); }
    | TK_IF bexpr TK_THEN stm TK_SEMICOLON else_stm TK_END TK_IF { $$ = mk_branch($2,$4,$6); }
    | TK_PUT_LINE TK_LPAREN str_expr TK_RPAREN                   { $$ = mk_put_line($3); }
    | TK_PUT_LINE TK_LPAREN TK_RPAREN                            { $$ = mk_put_line(NULL); }
    | TK_GET_LINE TK_LPAREN TK_ID TK_COMMA TK_ID TK_RPAREN       { $$ = mk_get_line($3,$5); }
    | TK_GET TK_LPAREN TK_ID TK_RPAREN                           { $$ = mk_get($3); }
    | TK_PUT TK_LPAREN expr TK_RPAREN                            { $$ = mk_put($3); }
    | stm TK_SEMICOLON stm                                       { $$ = mk_compound($1,$3); }
    ;

else_stm :	                                         { $$ = NULL; }
	       | TK_ELSE stm TK_SEMICOLON                        { $$ = $2; }
	       | TK_ELSE_IF bexpr TK_THEN stm TK_SEMICOLON else_stm { $$ = mk_branch($2,$4,$6); }
	       ;

expr : TK_INT                { $$ = mk_int($1); }
     | TK_FLOAT              { $$ = mk_float($1); }
     | TK_ID                 { $$ = mk_ident($1); }
     | expr TK_PLUS expr     { $$ = mk_op(AST_PLUS, $1, $3); }
     | expr TK_MINUS expr    { $$ = mk_op(AST_MINUS, $1, $3); }
     | expr TK_MULT expr     { $$ = mk_op(AST_MULT, $1, $3); }
     | expr TK_DIV expr      { $$ = mk_op(AST_DIV, $1, $3); }
     | TK_LPAREN expr TK_RPAREN { $$ = $2; }
     ;

str_expr : TK_STRING                      { $$ = mk_string($1); }
	       | TK_ID                    { $$ = mk_ident_string($1); }
	       | image_expr               { $$ = $1; }
	       | str_expr TK_AMP str_expr { $$ = mk_concat($1,$3); };
	       ;

image_expr : TK_TYPE_FLOAT TK_IMAGE TK_LPAREN expr TK_RPAREN   { $$ = mk_image(AST_TYPE_FLOAT, $4); }
           | TK_TYPE_INTEGER TK_IMAGE TK_LPAREN expr TK_RPAREN { $$ = mk_image(AST_TYPE_INT,   $4); }
           ;

bexpr : TK_TRUE                   { $$ = mk_bool(AST_TRUE); }
      | TK_FALSE                  { $$ = mk_bool(AST_FALSE); }
      | bexpr TK_AND bexpr        { $$ = mk_compound_bbinop(AST_AND,$1,$3); }
      | bexpr TK_OR bexpr         { $$ = mk_compound_bbinop(AST_OR,$1,$3); }
      | bexpr TK_XOR bexpr        { $$ = mk_compound_bbinop(AST_XOR,$1,$3); }
      | TK_NOT bexpr              { $$ = mk_not_boolean($2); }
      | expr TK_NOT_EQUAL expr    { $$ = mk_bbinop(AST_NOT_EQUAL,$1,$3); }
      | expr TK_EQUAL expr        { $$ = mk_bbinop(AST_EQUAL,$1,$3); }
      | expr TK_LESS expr         { $$ = mk_bbinop(AST_LESS,$1,$3); }
      | expr TK_E_LESS expr       { $$ = mk_bbinop(AST_E_LESS,$1,$3); }
      | expr TK_GREAT expr        { $$ = mk_bbinop(AST_GREAT,$1,$3); }
      | expr TK_E_GREAT expr      { $$ = mk_bbinop(AST_E_GREAT,$1,$3); }
      | TK_LPAREN bexpr TK_RPAREN { $$ = $2; }
      ;



%%
Stm root = NULL;
void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
