%{
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include<ctype.h>
    #include"lex.yy.c"
    void yyerror(const char *s);
    int yylex();
    int yywrap();
    void ajouter(char);
    void inserer_type();
    int chercher(char *);
	void afficher_arbre(struct noeud*);
	void afficher_arbre_to_file(FILE* f,struct noeud*);
	void afficher_dans_lorder(struct noeud *);
	void affichage_prifixe_de_larbre_syntaxique(FILE* f,struct noeud *,int* j);
    void verefier_declaration(char *);
	void verefier_type_de_return(char *);
	int verefier_type(char *, char *);
	char *retrurner_type(char *);
	struct noeud* faire_noeud(struct noeud *gauche, struct noeud *droite, char *lexeme);
	struct noeud_lcrs* faire_noeud_lcrs(struct noeud_lcrs *left_child, struct noeud_lcrs *right_sibling, char *label,char *shape,char *style);
    void afficher_les_dependances_dot_lcrs(FILE* f,struct noeud_lcrs *tree);
	void afficher_les_dependances_dot(FILE* f,struct noeud *tree,int* j);
	void affichage_prifixe_de_larbre_syntaxique_dot_lcrs(FILE* f,struct noeud_lcrs *tree,int* j);
	void afficher_arbre_dot_lcrs(FILE* f,struct noeud_lcrs* tree);
	struct dataType {
        char * nom_id;
        char * type_data;
        char * type;
        int ligne_nombre;
	} table_de_symbols[40];

    int compter=0;
    int q;
	char type[10];
	char debug[100];
    extern int CompterN;
	struct noeud *head;
	struct noeud_lcrs *head_dot;
	int sem_errors=0;
	int DOT_index=0;
	int temp_var=0;
	int label=0;
	int is_for=0;
	char buff[300];
	char errors[10][100];
	char reserves[12][10] = {"extern", "int", "void", "for", "while", "if", "then","else", "switch", "case", "default", "break"};
	char code3v[50][100];

	struct noeud { 
		struct noeud *gauche; 
		struct noeud *droite; 
		char *lexeme; 
	};
	struct noeud_lcrs { 
		struct noeud_lcrs *left_child; 
		struct noeud_lcrs *right_sibling; 
		char *shape;
		char *label; 
		char *style;
		int inode;
	};

%}

%union { struct nom_variable { 
			char nom[100]; 
			struct noeud* nd;
			struct noeud_lcrs* nd_dot;
		} nd_obj;

		struct nom_variable2 { 
			char nom[100]; 
			struct noeud* nd;
			struct noeud_lcrs* nd_dot;
			char type[5];
		} nd_obj2; 

		struct nom_variable3 {
			char nom[100];
			struct noeud* nd;
			struct noeud_lcrs* nd_dot;
			char if_corps[5];
			char else_corps[5];
		} nd_obj3;
	} 
%token VOID 
%token <nd_obj> EXTERN INT CHAR FOR WHILE SWITCH CASE DEFAULT BREAK IF ELSE TRUE FALSE CONSTANTE IDENTIFICATEUR LEQ GEQ EQ NOT GT LT LAND LOR NEQ STR  PLUS MUL DIV MOINS UNARY INCLUDE RETURN 
%type <nd_obj> externe externs main liste_instructions liste_expressions returne appel datatype instruction1 arithmetic relop programme else instruction binary_op
%type <nd_obj2> init valeur expression variable
%type <nd_obj3> condition
%start programme
%%

programme: main '(' ')' '{' liste_instructions returne '}' { 
$1.nd = faire_noeud($5.nd, NULL, "main");
$$.nd = faire_noeud($1.nd, NULL, "programme");
head = $$.nd;

$5.nd_dot = faire_noeud_lcrs(NULL, NULL, "","","");
$$.nd_dot = $1.nd_dot;
head_dot=$$.nd_dot;
} 
| externs programme {
	$$.nd=$2.nd;
	head=$$.nd;
	$$.nd_dot=$2.nd_dot;
	head_dot=$$.nd_dot;
}
;

