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
	void afficher_arbre_dot(FILE* f,struct noeud*);
	void afficher_dans_lorder(struct noeud *);
	void affichage_prifixe_de_larbre_syntaxique_dot(FILE* f,struct noeud *,int* j);
    void verefier_declaration(char *);
	void verefier_type_de_return(char *);
	int verefier_type(char *, char *);
	char *get_type(char *);
	struct noeud* faire_noeud(struct noeud *gauche, struct noeud *droite, char *lexeme);

    struct dataType {
        char * nom_id;
        char * type_data;
        char * type;
        int ligne_nombre;
	} table_de_symbols[40];

    int compter=0;
    int q;
	char type[10];
    extern int CompterN;
	struct noeud *head;
	int sem_errors=0;
	int DOT_index=0;
	int temp_var=0;
	int label=0;
	int is_for=0;
	char buff[100];
	char errors[10][100];
	char reserved[12][10] = {"extern", "int", "void", "for", "while", "if", "then","else", "switch", "case", "default", "break"};
	char code3v[50][100];

	struct noeud { 
		struct noeud *gauche; 
		struct noeud *droite; 
		char *lexeme; 
	};

struct DOTNode
{
    int data;
    struct Node *next;
    struct Node *child;
};

%}

%union { struct nom_variable { 
			char nom[100]; 
			struct noeud* nd;
		} nd_obj;

		struct nom_variable2 { 
			char nom[100]; 
			struct noeud* nd;
			char type[5];
		} nd_obj2; 

		struct nom_variable3 {
			char nom[100];
			struct noeud* nd;
			char if_body[5];
			char else_body[5];
		} nd_obj3;
	} 
%token VOID 
%token <nd_obj> EXTERN CHARACTER PRINTFF SCANFF INT FLOAT CHAR FOR WHILE SWITCH CASE DEFAULT BREAK IF ELSE TRUE FALSE CONSTANTE FLOAT_NUM IDENTIFICATEUR LEQ GEQ EQ NOT GT LT LAND LOR NEQ STR PLUS MUL DIV MOINS UNARY INCLUDE RETURN 
%type <nd_obj> externe externs main liste_instructions returne datatype statement arithmetic relop programme else instruction 
%type <nd_obj2> init value expression
%type <nd_obj3> condition

%%

programme: main '(' ')' '{' liste_instructions returne '}' { 
$1.nd = faire_noeud($5.nd, NULL, "main");
$$.nd = faire_noeud($1.nd, NULL, "programme"); 
head = $$.nd;
} 
| externs programme {
	$$.nd=$2.nd;
	head=$$.nd;
}
;

main: datatype IDENTIFICATEUR { ajouter('F'); }
;
externs: externs externe
|externe
|
;
externe: EXTERN datatype IDENTIFICATEUR { ajouter('F'); } '(' liste_parms ')' ';'
;

liste_parms	:liste_parms ',' parm
	|	parm
	| 
;
parm	:	
		INT IDENTIFICATEUR { ajouter('V'); }
;
liste_declarations	:	
		liste_declarations declaration 
	|	
;
liste_declarateurs	:	
		liste_declarateurs ',' declarateur
	|	declarateur
;
declarateur	:	
		IDENTIFICATEUR
	|	declarateur '[' CONSTANTE ']'
;
declaration	:	
		datatype liste_declarateurs ';'
;
datatype: INT { inserer_type(); }
| FLOAT { inserer_type(); }
| CHAR { inserer_type(); }
| VOID { inserer_type(); }
;
liste_instructions :	liste_instructions  instruction
	| instruction
	|
;
instruction: FOR { ajouter('K'); is_for = 1; } '(' statement ';' condition ';' statement ')' '{' liste_instructions '}' { 
	struct noeud *temp = faire_noeud($6.nd, $8.nd, "CONDITION"); 
	struct noeud *temp2 = faire_noeud($4.nd, temp, "CONDITION"); 
	$$.nd = faire_noeud(temp2, $11.nd, $1.nom); 
	sprintf(code3v[DOT_index++], buff);
	sprintf(code3v[DOT_index++], "JUMP to %s\n", $6.if_body);
	sprintf(code3v[DOT_index++], "\nLABEL %s:\n", $6.else_body);
}
| IF { ajouter('K'); is_for = 0; } '(' condition ')' { sprintf(code3v[DOT_index++], "\nLABEL %s:\n", $4.if_body); } '{' liste_instructions '}' { sprintf(code3v[DOT_index++], "\nLABEL %s:\n", $4.else_body); } else { 
	struct noeud *iff = faire_noeud($4.nd, $8.nd, $1.nom); 
	$$.nd = faire_noeud(iff, $11.nd, "if-else"); 
	sprintf(code3v[DOT_index++], "GOTO next\n");
}
| statement ';' { $$.nd = $1.nd; }
| liste_instructions liste_instructions { $$.nd = faire_noeud($1.nd, $2.nd, "instructions"); }
| PRINTFF { ajouter('K'); } '(' STR ')' ';' { $$.nd = faire_noeud(NULL, NULL, "printf"); }
| SCANFF { ajouter('K'); } '(' STR ',' '&' IDENTIFICATEUR ')' ';' { $$.nd = faire_noeud(NULL, NULL, "scanf"); }
;

