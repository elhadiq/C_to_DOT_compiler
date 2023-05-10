%{
	#include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include<ctype.h>
    #include"lex.yy.c"
    
    void yyerror(const char *s);
    int yylex();
    int yywrap();
    extern int CompterN;
	extern int yycolumn;
%}
%token IDENTIFICATEUR CONSTANTE VOID INT FOR WHILE IF ELSE SWITCH CASE DEFAULT
%token BREAK RETURN PLUS MOINS MUL DIV LSHIFT RSHIFT BAND BOR LAND LOR LT GT 
%token GEQ LEQ EQ NEQ NOT EXTERN
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
%%
programme	: liste_fonctions {printf("RULE 1.1\n");}
;
liste_declarations	:	
		liste_declarations declaration {printf("RULE 2\n");}
	| declaration
;
liste_fonctions	:liste_fonctions fonction {printf("RULE3\n");}
| fonction {printf("RULE3.1\n");}
;
declaration	:	
		type liste_declarateurs ';' {printf("RULE4\n");}
;
liste_declarateurs	:	
		liste_declarateurs ',' declarateur { printf("RULE 5\n");}
	|	declarateur {printf("RULE 6\t %s\n",yytext);}
;
declarateur	:	
		IDENTIFICATEUR {printf("RULE 7 id=%s\n",yytext);}
	|	declarateur '[' CONSTANTE ']' {printf("RULE 8\n");}
;
fonction :type IDENTIFICATEUR '(' liste_parms ')' '{' liste_declarations  liste_instructions '}' {printf(" Function rule RULE 1\n");}
	|	EXTERN type IDENTIFICATEUR '(' liste_parms ')'  {printf(" Function rule RULE 2\n");}
;
type	:
VOID {printf("RULE 10 type=%s\n",yytext);}
|	INT {printf("RULE 11 type=%s \n",yytext);}
;
liste_parms	:parm 
| liste_parms ',' parm  {printf("RULE 12 type=%s\n",yytext);}

	|
;
parm	:	
		INT IDENTIFICATEUR  {printf("RULE 13 type=%s\n",yytext);}
;
liste_instructions :	
		liste_instructions instruction {printf("RULE 14 type=%s\n",yytext);}
	|
;
instruction	:	
		iteration {printf("RULE 15 type=%s\n",yytext);}
	|	selection {printf("RULE 16 type=%s\n",yytext);}
	|	saut {printf("RULE 17 type=%s\n",yytext);}
	|	affectation ';'  {printf("RULE 18 type=%s\n",yytext);}
	|	bloc {printf("RULE 19 type=%s\n",yytext);}
	|	appel {printf("RULE 20 type=%s\n",yytext);}
;
iteration	:	
		FOR '(' affectation ';' condition ';' affectation ')' instruction
	|	WHILE '(' condition ')' instruction
;
selection	:	
		IF '(' condition ')' instruction %prec THEN
	|	IF '(' condition ')' instruction ELSE instruction
	|	SWITCH '(' expression ')' instruction
	|	CASE CONSTANTE ':' instruction
	|	DEFAULT ':' instruction
;
saut	:	
		BREAK ';'
	|	RETURN ';'
	|	RETURN expression ';'
;
affectation	:	
		variable '=' expression
;
bloc	:	
		'{' liste_declarations liste_instructions '}'
;
appel	:	
		IDENTIFICATEUR '(' liste_expressions ')' ';'
;
variable	:	
		IDENTIFICATEUR
	|	variable '[' expression ']'
;
expression	:	
		'(' expression ')'
	|	expression binary_op expression %prec OP
	|	MOINS expression
	|	CONSTANTE
	|	variable
	|	IDENTIFICATEUR '(' liste_expressions ')'
;
liste_expressions	:	
		liste_expressions ',' expression
	|
;
condition	:	
		NOT '(' condition ')'
	|	condition binary_rel condition %prec REL
	|	'(' condition ')'
	|	expression binary_comp expression
;
binary_op	:	
		PLUS
	|       MOINS
	|	MUL
	|	DIV
	|       LSHIFT
	|       RSHIFT
	|	BAND
	|	BOR
;
binary_rel	:	
		LAND
	|	LOR
;
binary_comp	:	
		LT
	|	GT
	|	GEQ
	|	LEQ
	|	EQ
	|	NEQ
;
%%
int main() {
	printf("\t\tL'ANALYSE LEXICAL\n");
	int yylex();
	printf("\t\tL'ANALYSE SYNTAXIQUE\n");
    yyparse();
}
void yyerror(const char *msg) {
    fprintf(stderr, "Syntax error: %s\n", msg);
    fprintf(stderr, "Last token read was '%s'\n", yytext);
    fprintf(stderr, "Error occurred at line %d\n", yylineno-1);
    fprintf(stderr, "The input was: %.*s\n", yyleng, yytext);
}