main: datatype IDENTIFICATEUR { ajouter('F'); } {sprintf(buff,"%s, %s",$2.nom,$1.nom);$$.nd_dot=faire_noeud_lcrs(NULL, NULL, buff,"invtrapezium","");}
;
externs: externs externe
|externe
;
externe: EXTERN datatype IDENTIFICATEUR { ajouter('F'); } '(' liste_parms ')' ';'
;

liste_parms	:liste_parms ',' parm
	|	parm
	| 
;
parm	:	
		INT { inserer_type(); } IDENTIFICATEUR { ajouter('V'); }
;
liste_declarations	:	
		liste_declarations declaration 
	|	declaration
;
liste_declarateurs	:{sprintf(debug,"1");} declarateur ':' liste_declarateurs 
	|	declarateur
;
declarateur	:{sprintf(debug,"2");}  IDENTIFICATEUR {ajouter('V');}
	|	declarateur '[' CONSTANTE {ajouter('C');}']'
;
declaration	:	{sprintf(debug,"list_declarateurs");} 
		datatype liste_declarateurs ';'
;
datatype: INT { inserer_type(); }
| VOID { inserer_type(); }
;
liste_instructions :	instruction liste_instructions   {$$.nd=faire_noeud($1.nd,$2.nd,"instructions");}
	| instruction
	|
;
instruction:
| FOR { ajouter('K'); is_for = 1; } '(' instruction1 ';' condition ';' instruction1 ')' '{' liste_instructions '}' { 
	struct noeud *temp = faire_noeud($6.nd, $8.nd, "CONDITION"); 
	struct noeud *temp2 = faire_noeud($4.nd, temp, "CONDITION"); 
	$$.nd = faire_noeud(temp2, $11.nd, $1.nom); 
	strcpy(code3v[DOT_index++], buff);
	sprintf(code3v[DOT_index++], "JUMP to %s\n", $6.if_corps);
	sprintf(code3v[DOT_index++], "\nLABEL %s:\n", $6.else_corps);
}
| IF { ajouter('K'); is_for = 0; } '(' condition ')' { sprintf(code3v[DOT_index++], "\nLABEL %s:\n", $4.if_corps); } '{' liste_instructions '}' { sprintf(code3v[DOT_index++], "\nLABEL %s:\n", $4.else_corps); } else { 
	struct noeud *iff = faire_noeud($4.nd, $8.nd, $1.nom); 
	$$.nd = faire_noeud(iff, $11.nd, "if-else"); 
	sprintf(code3v[DOT_index++], "GOTO next\n");
}
| instruction1 ';' { $$.nd = $1.nd; }
| liste_instructions liste_instructions { $$.nd = faire_noeud($1.nd, $2.nd, "instructions"); }
| appel {$$.nd=$1.nd;}

;
appel	:	
		IDENTIFICATEUR '(' liste_expressions ')' ';'{$1.nd=faire_noeud($3.nd,NULL,$1.nom); $$.nd=$1.nd;}
;
variable	:	
		IDENTIFICATEUR  {$$.nd=faire_noeud(NULL,NULL,$1.nom);}
	|	variable '[' expression ']'
;
expression	:	
		'(' expression ')' {$$.nd=$2.nd;}
	|	expression binary_op expression %prec OP {$$.nd=faire_noeud($1.nd,$3.nd,$2.nom);} 
	|	MOINS expression {$$.nd=$2.nd;}
	|	CONSTANTE { ajouter('C'); }{struct noeud* tmp=faire_noeud(NULL,NULL,$1.nom); $$.nd=tmp;}
	|	variable {$$.nd=$1.nd;}
	|	IDENTIFICATEUR '(' liste_expressions ')'
;
liste_expressions	:liste_expressions ',' expression {$$.nd=faire_noeud($1.nd,$3.nd,"expressions");}
	| expression {$$.nd=$1.nd;}
;
else: ELSE { ajouter('K'); } '{' liste_instructions '}' { $$.nd = faire_noeud(NULL, $4.nd, $1.nom); }
| { $$.nd = NULL; }
;
binary_op	:PLUS 
	|   MOINS
	|	MUL
	|	DIV
