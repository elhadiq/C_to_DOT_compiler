D                       [0-9]
L                       [a-zA-Z_]
H                       [a-fA-F0-9]
E                       [Ee][+-]?{D}+
FS                      (f|F|l|L)
IS                      (u|U|l|L)*

%{
#include <stdio.h>
#include "y.tab.h"
%}
%option yylineno
alpha [a-zA-Z]
digit [0-9]
unary "++"|"--"
%%
"break"                 { strcpy(yylval.nd_obj.nom,(yytext)); return BREAK;}
"case"                  { strcpy(yylval.nd_obj.nom,(yytext)); return CASE;}
"default"               { strcpy(yylval.nd_obj.nom,(yytext)); return DEFAULT;}
"else"                  { strcpy(yylval.nd_obj.nom,(yytext)); return ELSE;}
"extern"                { strcpy(yylval.nd_obj.nom,(yytext)); return EXTERN;}
"for"                   { strcpy(yylval.nd_obj.nom,(yytext)); return FOR;}
"if"                    { strcpy(yylval.nd_obj.nom,(yytext)); return IF; }
"int"                   { strcpy(yylval.nd_obj.nom,(yytext)); return INT ;}
"return"                {strcpy(yylval.nd_obj.nom,(yytext)); return RETURN; }
"switch"                { strcpy(yylval.nd_obj.nom,(yytext)); return SWITCH; }
"void"                  {strcpy(yylval.nd_obj.nom,(yytext)); return VOID; }
"while"                 { strcpy(yylval.nd_obj.nom,(yytext)); return WHILE; }
"-"                         { strcpy(yylval.nd_obj.nom,(yytext)); return MOINS; }
"+"                         { strcpy(yylval.nd_obj.nom,(yytext)); return PLUS; }
"*"                         { strcpy(yylval.nd_obj.nom,(yytext)); return MUL; }
"/"                         { strcpy(yylval.nd_obj.nom,(yytext)); return DIV; }
{digit}+                {strcpy(yylval.nd_obj.nom,(yytext)); return CONSTANTE; }

{alpha}({alpha}|{digit})*   { strcpy(yylval.nd_obj.nom,(yytext)); return IDENTIFICATEUR ; }

"..."                   { /* A completer */ }
">>="                   { /* A completer */ }
"<<="                   { /* A completer */ }
"+="                    { /* A completer */ }
"-="                    { /* A completer */ }
"*="                    { /* A completer */ }
"/="                    { /* A completer */ }
"%="                    { /* A completer */ }
"&="                    { strcpy(yylval.nd_obj.nom,(yytext)); return LAND;}
"^="                    { /* A completer */ }
"|="                    { /* A completer */ }
">>"                    { strcpy(yylval.nd_obj.nom,(yytext)); return RSHIFT; }
"<<"                    { strcpy(yylval.nd_obj.nom,(yytext)); return LSHIFT;}
"++"                    { /* A completer */ }
"--"                    { /* A completer */ }
"->"                    { /* A completer */ }
"&&"                    { /* A completer */ }
"||"                    {strcpy(yylval.nd_obj.nom,(yytext)); return LOR;}
"<="                    { strcpy(yylval.nd_obj.nom,(yytext)); return LEQ; }
"<"                    { strcpy(yylval.nd_obj.nom,(yytext)); return LT; }
">="                    { strcpy(yylval.nd_obj.nom,(yytext)); return GEQ; }
">"                    { strcpy(yylval.nd_obj.nom,(yytext)); return GT; }
"=="                    {strcpy(yylval.nd_obj.nom,(yytext)); return EQ; }
"!"                     {strcpy(yylval.nd_obj.nom,(yytext)); return NOT;}
"!="                    { strcpy(yylval.nd_obj.nom,(yytext)); return NEQ;}
[ \t\v\n\f]             { /* A completer */ }

\/\/.*                      { ; }
\/\*(.*\n)*.*\*\/           { ; } 
[ \t]*                      { ; }
[\n]                        { ; }
.                       { strcpy(yylval.nd_obj.nom,(yytext)); return yytext[0]; }
%%

