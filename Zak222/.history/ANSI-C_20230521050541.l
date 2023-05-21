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
"break"                 { return BREAK;}
"case"                  { return CASE;}
"default"               { return DEFAULT;}
"else"                  { return ELSE;}
"extern"                { return EXTERN;}
"for"                   { return FOR;}
"if"                    { return IF; }
"int"                   { return INT ;}
"return"                {return RETURN; }
"switch"                { return SWITCH; }
"void"                  {return VOID; }
"while"                 { return WHILE; }
"-"                         { return MOINS; }
"+"                         { return PLUS; }
"*"                         { return MUL; }
"/"                         { return DIV; }
{digit}+                {return CONSTANTE; }

{alpha}({alpha}|{digit})*   { return IDENTIFICATEUR ; }

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
"<"                    { return LT; }
">="                    { return GEQ; }

">"                    { return GT; }
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

