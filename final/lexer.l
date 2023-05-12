%{
    #include "y.tab.h"
    int CompterN=0;
%}
%option yylineno

alpha [a-zA-Z]
digit [0-9]
unary "++"|"--"

%%
"extern"                    { strcpy(yylval.nd_obj.nom,(yytext)); return EXTERN; }
"int"                       { strcpy(yylval.nd_obj.nom,(yytext)); return INT; }
"void"                      { strcpy(yylval.nd_obj.nom,(yytext)); return VOID; }
"return"                    { strcpy(yylval.nd_obj.nom,(yytext)); return RETURN; }
"for"	                    { strcpy(yylval.nd_obj.nom,(yytext)); return FOR; }
"while"	                    { strcpy(yylval.nd_obj.nom,(yytext)); return WHILE; }
"if"	                    { strcpy(yylval.nd_obj.nom,(yytext)); return IF; }
"else"	                    { strcpy(yylval.nd_obj.nom,(yytext)); return ELSE; }
"switch"                    { strcpy(yylval.nd_obj.nom,(yytext)); return SWITCH; }
"case"	                    { strcpy(yylval.nd_obj.nom,(yytext)); return CASE; }
"default"                   { strcpy(yylval.nd_obj.nom,(yytext)); return DEFAULT; }
"break"	                    { strcpy(yylval.nd_obj.nom,(yytext)); return BREAK; }

^"#include"[ ]*<.+\.h>      { strcpy(yylval.nd_obj.nom,(yytext)); return INCLUDE; }
"true"                      { strcpy(yylval.nd_obj.nom,(yytext)); return TRUE; }
"false"                     { strcpy(yylval.nd_obj.nom,(yytext)); return FALSE; }
[-]?{digit}+                { strcpy(yylval.nd_obj.nom,(yytext)); printf("une constante %s",yytext); return CONSTANTE; }
[-]?{digit}+\.{digit}{1,6}  { strcpy(yylval.nd_obj.nom,(yytext)); return FLOAT_NUM; }
{alpha}({alpha}|{digit})*   { strcpy(yylval.nd_obj.nom,(yytext)); return IDENTIFICATEUR ; }
{unary}                     { strcpy(yylval.nd_obj.nom,(yytext)); return UNARY; }
"<="                        { strcpy(yylval.nd_obj.nom,(yytext)); return LEQ; }
">="                        { strcpy(yylval.nd_obj.nom,(yytext)); return GEQ; }
"=="                        { strcpy(yylval.nd_obj.nom,(yytext)); return EQ; }
"!="                        { strcpy(yylval.nd_obj.nom,(yytext)); return NEQ; }
"!"                        { strcpy(yylval.nd_obj.nom,(yytext)); return NOT; }
">"	                        { strcpy(yylval.nd_obj.nom,(yytext)); return GT; }
"<"	                        { strcpy(yylval.nd_obj.nom,(yytext)); return LT; }
"&&"	                    { strcpy(yylval.nd_obj.nom,(yytext)); return LAND; }
"||"	                    { strcpy(yylval.nd_obj.nom,(yytext)); return LOR; }
"+"                         { strcpy(yylval.nd_obj.nom,(yytext)); return PLUS; }
"-"                         { strcpy(yylval.nd_obj.nom,(yytext)); return MOINS; }
"*"                         { strcpy(yylval.nd_obj.nom,(yytext)); return MUL; }
"/"                         { strcpy(yylval.nd_obj.nom,(yytext)); return DIV; }
\/\/.*                      { ; }
\/\*(.*\n)*.*\*\/           { ; } 
[ \t]*                      { ; }
[\n]                        { CompterN++; }
.	                        { return *yytext; }
["].*["]                    { strcpy(yylval.nd_obj.nom,(yytext)); return STR; }
['].[']                     { strcpy(yylval.nd_obj.nom,(yytext)); return CHARACTER; }

%%

int yywrap() {
    return 1;
}