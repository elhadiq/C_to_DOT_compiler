D                       [0-9]
L                       [a-zA-Z_]
H                       [a-fA-F0-9]
E                       [Ee][+-]?{D}+
FS                      (f|F|l|L)
IS                      (u|U|l|L)*

%{
#include <stdio.h>
#include "y.tab.h"

/* Ne g�re pas les commentaires. A rajouter */
/* Supprimer les lignes dont vous n'avez pas besoin. */
/*
%token IDENTIFICATEUR CONSTANTE VOID INT FOR WHILE IF ELSE SWITCH CASE DEFAULT
%token BREAK RETURN PLUS MOINS MUL DIV LSHIFT RSHIFT BAND BOR LAND LOR LT GT EXTERN


%left BOR BAND

%nonassoc THEN
%nonassoc ELSE
%left OP
%left REL
%start programme
*/
%}
%option yylineno
alpha [a-zA-Z]
digit [0-9]
unary "++"|"--"
%%
"break"                 { return BREAK;}
"case"                  { return CASE;}
"default"               { return DEFAULT;}
"else"                  { return ELSE;}
"extern"                { return EXTERN;}
"for"                   { return FOR;}
"if"                    { return IF; }
"int"                   { return INT ;}
"return"                {return RETURN; }
"switch"                { /* A completer */ }
"typedef"               { /* A completer */ }
"union"                 { /* A completer */ }
"unsigned"              { /* A completer */ }
"void"                  {return VOID; }
"volatile"              { /* A completer */ }
"while"                 { /* A completer */ }
"-"                         { return MOINS; }
"+"                         { return PLUS; }
"*"                         { return MUL; }
"/"                         { return DIV; }
{digit}+                {return CONSTANTE; }

{alpha}({alpha}|{digit})*   { return IDENTIFICATEUR ; }
{L}({L}|{D})*           { /* A completer */ }

0[xX]{H}+{IS}?          { /* A completer */ }
0{D}+{IS}?              { /* A completer */ }
{D}+{IS}?               { /* A completer */ }
L?'(\\.|[^\\'])+'       { /* A completer */ }

{D}+{E}{FS}?            { /* A completer */ }
{D}*"."{D}+({E})?{FS}?  { /* A completer */ }
{D}+"."{D}*({E})?{FS}?  { /* A completer */ }

L?\"(\\.|[^\\"])*\"     { /* A completer */ }

"..."                   { /* A completer */ }
">>="                   { /* A completer */ }
"<<="                   { /* A completer */ }
"+="                    { /* A completer */ }
"-="                    { /* A completer */ }
"*="                    { /* A completer */ }
"/="                    { /* A completer */ }
"%="                    { /* A completer */ }
"&="                    { return LAND;}
"^="                    { /* A completer */ }
"|="                    { /* A completer */ }
">>"                    { return RSHIFT; }
"<<"                    { return LSHIFT;}
"++"                    { /* A completer */ }
"--"                    { /* A completer */ }
"->"                    { /* A completer */ }
"&&"                    { /* A completer */ }
"||"                    {return LOR;}
"<="                    { return LEQ; }
">="                    { return GEQ; }
"=="                    {return EQ; }
"!" {return NOT;}
"!="                    { return NEQ;}

[ \t\v\n\f]             { /* A completer */ }

\/\/.*                      { ; }
\/\*(.*\n)*.*\*\/           { ; } 
[ \t]*                      { ; }
[\n]                        { ; }
.                       { return yytext[0]; }
%%

