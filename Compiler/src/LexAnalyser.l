D                       [0-9]
L                       [a-zA-Z_]
H                       [a-fA-F0-9]
E                       [Ee][+-]?{D}+
FS                      (f|F|l|L)
IS                      (u|U|l|L)*
%{
    #include "y.tab.h"
    int CompterN=0;
    int yycolumn = 0; // declare and initialize yycolumn

    
    
    /*
%token     MUL  LSHIFT RSHIFT BAND BOR     
%token     NOT
%left PLUS MOINS
%left MUL DIV
%left LSHIFT RSHIFT
%left BOR BAND
%left LAND LOR
%nonassoc THEN
%nonassoc ELSE
%left OP
%left REL
%start programme
%%*/

%}
%option yylineno
%option 

alpha [a-zA-Z]
digit [0-9]
unary "++"|"--"

%%
"extern"                    { return EXTERN; }
"int"                       { return INT; }
"void"                      { return VOID; }
"return"                    { return RETURN; }
"for"	                    { return FOR; }
"if"	                    { return IF; }
"else"	                    { return ELSE; }
"then"	                    { return THEN; }
"break"                 { return BREAK; }
"case"                  { return CASE; }
"const"                 { return CONSTANTE; }
"default"               { return DEFAULT; }
"switch"                { return SWITCH;}
"while"                 { return WHILE;}
"<="                        { return LEQ; }
">="                        { return GEQ; }
"=="                        { return EQ; }
"!="                        { return NEQ; }
">"	                        { return GT; }
"<"	                        { return LT; }
"&&"	                    { return LAND; }
"||"	                    { return LOR; }
"+"                         { return PLUS; }
"-"                         { return MOINS; }
"/"                         { return DIV; }
{alpha}({alpha}|{digit})*   { return IDENTIFICATEUR; }
\/\/.*                      { ; }
\/\*(.*\n)*.*\*\/           { ; } 
[ \t]*                      { ; }
\n                        { yylineno++;  yycolumn = 0;}
.               { yycolumn++; }
%%

int yywrap() {
    return 1;
}