else: ELSE { ajouter('K'); } '{' liste_instructions '}' { $$.nd = faire_noeud(NULL, $4.nd, $1.nom); }
| { $$.nd = NULL; }
;

condition: value relop value { 
	$$.nd = faire_noeud($1.nd, $3.nd, $2.nom); 
	if(is_for) {
		sprintf($$.if_body, "L%d", label++);
		sprintf(code3v[DOT_index++], "\nLABEL %s:\n", $$.if_body);
		sprintf(code3v[DOT_index++], "\nif NOT (%s %s %s) GOTO L%d\n", $1.nom, $2.nom, $3.nom, label);
		sprintf($$.else_body, "L%d", label++);
	} else {
		sprintf(code3v[DOT_index++], "\nif (%s %s %s) GOTO L%d else GOTO L%d\n", $1.nom, $2.nom, $3.nom, label, label+1);
		sprintf($$.if_body, "L%d", label++);
		sprintf($$.else_body, "L%d", label++);
	}
}
| TRUE { ajouter('K'); $$.nd = NULL; }
| FALSE { ajouter('K'); $$.nd = NULL; }
| { $$.nd = NULL; }
;

statement: datatype IDENTIFICATEUR { ajouter('V'); } init { 
	$2.nd = faire_noeud(NULL, NULL, $2.nom); 
	int t = verefier_type($1.nom, $4.type); 
	if(t>0) { 
		if(t == 1) {
			struct noeud *temp = faire_noeud(NULL, $4.nd, "floattoint"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		} 
		else if(t == 2) { 
			struct noeud *temp = faire_noeud(NULL, $4.nd, "inttofloat"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		} 
		else if(t == 3) { 
			struct noeud *temp = faire_noeud(NULL, $4.nd, "chartoint"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		} 
		else if(t == 4) { 
			struct noeud *temp = faire_noeud(NULL, $4.nd, "inttochar"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		} 
		else if(t == 5) { 
			struct noeud *temp = faire_noeud(NULL, $4.nd, "chartofloat"); 
			$$.nd = faire_noeud($2.nd, temp, ":="); 
		} 
		else{
			struct noeud *temp = faire_noeud(NULL, $4.nd, "floattochar"); 
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
	char *id_type = get_type($1.nom); 
	if(strcmp(id_type, $4.type)) {
		if(!strcmp(id_type, "int")) {
			if(!strcmp($4.type, "float")){
				struct noeud *temp = faire_noeud(NULL, $4.nd, "floattoint");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
			else{
				struct noeud *temp = faire_noeud(NULL, $4.nd, "chartoint");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
			
		}
		else if(!strcmp(id_type, "float")) {
			if(!strcmp($4.type, "int")){
				struct noeud *temp = faire_noeud(NULL, $4.nd, "inttofloat");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
			else{
				struct noeud *temp = faire_noeud(NULL, $4.nd, "chartofloat");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
			
		}
		else{
			if(!strcmp($4.type, "int")){
				struct noeud *temp = faire_noeud(NULL, $4.nd, "inttochar");
				$$.nd = faire_noeud($1.nd, temp, ":="); 
			}
			else{
				struct noeud *temp = faire_noeud(NULL, $4.nd, "floattochar");
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

init: '=' value { $$.nd = $2.nd; sprintf($$.type, $2.type); strcpy($$.nom, $2.nom); }
| { sprintf($$.type, "null"); $$.nd = faire_noeud(NULL, NULL, "NULL"); strcpy($$.nom, "NULL"); }
;

expression: expression arithmetic expression { 
	if(!strcmp($1.type, $3.type)) {
		sprintf($$.type, $1.type);
		$$.nd = faire_noeud($1.nd, $3.nd, $2.nom); 
	}
	else {
		if(!strcmp($1.type, "int") && !strcmp($3.type, "float")) {
			struct noeud *temp = faire_noeud(NULL, $1.nd, "inttofloat");
			sprintf($$.type, $3.type);
			$$.nd = faire_noeud(temp, $3.nd, $2.nom);
		}
		else if(!strcmp($1.type, "float") && !strcmp($3.type, "int")) {
			struct noeud *temp = faire_noeud(NULL, $3.nd, "inttofloat");
			sprintf($$.type, $1.type);
			$$.nd = faire_noeud($1.nd, temp, $2.nom);
		}
		else if(!strcmp($1.type, "int") && !strcmp($3.type, "char")) {
			struct noeud *temp = faire_noeud(NULL, $3.nd, "chartoint");
			sprintf($$.type, $1.type);
			$$.nd = faire_noeud($1.nd, temp, $2.nom);
		}
		else if(!strcmp($1.type, "char") && !strcmp($3.type, "int")) {
			struct noeud *temp = faire_noeud(NULL, $1.nd, "chartoint");
			sprintf($$.type, $3.type);
			$$.nd = faire_noeud(temp, $3.nd, $2.nom);
		}
		else if(!strcmp($1.type, "float") && !strcmp($3.type, "char")) {
			struct noeud *temp = faire_noeud(NULL, $3.nd, "chartofloat");
			sprintf($$.type, $1.type);
			$$.nd = faire_noeud($1.nd, temp, $2.nom);
		}
		else {
			struct noeud *temp = faire_noeud(NULL, $1.nd, "chartofloat");
			sprintf($$.type, $3.type);
			$$.nd = faire_noeud(temp, $3.nd, $2.nom);
		}
	}
	sprintf($$.nom, "t%d", temp_var);
	temp_var++;
	sprintf(code3v[DOT_index++], "%s = %s %s %s\n",  $$.nom, $1.nom, $2.nom, $3.nom);
}
| value { strcpy($$.nom, $1.nom); sprintf($$.type, $1.type); $$.nd = $1.nd; }
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

value: CONSTANTE { strcpy($$.nom, $1.nom); sprintf($$.type, "int"); ajouter('C'); $$.nd = faire_noeud(NULL, NULL, $1.nom); }
| FLOAT_NUM { strcpy($$.nom, $1.nom); sprintf($$.type, "float"); ajouter('C'); $$.nd = faire_noeud(NULL, NULL, $1.nom); }
| CHARACTER { strcpy($$.nom, $1.nom); sprintf($$.type, "char"); ajouter('C'); $$.nd = faire_noeud(NULL, NULL, $1.nom); }
| IDENTIFICATEUR { strcpy($$.nom, $1.nom); char *id_type = get_type($1.nom); sprintf($$.type, id_type); verefier_declaration($1.nom); $$.nd = faire_noeud(NULL, NULL, $1.nom); }
;

returne: RETURN { ajouter('K'); } value ';' { verefier_type_de_return($3.nom); $1.nd = faire_noeud(NULL, NULL, "return"); $$.nd = faire_noeud($1.nd, $3.nd, "RETURN"); }
| RETURN
| 
;

%%

int main() {
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
	fp = fopen("output.dot", "w"); // create or open the file for writing
	afficher_arbre_dot(fp,head); 
    fclose(fp); // close the file
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

void verefier_type_de_return(char *value) {
	char *main_datatype = get_type("main");
	char *return_datatype = get_type(value);
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

char *get_type(char *var){
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
			if(!strcmp(reserved[i], strdup(yytext))){
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

void afficher_arbre(struct noeud* tree) {
	printf("\n\nInorder traversal of the Parse Tree is: \n\n");
	afficher_dans_lorder(tree);
}
void afficher_arbre_dot(FILE* f,struct noeud* tree) {
	fprintf(f,"digraph mon_programme {\n");
	int j=1;
	affichage_prifixe_de_larbre_syntaxique_dot(f,tree,&j);
	j=1;
	afficher_les_dependances_dot(f,tree,&j);
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
void affichage_prifixe_de_larbre_syntaxique_dot(FILE* f,struct noeud *tree,int* j) {
	fprintf(f,"\nnode%d [label=\"%s\" shape=ellipse ];",*j, tree->lexeme);
	*j=*j+1;
	if (tree->gauche) {
		affichage_prifixe_de_larbre_syntaxique_dot(f,tree->gauche,j);
	}
	if (tree->droite) {
		affichage_prifixe_de_larbre_syntaxique_dot(f,tree->droite,j);
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

void inserer_type() {
	strcpy(type, yytext);
}

void yyerror(const char *msg) {
    fprintf(stderr, "Syntax error: %s\n", msg);
    fprintf(stderr, "Last token read was '%s'\n", yytext);
    fprintf(stderr, "Error occurred at line %d, column %d\n", CompterN+1 );
    fprintf(stderr, "The input was: %.*s\n", yyleng, yytext);
}