;
condition: valeur relop valeur { 
	$$.nd = faire_noeud($1.nd, $3.nd, $2.nom); 
	if(is_for) {
		sprintf($$.if_corps, "L%d", label++);
		sprintf(code3v[DOT_index++], "\nLABEL %s:\n", $$.if_corps);
		sprintf(code3v[DOT_index++], "\nif NOT (%s %s %s) GOTO L%d\n", $1.nom, $2.nom, $3.nom, label);
		sprintf($$.else_corps, "L%d", label++);
	} else {
		sprintf(code3v[DOT_index++], "\nif (%s %s %s) GOTO L%d else GOTO L%d\n", $1.nom, $2.nom, $3.nom, label, label+1);
		sprintf($$.if_corps, "L%d", label++);
		sprintf($$.else_corps, "L%d", label++);
	}
}
| TRUE { ajouter('K'); $$.nd = NULL; }
| FALSE { ajouter('K'); $$.nd = NULL; }
| { $$.nd = NULL; }
;

instruction1:{strcpy(debug,"ID1");} datatype IDENTIFICATEUR {ajouter('V');} ";"
| datatype IDENTIFICATEUR { ajouter('V'); } init { 
	$2.nd = faire_noeud(NULL, NULL, $2.nom); 
	int t = verefier_type($1.nom, $4.type); 
	if(t>0) { 
		if(t == 1) {
			struct noeud *temp = faire_noeud(NULL, $4.nd, "float_vers_int"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		} 
		else if(t == 2) { 
			struct noeud *temp = faire_noeud(NULL, $4.nd, "int_vers_float"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		} 
		else if(t == 3) { 
			struct noeud *temp = faire_noeud(NULL, $4.nd, "char_vers_int"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		} 
		else if(t == 4) { 
			struct noeud *temp = faire_noeud(NULL, $4.nd, "int_to_char"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		} 
		else if(t == 5) { 
			struct noeud *temp = faire_noeud(NULL, $4.nd, "char_to_float"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		} 
		else{
			struct noeud *temp = faire_noeud(NULL, $4.nd, "float_to_char"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		}
	} 
	else { 
		$$.nd = faire_noeud($2.nd, $4.nd, ":="); 
	} 
	sprintf(code3v[DOT_index++], "%s = %s\n", $2.nom, $4.nom);
}
| IDENTIFICATEUR { verefier_declaration($1.nom); } '=' expression {
	$1.nd = faire_noeud(NULL, NULL, $1.nom); 
	char *id_type = retrurner_type($1.nom); 
	if(strcmp(id_type, $4.type)) {
		if(!strcmp(id_type, "int")) {
			if(!strcmp($4.type, "float")){
				struct noeud *temp = faire_noeud(NULL, $4.nd, "float_vers_int");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
			else{
				struct noeud *temp = faire_noeud(NULL, $4.nd, "char_vers_int");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
			
		}
		else if(!strcmp(id_type, "float")) {
			if(!strcmp($4.type, "int")){
				struct noeud *temp = faire_noeud(NULL, $4.nd, "int_vers_float");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
			else{
				struct noeud *temp = faire_noeud(NULL, $4.nd, "char_to_float");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
			
		}
		else{
			if(!strcmp($4.type, "int")){
				struct noeud *temp = faire_noeud(NULL, $4.nd, "int_to_char");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
			else{
				struct noeud *temp = faire_noeud(NULL, $4.nd, "float_to_char");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
		}
	}
	else {
		$$.nd = faire_noeud($1.nd, $4.nd, ":="); 
	}
	sprintf(code3v[DOT_index++], "%s = %s\n", $1.nom, $4.nom);
}
| IDENTIFICATEUR { verefier_declaration($1.nom); } relop expression { $1.nd = faire_noeud(NULL, NULL, $1.nom); $$.nd = faire_noeud($1.nd, $4.nd, $3.nom); }
| IDENTIFICATEUR { verefier_declaration($1.nom); } UNARY { 
	$1.nd = faire_noeud(NULL, NULL, $1.nom); 
	$3.nd = faire_noeud(NULL, NULL, $3.nom); 
	$$.nd = faire_noeud($1.nd, $3.nd, "ITERATOR");  
	if(!strcmp($3.nom, "++")) {
		sprintf(buff, "t%d = %s + 1\n%s = t%d\n", temp_var, $1.nom, $1.nom, temp_var++);
	}
	else {
		sprintf(buff, "t%d = %s + 1\n%s = t%d\n", temp_var, $1.nom, $1.nom, temp_var++);
	}
}
| UNARY IDENTIFICATEUR { 
	verefier_declaration($2.nom); 
	$1.nd = faire_noeud(NULL, NULL, $1.nom); 
	$2.nd = faire_noeud(NULL, NULL, $2.nom); 
	$$.nd = faire_noeud($1.nd, $2.nd, "ITERATOR"); 
	if(!strcmp($1.nom, "++")) {
		sprintf(buff, "t%d = %s + 1\n%s = t%d\n", temp_var, $2.nom, $2.nom, temp_var++);
	}
	else {
		sprintf(buff, "t%d = %s - 1\n%s = t%d\n", temp_var, $2.nom, $2.nom, temp_var++);

	}
}
;

init: '=' valeur { $$.nd = $2.nd; strcpy($$.type, $2.type); strcpy($$.nom, $2.nom); }
| { strcpy($$.type, "null"); $$.nd = faire_noeud(NULL, NULL, "NULL"); strcpy($$.nom, "NULL"); }
;

expression: expression arithmetic expression { 
	if(!strcmp($1.type, $3.type)) {
		strcpy($$.type, $1.type);
		$$.nd = faire_noeud($1.nd, $3.nd, $2.nom); 
	}
	else {
		if(!strcmp($1.type, "int") && !strcmp($3.type, "float")) {
			struct noeud *temp = faire_noeud(NULL, $1.nd, "int_vers_float");
			strcpy($$.type, $3.type);
			$$.nd = faire_noeud(temp, $3.nd, $2.nom);
		}
		else if(!strcmp($1.type, "float") && !strcmp($3.type, "int")) {
			struct noeud *temp = faire_noeud(NULL, $3.nd, "int_vers_float");
			strcpy($$.type, $1.type);
			$$.nd = faire_noeud($1.nd, temp, $2.nom);
		}
		else if(!strcmp($1.type, "int") && !strcmp($3.type, "char")) {
			struct noeud *temp = faire_noeud(NULL, $3.nd, "char_vers_int");
			strcpy($$.type, $1.type);
			$$.nd = faire_noeud($1.nd, temp, $2.nom);
		}
		else if(!strcmp($1.type, "char") && !strcmp($3.type, "int")) {
			struct noeud *temp = faire_noeud(NULL, $1.nd, "char_vers_int");
			strcpy($$.type, $3.type);
			$$.nd = faire_noeud(temp, $3.nd, $2.nom);
		}
		else if(!strcmp($1.type, "float") && !strcmp($3.type, "char")) {
			struct noeud *temp = faire_noeud(NULL, $3.nd, "char_to_float");
			strcpy($$.type, $1.type);
			$$.nd = faire_noeud($1.nd, temp, $2.nom);
		}
		else {
			struct noeud *temp = faire_noeud(NULL, $1.nd, "char_to_float");
			strcpy($$.type, $3.type);
			$$.nd = faire_noeud(temp, $3.nd, $2.nom);
		}
	}
	sprintf($$.nom, "t%d", temp_var);
	temp_var++;
	sprintf(code3v[DOT_index++], "%s = %s %s %s\n",  $$.nom, $1.nom, $2.nom, $3.nom);
}
| valeur { strcpy($$.nom, $1.nom); strcpy($$.type, $1.type); $$.nd = $1.nd; }
;

arithmetic: PLUS 
| MOINS 
| MUL
| DIV
;

relop: LT
| GT
| LEQ
| GEQ
| EQ
| NOT
;

valeur: CONSTANTE { strcpy($$.nom, $1.nom); strcpy($$.type, "int"); ajouter('C'); $$.nd = faire_noeud(NULL, NULL, $1.nom); }
| IDENTIFICATEUR { strcpy($$.nom, $1.nom); char *id_type = retrurner_type($1.nom); strcpy($$.type, id_type); verefier_declaration($1.nom); $$.nd = faire_noeud(NULL, NULL, $1.nom); }
;

returne: RETURN  valeur ';' 

{ verefier_type_de_return($2.nom); $1.nd = faire_noeud(NULL, NULL, "return"); $$.nd = faire_noeud($1.nd, $2.nd, "RETURN"); }
| RETURN 
| 
;

%%

int main() {
	FILE* flog;
	flog=fopen("compilation.log","w");
    yyparse();
    printf("\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 1: LEXICAL ANALYSIS \n\n");
	printf("\nSYMBOL   DATATYPE   TYPE   LINE NUMBER \n");
	printf("_______________________________________\n\n");
	int i=0;
	for(i=0; i<compter; i++) {
		printf("%s\t%s\t%s\t%d\t\n", table_de_symbols[i].nom_id, table_de_symbols[i].type_data, table_de_symbols[i].type, table_de_symbols[i].ligne_nombre);
	}
	for(i=0;i<compter;i++) {
		free(table_de_symbols[i].nom_id);
		free(table_de_symbols[i].type);
	}
	printf("\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 2: l'ANALYSE SYNTAXIQUE \n\n");
	afficher_arbre(head); 
	
	FILE *fp;
	fp = fopen("ArbreSyntaxique.dot", "w"); // create or open the file for writing
	afficher_arbre_to_file(fp,head); 
    fclose(fp); // close the file
	printf("\n\n\n\n");

	FILE *fp_dot;
	fp_dot = fopen("output.dot", "w"); // create or open the file for writing
	afficher_arbre_dot_lcrs(fp_dot,head_dot); 
    fclose(fp_dot); // close the file
	printf("\n\n\n\n");

	printf("\t\t\t\t\t\t\t\t PHASE 3: L'ANALYSE SEMANTIQUE\n\n");
	if(sem_errors>0) {
		printf("L'analyse symantique est terminé avec  %d erreurs\n", sem_errors);
		for(int i=0; i<sem_errors; i++){
			printf("\t - %s", errors[i]);
		}
	} else {
		printf("L'analyse symantique est terminé avec  no erreurs");
	}
	printf("\n\n");
	printf("\t\t\t\t\t\t\t   PHASE 4: GENERATION DU CODE 3 variable\n\n");
	FILE *f3;
	f3 = fopen("3var.txt", "w"); // create or open the file for writing

	for(int i=0; i<DOT_index; i++){
		fprintf(f3,"%s", code3v[i]);
	}
	fclose(fp); // close the file
	printf("\n\n");
}

int chercher(char *type) {
	int i;
	for(i=compter-1; i>=0; i--) {
		if(strcmp(table_de_symbols[i].nom_id, type)==0) {
			return -1;
			break;
		}
	}
	return 0;
}

void verefier_declaration(char *c) {
    q = chercher(c);
    if(!q) {
        sprintf(errors[sem_errors], "Ligne %d: La Variable \"%s\" n'est pas declaré avant l'utilisation!\n", CompterN+1, c);
		sem_errors++;
    }
}

void verefier_type_de_return(char *valeur) {
	char *main_datatype = retrurner_type("main");
	char *return_datatype = retrurner_type(valeur);
	if((!strcmp(main_datatype, "int") && !strcmp(return_datatype, "CONST")) || !strcmp(main_datatype, return_datatype)){
		return ;
	}
	else {
		sprintf(errors[sem_errors], "Ligne %d: Le type de return est incorrect\n", CompterN+1);
		sem_errors++;
	}
}

int verefier_type(char *type1, char *type2){
	// declaration with no init
	if(!strcmp(type2, "null"))
		return -1;
	// both datatypes are same
	if(!strcmp(type1, type2))
		return 0;
	// both datatypes are different
	if(!strcmp(type1, "int") && !strcmp(type2, "float"))
		return 1;
	if(!strcmp(type1, "float") && !strcmp(type2, "int"))
		return 2;
	if(!strcmp(type1, "int") && !strcmp(type2, "char"))
		return 3;
	if(!strcmp(type1, "char") && !strcmp(type2, "int"))
		return 4;
	if(!strcmp(type1, "float") && !strcmp(type2, "char"))
		return 5;
	if(!strcmp(type1, "char") && !strcmp(type2, "float"))
		return 6;
}

char *retrurner_type(char *var){
	for(int i=0; i<compter; i++) {
		// Handle case of use before declaration
		if(!strcmp(table_de_symbols[i].nom_id, var)) {
			return table_de_symbols[i].type_data;
		}
	}
}

void ajouter(char c) {
	if(c == 'V'){
		for(int i=0; i<10; i++){
			if(!strcmp(reserves[i], strdup(yytext))){
        		sprintf(errors[sem_errors], "Line %d: Variable nom \"%s\" est un mot clé reservé!\n", CompterN+1, yytext);
				sem_errors++;
				return;
			}
		}
	}
    q=chercher(yytext);
	if(!q) {
		if(c == 'H') {
			table_de_symbols[compter].nom_id=strdup(yytext);
			table_de_symbols[compter].type_data=strdup(type);
			table_de_symbols[compter].ligne_nombre=CompterN;
			table_de_symbols[compter].type=strdup("Header");
			compter++;
		}
		else if(c == 'K') {
			table_de_symbols[compter].nom_id=strdup(yytext);
			table_de_symbols[compter].type_data=strdup("N/A");
			table_de_symbols[compter].ligne_nombre=CompterN;
			table_de_symbols[compter].type=strdup("Keyword\t");
			compter++;
		}
		else if(c == 'V') {
			table_de_symbols[compter].nom_id=strdup(yytext);
			table_de_symbols[compter].type_data=strdup(type);
			table_de_symbols[compter].ligne_nombre=CompterN;
			table_de_symbols[compter].type=strdup("Variable");
			compter++;
		}
		else if(c == 'C') {
			table_de_symbols[compter].nom_id=strdup(yytext);
			table_de_symbols[compter].type_data=strdup("CONST");
			table_de_symbols[compter].ligne_nombre=CompterN;
			table_de_symbols[compter].type=strdup("Constant");
			compter++;
		}
		else if(c == 'F') {
			table_de_symbols[compter].nom_id=strdup(yytext);
			table_de_symbols[compter].type_data=strdup(type);
			table_de_symbols[compter].ligne_nombre=CompterN;
			table_de_symbols[compter].type=strdup("Function");
			compter++;
		}
    }
    else if(c == 'V' && q) {
        sprintf(errors[sem_errors], "Line %d: Plusiers declaration de  \"%s\" n'est pas autorisé!\n", CompterN+1, yytext);
		sem_errors++;
    }
}

struct noeud* faire_noeud(struct noeud *gauche, struct noeud *droite, char *lexeme) {	
	struct noeud *newnode = (struct noeud *)malloc(sizeof(struct noeud));
	char *newstr = (char *)malloc(strlen(lexeme)+1);
	strcpy(newstr, lexeme);
	newnode->gauche = gauche;
	newnode->droite = droite;
	newnode->lexeme = newstr;
	return(newnode);
}
struct noeud_lcrs* faire_noeud_lcrs(struct noeud_lcrs *left_child, struct noeud_lcrs *right_sibling, char *label,char *shape,char *style) {	
	struct noeud_lcrs *newnode = (struct noeud_lcrs *)malloc(sizeof(struct noeud_lcrs));
	char *newlabel = (char *)malloc(strlen(label)+1);
	strcpy(newlabel, label);
		char *newstyle = (char *)malloc(strlen(style)+1);
	strcpy(newstyle, style);
		char *newsshape = (char *)malloc(strlen(shape)+1);
	strcpy(newsshape, shape);
	
	newnode->left_child = left_child;
	newnode->right_sibling = right_sibling;
	newnode->label =newlabel;
	newnode->style=newstyle;
	newnode->shape=newsshape;
	return(newnode);
}

void afficher_arbre(struct noeud* tree) {
	printf("\n\nLe parcour INFIXE DE l'arbre syntaxique est : \n\n");
	afficher_dans_lorder(tree);
}
void afficher_arbre_to_file(FILE* f,struct noeud* tree) {
	fprintf(f,"digraph mon_programme {\n");
	int j=1;
	affichage_prifixe_de_larbre_syntaxique(f,tree,&j);
	j=1;
	afficher_les_dependances_dot(f,tree,&j);
	fprintf(f,"\n}");

}
void afficher_arbre_dot_lcrs(FILE* f,struct noeud_lcrs* tree) {
	fprintf(f,"digraph mon_programme {\n");
	int j=1;
	affichage_prifixe_de_larbre_syntaxique_dot_lcrs(f,tree,&j);
	j=1;
	afficher_les_dependances_dot_lcrs(f,tree);
	fprintf(f,"\n}");

}
void afficher_dans_lorder(struct noeud *tree) {
	int i;
	if (tree->gauche) {
		afficher_dans_lorder(tree->gauche);
	}
	printf("%s, ", tree->lexeme);
	if (tree->droite) {
		afficher_dans_lorder(tree->droite);
	}
}
void affichage_prifixe_de_larbre_syntaxique(FILE* f,struct noeud *tree,int* j) {
	fprintf(f,"\nnode%d [label=\"%s\" shape=ellipse ];",*j, tree->lexeme);
	*j=*j+1;
	if (tree->gauche) {
		affichage_prifixe_de_larbre_syntaxique(f,tree->gauche,j);
	}
	if (tree->droite) {
		affichage_prifixe_de_larbre_syntaxique(f,tree->droite,j);
	}


}
void affichage_prifixe_de_larbre_syntaxique_dot_lcrs(FILE* f,struct noeud_lcrs *tree,int* j) {
	fprintf(f,"\nnode%d [label=\"%s\"  ",*j, tree->label);
	fprintf(f,"shape=\"%s\" ", tree->shape);
	fprintf(f,"style=\"%s\" ", tree->style);
	fprintf(f,"]");
	tree->inode=*j;
	*j=*j+1;
	if (tree->left_child) {
		affichage_prifixe_de_larbre_syntaxique_dot_lcrs(f,tree->left_child,j);
}
	if (tree->right_sibling) {
		affichage_prifixe_de_larbre_syntaxique_dot_lcrs(f,tree->right_sibling,j);
}


}
void afficher_les_dependances_dot(FILE* f,struct noeud *tree,int* j) {
	int p=*j;
	*j=*(j)+1;
	int g=*j;
	if (tree->gauche) {
		afficher_les_dependances_dot(f,tree->gauche,j);
	}
	int d=*j;
	if (tree->droite) {
		afficher_les_dependances_dot(f,tree->droite,j);
	}
		if (tree->gauche) fprintf(f,"\nnode%d->node%d;",p,g);
		if (tree->droite) fprintf(f,"\nnode%d->node%d;",p,d);
		}

void afficher_les_dependances_dot_lcrs(FILE* f,struct noeud_lcrs *tree) {
		if (tree->left_child){
			struct noeud_lcrs* current_chilid=tree->left_child;
			while(current_chilid){
				fprintf(f,"\nnode%d->node%d;",tree->inode,current_chilid->inode);
				afficher_les_dependances_dot_lcrs(f,current_chilid);
			}
			}
		}

void inserer_type() {
	strcpy(type, yytext);
}

void yyerror(const char *msg) {
    fprintf(stderr, "Erreur de Syntax: %s\n", msg);
    fprintf(stderr, "Le dernier lexème lue est '%s'\n", yytext);
    fprintf(stderr, "L'erreur est apparue dans la ligne %d, column \n", CompterN+1 );
    fprintf(stderr, "last rule %s\n", debug);
}
