%{
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

static char* strip_underscores(const char* s) {
   size_t n = strlen(s), j = 0;
   char *out = (char*)malloc(n+1);
   for (size_t i=0; i<n; ++i) if (s[i] != '_') out[j++] = s[i];
   out[j] = '\0';
   return out;
}

int yyline = 1;

%}

%option noyywrap
%option noinput nounput

%%
[ \t\r]+   { }
"--".*\n   { yyline++; }
\n         { yyline++; }

"with"        { return TK_WITH; }
"use"         { return TK_USE; }
"Ada.Text_IO" { return TK_ADA_TEXT_IO; }
"Ada.Integer_Text_IO" { return TK_ADA_IO_INT; }
"procedure"   { return TK_PROCEDURE; }
"is"          { return TK_IS; }
"begin"       { return TK_BEGIN; }

"while" { return TK_WHILE; }
"loop"  { return TK_LOOP; }
"end"   { return TK_END; }
"if"    { return TK_IF; }
"then"  { return TK_THEN; }
"else"  { return TK_ELSE; }
"elsif" { return TK_ELSE_IF; }

"Put_Line" { return TK_PUT_LINE; }
"Get_Line" { return TK_GET_LINE; }
"Get"      { return TK_GET; }
"Put"      { return TK_PUT; }

"True"  { return TK_TRUE; }
"False" { return TK_FALSE; }
"and"   { return TK_AND; }
"or"    { return TK_OR; }
"xor"   { return TK_XOR; }
"not"   { return TK_NOT; }

"Float"   { return TK_TYPE_FLOAT; }
"Integer" { return TK_TYPE_INTEGER; }
"String"  { return TK_TYPE_STRING; }
"'Image"  { return TK_IMAGE; }

[A-Za-z](((_?[A-Za-z0-9]+_?)*|(_?[A-Za-z0-9]*))[A-Za-z0-9])? {
   yylval.stringValue = strdup(yytext);
   return TK_ID;
}
[+-]?[0-9]+(_[0-9]+)*\.[0-9]+(_[0-9]+)*([eE][+-]?[0-9]+(_[0-9]+)*)? {
   char *clean = strip_underscores(yytext);
   yylval.floatValue = strtod(clean, NULL);
   free(clean);
   return TK_FLOAT;
}
[+-]?[0-9]+(_[0-9]+)*[eE][+-]?[0-9]+(_[0-9]+)* {
   char *clean = strip_underscores(yytext);
   yylval.floatValue = strtod(clean, NULL);
   free(clean);
   return TK_FLOAT;
}
[+-]?[0-9](_?[0-9])* {
   char *clean = strip_underscores(yytext);
   yylval.intValue = atoi(clean);
   free(clean);
   return TK_INT;
}

\"([^\\\"]|\\.)*\" { 
   yylval.stringValue = strdup(yytext);
   return TK_STRING; 
}

":=" { return TK_ASSIGN; }
":"  { return TK_COLON; }
"("  { return TK_LPAREN; }
")"  { return TK_RPAREN; }
"&"  { return TK_AMP; }
"+"  { return TK_PLUS; }
"-"  { return TK_MINUS; }
"*"  { return TK_MULT; }
"/"  { return TK_DIV; }
"/=" { return TK_NOT_EQUAL; }
"="  { return TK_EQUAL; }
"<"  { return TK_LESS; }
"<=" { return TK_E_LESS; }
">"  { return TK_GREAT; } 
">=" { return TK_E_GREAT; }
";"  { return TK_SEMICOLON; }
","  { return TK_COMMA; }
"."  { return TK_DOT; }
.    { yyerror("unexpected character"); }

%%
