%{
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include"lex.yy.c"

//Analyse yacc fonctions
    void yyerror(const char *s);
    int yylex();
// Table de symbole fonctions
    void ajouter(char);
    int chercher(char *);


// Affichage d'arbre syntaxique
	void afficher_arbre(struct noeud*);
	void afficher_arbre_to_file(FILE* f,struct noeud*);
	void afficher_dans_lorder(struct noeud *);
	void affichage_prifixe_de_larbre_syntaxique(FILE* f,struct noeud *,int* j);
	struct noeud* faire_noeud(struct noeud *gauche, struct noeud *droite, char *lexeme);
	void afficher_les_dependances_dot(FILE* f,struct noeud *tree,int* j);


// Analyse semantique
    void verefier_declaration(char *);
	void verefier_type_de_return(char *);
	char *retrurner_type(char *);

	struct noeud_lcrs* faire_noeud_lcrs(struct noeud_lcrs *left_child, struct noeud_lcrs *right_sibling, char *description);
   // Fonctions pour dessiner l'arbre de l'output
    void afficher_les_dependances_dot_lcrs(FILE* f,struct noeud_lcrs *tree);
	void affichage_prifixe_de_larbre_syntaxique_dot_lcrs(FILE* f,struct noeud_lcrs *tree,int* j);
	void afficher_arbre_dot_lcrs(FILE* f,struct noeud_lcrs* tree);
	void  ajouter_dernier_fils(struct noeud_lcrs* pere,struct noeud_lcrs* fils);
	struct noeud_lcrs* get_last_sibling(struct noeud_lcrs* tree);
	// Concatenation avec creation d'un nouveau chaine
	char* concatener(char*a,char*b);
	//insertion du lexeme rencontré dans la variable type
	void inserer_type();
	//Un table de symbole statique de longeur 100
	struct dataType {
        char * nom_id;
        char * type_data;
        char * type;
        int ligne_nombre;
	} table_de_symbols[100];
//une variable pour garder le nom de la fonction principale 'la premiere fonction rencontrée'
	char* main_function=NULL;
//Un nombre qui compte le nombre des symboles dans la table de symbole
    int compter_symbole=0;

    int requete;//variable temporaire
	char type[10];//variable temporaire qui garde le type d'un lexeme 
	extern int yylineno; 
	struct noeud *head;
	struct noeud_lcrs *head_dot;

	int sem_errors=0;//Nombre des erreurs sémantique
	int _3adr_index=0;// nombre des instruction en 3 var code

	int temp_var=0;//Compteur pour les registres en 3 var code
	int label_count=0;//the number of labels in the 3 variable code 
	int is_for=0;// pour code 3 var pour destiguer l'utilisation d'une condition 
	char buff_3adr[300];//variable temporaire pour enregistrer les chaines 3 var
	char strTmp[300];//variable temporaire pour enregistrer les chaines des description des fichier DOT
	char errors[10][100];// Un tableu des erreurs sémantiques
	char reserves[12][10] = {"extern", "int", "void", "for", "while", "if", "then","else", "switch", "case", "default", "break"};
	char code3v[500][100];//Tableu pour stocker le code 3 var

	struct noeud { 
		struct noeud *gauche; 
		struct noeud *droite; 
		char *lexeme; 
	};
	struct noeud_lcrs { 
		struct noeud_lcrs *left_child; 
		struct noeud_lcrs *right_sibling; 
		char *description;
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
%token <nd_obj> EXTERN INT CHAR FOR WHILE SWITCH CASE DEFAULT BREAK THEN IF ELSE TRUE FALSE CONSTANTE IDENTIFICATEUR LEQ GEQ EQ NOT GT BAND BOR LSHIFT RSHIFT LT LAND LOR NEQ STR  PLUS MUL DIV MOINS UNARY INCLUDE RETURN 
%type <nd_obj> externe main liste_fonctions fonction nom_fonction liste_instructions liste_declarations declaration selection tableu liste_declarateurs declarateur liste_expressions returne appel datatype instruction1 arithmetic binary_comp programme else instruction binary_op
%type <nd_obj2> init valeur expression variable 
%type <nd_obj3> condition
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
programme	:	
		 liste_fonctions
		{
		$$.nd=faire_noeud($1.nd,NULL,"programme");
		head = $$.nd; 


		$$.nd_dot=faire_noeud_lcrs($1.nd_dot,NULL,"label=programme");
		head_dot=$$.nd_dot;}
		
;
liste_fonctions	:	
		liste_fonctions fonction
		{
		$$.nd=faire_noeud($1.nd,$2.nd,"fonctions");
		$$.nd_dot=$1.nd_dot;
		
		
		if($1.nd_dot!=NULL)$1.nd_dot->right_sibling=$2.nd_dot;
		else $$.nd_dot=$1.nd_dot=$2.nd_dot;
		}
|               fonction {$$.nd=$1.nd; $$.nd_dot=$1.nd_dot;}
;
fonction: nom_fonction '(' ')' '{' liste_instructions  '}' { 
$$.nd = $1.nd;
$1.nd->gauche=$5.nd;



$$.nd_dot = $1.nd_dot;
$1.nd_dot->left_child=faire_noeud_lcrs($5.nd_dot, NULL, "label=BLOC");

} 
| externe {$$.nd=NULL;$$.nd_dot=NULL;}
;

nom_fonction: datatype IDENTIFICATEUR { ajouter('F'); if(!main_function)main_function=concatener("",yytext);} 
{
$$.nd=faire_noeud(NULL,NULL,concatener("fonction ",$2.nom));
sprintf(strTmp,"label=\"%s, %s\" shape=invtrapezium color=blue",$2.nom,$1.nom);
$$.nd_dot=faire_noeud_lcrs(NULL, NULL, strTmp);

}
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
liste_declarateurs	: declarateur ',' liste_declarateurs 
	|	declarateur
	| declarateur init 
;
declarateur	:  IDENTIFICATEUR {ajouter('V');}
	|	declarateur '[' CONSTANTE {ajouter('C');}']'
;
declaration	:	
		datatype liste_declarateurs ';'
;
datatype:  INT { inserer_type(); }
| VOID { inserer_type(); }
;
liste_instructions :	instruction liste_instructions   
{$$.nd=faire_noeud($1.nd,$2.nd,"instructions");
if($1.nd_dot){
$1.nd_dot->right_sibling=$2.nd_dot;
$$.nd_dot=$1.nd_dot;}
else $$.nd_dot=$2.nd_dot;

}
	| instruction {$$.nd_dot=$1.nd_dot;}
	|
;
instruction:
| FOR { ajouter('K'); is_for = 1; } '(' instruction1 ';' condition ';' instruction1 ')' instruction  { 
	struct noeud *temp = faire_noeud($6.nd, $8.nd, "CONDITION"); 
	struct noeud *temp2 = faire_noeud($4.nd, temp, "CONDITION"); 
	$$.nd = faire_noeud(temp2, $10.nd, $1.nom); 
	strcpy(code3v[_3adr_index++], buff_3adr);
	sprintf(code3v[_3adr_index++], "JUMP to %s\n", $6.if_corps);
	sprintf(code3v[_3adr_index++], "\nLABEL %s:\n", $6.else_corps);
	$$.nd_dot=faire_noeud_lcrs($4.nd_dot,NULL,"label=for");
	$4.nd_dot->right_sibling=$6.nd_dot;
	$6.nd_dot->right_sibling=$8.nd_dot;
	$8.nd_dot->right_sibling=$10.nd_dot;
}

| selection {$$.nd=$1.nd;}
| instruction1 ';' { $$.nd = $1.nd; $$.nd_dot=$1.nd_dot;}
| appel {$$.nd=$1.nd;
$$.nd_dot=$1.nd_dot;}
|declaration {$$.nd_dot=NULL;}
|returne {$$.nd=$1.nd;$$.nd_dot=$1.nd_dot;}
| BREAK ';'{$$.nd=faire_noeud(NULL,NULL,"break");$$.nd_dot=faire_noeud_lcrs(NULL,NULL,"label=break");}
;



instruction1:
| IDENTIFICATEUR { verefier_declaration($1.nom); } '=' expression {
	$1.nd = faire_noeud(NULL, NULL, $1.nom); 
	$$.nd = faire_noeud($1.nd, $4.nd, ":="); 
	sprintf(code3v[_3adr_index++], "%s = %s\n", $1.nom, $4.nom);
	sprintf(strTmp,"label=%s",$1.nom);
	$$.nd_dot=faire_noeud_lcrs(faire_noeud_lcrs(NULL,$4.nd_dot,strTmp),NULL,"label=\":=\"");
}
| IDENTIFICATEUR { verefier_declaration($1.nom); } binary_comp expression {
	 $1.nd = faire_noeud(NULL, NULL, $1.nom);
	  $$.nd = faire_noeud($1.nd, $4.nd, $3.nom); 
	  $$.nd_dot=faire_noeud_lcrs(NULL,NULL,"label=affectation2");}
| IDENTIFICATEUR { verefier_declaration($1.nom); } UNARY { 
	$1.nd = faire_noeud(NULL, NULL, $1.nom); 
	$3.nd = faire_noeud(NULL, NULL, $3.nom); 
	$$.nd = faire_noeud($1.nd, $3.nd, "ITERATOR");  
	if(!strcmp($3.nom, "++")) {
		sprintf(buff_3adr, "t%d = %s + 1\n%s = t%d\n", temp_var, $1.nom, $1.nom, temp_var++);
	}
	else {
		sprintf(buff_3adr, "t%d = %s + 1\n%s = t%d\n", temp_var, $1.nom, $1.nom, temp_var++);
	}
	$$.nd_dot=faire_noeud_lcrs(NULL,NULL,"label=affectation3");
}
| UNARY IDENTIFICATEUR { 
	verefier_declaration($2.nom); 
	$1.nd = faire_noeud(NULL, NULL, $1.nom); 
	$2.nd = faire_noeud(NULL, NULL, $2.nom); 
	$$.nd = faire_noeud($1.nd, $2.nd, "ITERATOR"); 
	if(!strcmp($1.nom, "++")) {
		sprintf(buff_3adr, "t%d = %s + 1\n%s = t%d\n", temp_var, $2.nom, $2.nom, temp_var++);
	}
	else {
		sprintf(buff_3adr, "t%d = %s - 1\n%s = t%d\n", temp_var, $2.nom, $2.nom, temp_var++);

	}
	$$.nd_dot=faire_noeud_lcrs(NULL,NULL,"label=affectation4");
}
;

init: '=' valeur { $$.nd = $2.nd; strcpy($$.type, $2.type); strcpy($$.nom, $2.nom); }
;

selection	:		IF { ajouter('K'); is_for = 0; } '(' condition  ')' 
{ sprintf(code3v[_3adr_index++], "\nLABEL %s:\n", $4.if_corps); }   instruction %prec THEN
	{struct noeud *iff = faire_noeud($4.nd, $7.nd, $1.nom); 
	sprintf(code3v[_3adr_index++], "GOTO next\n");
	$$.nd_dot=faire_noeud_lcrs($4.nd_dot,NULL,"label=if shape=diamond");
	$4.nd_dot->right_sibling=$7.nd_dot;	
	}
	|IF { ajouter('K'); is_for = 0; } '(' condition  ')' 
{ sprintf(code3v[_3adr_index++], "\nLABEL %s:\n", $4.if_corps); }   instruction   
{ sprintf(code3v[_3adr_index++], "\nLABEL %s:\n", $4.else_corps); } 
ELSE instruction
	{struct noeud *iff = faire_noeud($4.nd, $7.nd, $1.nom); 
	$$.nd = faire_noeud(iff, $10.nd, "if-else"); 
	sprintf(code3v[_3adr_index++], "GOTO next\n");
	$$.nd_dot=faire_noeud_lcrs($4.nd_dot,NULL,"label=if shape=diamond");
	$4.nd_dot->right_sibling=$7.nd_dot;
	$7.nd_dot->right_sibling=$10.nd_dot;
	}|
	SWITCH '(' expression ')' instruction
	|	CASE CONSTANTE ':' instruction
	|	DEFAULT ':' instruction
;



appel	:	
		IDENTIFICATEUR '(' liste_expressions ')' ';'

		{

			sprintf(code3v[_3adr_index++],"call %s (%s)",$1.nom,$3.nom);
			$1.nd=faire_noeud($3.nd,NULL,$1.nom); $$.nd=$1.nd;
			sprintf(strTmp,"label=%s shape=septagon",$1.nom);
				$$.nd_dot=faire_noeud_lcrs($3.nd_dot,NULL,strTmp);
		}
;
variable	:	
		IDENTIFICATEUR  
		{$$.nd=faire_noeud(NULL,NULL,$1.nom);
		sprintf(strTmp,"label=%s",$1.nom);
		$$.nd_dot=faire_noeud_lcrs(NULL,NULL,strTmp);
		}
	|	tableu {$$.nd_dot= faire_noeud_lcrs($1.nd_dot,NULL,"label=TAB");}
	
;
tableu: tableu '[' expression ']' 	{
		$3.nd_dot->description=concatener($3.nd_dot->description," style=dotted shape=triangle");
		get_last_sibling($1.nd_dot)->right_sibling=$3.nd_dot;
		$$.nd_dot= $1.nd_dot;
	}
	|		IDENTIFICATEUR  
		{$$.nd=faire_noeud(NULL,NULL,$1.nom);
		sprintf(strTmp,"label=%s",$1.nom);
		$$.nd_dot=faire_noeud_lcrs(NULL,NULL,strTmp);
		}

;
expression	:	
		'(' expression ')' {$$.nd=$2.nd;$$.nd_dot=$2.nd_dot;}
	|	expression binary_op expression %prec OP 
	{
	$$.nd=faire_noeud($1.nd,$3.nd,$2.nom);
	
	sprintf(strTmp,"label=\"%s\"",$2.nom);
	$$.nd_dot=faire_noeud_lcrs($1.nd_dot,NULL,strTmp);
	$1.nd_dot->right_sibling=$3.nd_dot;
	} 
	|	MOINS expression {$$.nd=$2.nd;
	$$.nd_dot=faire_noeud_lcrs($2.nd_dot,NULL,"label=\"-\" ");}
	|	CONSTANTE { ajouter('C'); } 
	{struct noeud* tmp=faire_noeud(NULL,NULL,$1.nom);
	$$.nd=tmp;
	sprintf(strTmp,"label=%s",$1.nom) ;
	$$.nd_dot=faire_noeud_lcrs(NULL,NULL,strTmp);}
	|	variable {$$.nd=$1.nd; $$.nd_dot=$1.nd_dot;}
	|	IDENTIFICATEUR '(' liste_expressions ')'

;
liste_expressions	:liste_expressions ',' expression {$$.nd=faire_noeud($1.nd,$3.nd,"expressions");}
	| expression {$$.nd=$1.nd;}
;
else: ELSE { ajouter('K'); } '{' liste_instructions '}' { $$.nd = faire_noeud(NULL, $4.nd, $1.nom); }
| { $$.nd = NULL; }
;
binary_op	:	
		PLUS
	|   MOINS
	|	MUL
	|	DIV
	|       LSHIFT
	|       RSHIFT
	|	BAND
	|	BOR
;

condition: expression binary_comp expression { 
	$$.nd = faire_noeud($1.nd, $3.nd, $2.nom); 
	if(is_for) {
		sprintf($$.if_corps, "L%d", label_count++);
		sprintf(code3v[_3adr_index++], "\nLABEL %s:\n", $$.if_corps);
		sprintf(code3v[_3adr_index++], "\nif NOT (%s %s %s) GOTO L%d\n", $1.nom, $2.nom, $3.nom, label_count);
		sprintf($$.else_corps, "L%d", label_count++);
	} else {
		sprintf(code3v[_3adr_index++], "\nif (%s %s %s) GOTO L%d else GOTO L%d\n", $1.nom, $2.nom, $3.nom, label_count, label_count+1);
		sprintf($$.if_corps, "L%d", label_count++);
		sprintf($$.else_corps, "L%d", label_count++);
	}
	sprintf(strTmp,"label=\"%s\"",$2.nom);
	$$.nd_dot=faire_noeud_lcrs($1.nd_dot,NULL,strTmp);
	$1.nd_dot->right_sibling=$3.nd_dot;
}

|NOT '(' condition ')' {
	
	
$$.nd=faire_noeud($1.nd,NULL,"not");
$$.nd_dot=faire_noeud_lcrs($1.nd_dot,NULL,"label=not");}
| TRUE { ajouter('K'); $$.nd = NULL; }
| FALSE { ajouter('K'); $$.nd = NULL; }
| { $$.nd = NULL; }
;


expression: expression arithmetic expression { 
	strcpy($$.type, $1.type);
	$$.nd = faire_noeud($1.nd, $3.nd, $2.nom); 
	sprintf($$.nom, "t%d", temp_var);
	temp_var++;
	sprintf(code3v[_3adr_index++], "%s = %s %s %s\n",  $$.nom, $1.nom, $2.nom, $3.nom);
	sprintf(strTmp,"label= \"%s\" ",$2.nom);
	$1.nd_dot->right_sibling=$3.nd_dot;
	$$.nd_dot=faire_noeud_lcrs($1.nd_dot,NULL, strTmp); 
}
| valeur {
strcpy($$.nom, $1.nom);
strcpy($$.type, $1.type); 
$$.nd = $1.nd;
$$.nd_dot=$1.nd_dot;
}
;

arithmetic: PLUS 
| MOINS 
| MUL
| DIV
;

binary_comp: LT
| GT
| LEQ
| GEQ
| EQ
| NEQ
;

valeur: CONSTANTE 
{
strcpy($$.nom, $1.nom);
 strcpy($$.type, "int");
 ajouter('C'); 
 $$.nd = faire_noeud(NULL, NULL, $1.nom); 
 sprintf(strTmp,"label=%s",$1.nom);
 $$.nd_dot=faire_noeud_lcrs(NULL,NULL,strTmp);
 }
| IDENTIFICATEUR { strcpy($$.nom, $1.nom); char *id_type = retrurner_type($1.nom); strcpy($$.type, id_type); verefier_declaration($1.nom); $$.nd = faire_noeud(NULL, NULL, $1.nom); }
;

returne: RETURN  expression ';' 
{ verefier_type_de_return($2.nom);
 $1.nd = faire_noeud(NULL, NULL, "return");
$$.nd = faire_noeud($1.nd, $2.nd, "RETURN"); 
$$.nd_dot=faire_noeud_lcrs($2.nd_dot,NULL,"label=RETURN shape=trapezium color=blue");
}
| RETURN ';'{
$$.nd = faire_noeud(NULL, NULL, "return");
$$.nd_dot=faire_noeud_lcrs(NULL,NULL,"label=RETURN shape=trapezium color=blue");
}
| 
;

%%

int main() {
	system("mkdir -p result");
	//system("rm -r lex.yy.c y.tab.c y.tab.h y.output");
    yyparse();
    printf("\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 1: LEXICAL ANALYSIS \n\n");
	printf("\nSYMBOL   DATATYPE   TYPE   LINE NUMBER \n");
	printf("_______________________________________\n\n");
	int i=0;
	for(i=0; i<compter_symbole; i++) {
		printf("%s\t%s\t%s\t%d\t\n", table_de_symbols[i].nom_id, table_de_symbols[i].type_data, table_de_symbols[i].type, table_de_symbols[i].ligne_nombre);
	}
	for(i=0;i<compter_symbole;i++) {
		free(table_de_symbols[i].nom_id);
		free(table_de_symbols[i].type);
	}
	printf("\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 2: l'ANALYSE SYNTAXIQUE \n\n");
	afficher_arbre(head); 
	
	FILE *fp;
	fp = fopen("result/ArbreSyntaxique.dot", "w"); // create or open the file for writing
	afficher_arbre_to_file(fp,head); 
    fclose(fp); // close the file

	printf("\n\n\n\n");

	FILE *fp_dot;
	fp_dot = fopen("result/output.dot", "w"); // create or open the file for writing
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
	f3 = fopen("result/3adr.txt", "w"); // create or open the file for writing

	for(int i=0; i<_3adr_index; i++){
		printf("%s\n", code3v[i]);
		fprintf(f3,"%s\n", code3v[i]);
	}
	fclose(fp); // close the file
	printf("\n\n");
	system("dot -Tpdf result/ArbreSyntaxique.dot -o result/ArbreSyntaxique.pdf");
	system("dot -Tpdf result/output.dot -o result/output.pdf");
}

int chercher(char *type) {
	int i;
	for(i=compter_symbole-1; i>=0; i--) {
		if(strcmp(table_de_symbols[i].nom_id, type)==0) {
			return -1;
		}
	}
	return 0;
}

void verefier_declaration(char *c) {
    requete = chercher(c);
    if(!requete) {
        sprintf(errors[sem_errors], "Ligne %d: La Variable \"%s\" n'est pas declaré avant l'utilisation!\n", yylineno+1, c);
		sem_errors++;
    }
}

void verefier_type_de_return(char *valeur) {
	char *main_datatype = retrurner_type(main_function);
	char *return_datatype = retrurner_type(valeur);
	if((!strcmp(main_datatype, "int") && !strcmp(return_datatype, "CONST")) || !strcmp(main_datatype, return_datatype)){
		return ;
	}
	else {
		sprintf(errors[sem_errors], "Ligne %d: Le type de return est incorrect\n", yylineno+1);
		sem_errors++;
	}
}

char *retrurner_type(char *var){
	for(int i=0; i<compter_symbole; i++) {
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
        		sprintf(errors[sem_errors], "Line %d: Variable nom \"%s\" est un mot clé reservé!\n", yylineno+1, yytext);
				sem_errors++;
				return;
			}
		}
	}
    requete=chercher(yytext);
	if(!requete) {
		if(c == 'K') {
			table_de_symbols[compter_symbole].nom_id=strdup(yytext);
			table_de_symbols[compter_symbole].type_data=strdup("N/A");
			table_de_symbols[compter_symbole].ligne_nombre=yylineno;
			table_de_symbols[compter_symbole].type=strdup("Keyword\t");
			compter_symbole++;
		}
		else if(c == 'V') {
			table_de_symbols[compter_symbole].nom_id=strdup(yytext);
			table_de_symbols[compter_symbole].type_data=strdup(type);
			table_de_symbols[compter_symbole].ligne_nombre=yylineno;
			table_de_symbols[compter_symbole].type=strdup("Variable");
			compter_symbole++;
		}
		else if(c == 'C') {
			table_de_symbols[compter_symbole].nom_id=strdup(yytext);
			table_de_symbols[compter_symbole].type_data=strdup("CONST");
			table_de_symbols[compter_symbole].ligne_nombre=yylineno;
			table_de_symbols[compter_symbole].type=strdup("Constant");
			compter_symbole++;
		}
		else if(c == 'F') {
			table_de_symbols[compter_symbole].nom_id=strdup(yytext);
			table_de_symbols[compter_symbole].type_data=strdup(type);
			table_de_symbols[compter_symbole].ligne_nombre=yylineno;
			table_de_symbols[compter_symbole].type=strdup("Function");
			compter_symbole++;
		}
    }
    else if(c == 'V' && requete) {
        sprintf(errors[sem_errors], "Line %d: Plusiers declaration de  \"%s\" n'est pas autorisé!\n", yylineno+1, yytext);
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
struct noeud_lcrs* faire_noeud_lcrs(struct noeud_lcrs *left_child, struct noeud_lcrs *right_sibling,char* description){
	struct noeud_lcrs *newnode = (struct noeud_lcrs *)malloc(sizeof(struct noeud_lcrs));
	char *newdescription = (char *)malloc(strlen(description)+1);
	strcpy(newdescription, description);
	newnode->left_child = left_child;
	newnode->right_sibling = right_sibling;
	newnode->description =newdescription;
	return(newnode);
}

void ajouter_dernier_fils(struct noeud_lcrs* pere,struct noeud_lcrs* fils){
	if(pere->left_child==NULL)pere->left_child=fils;
	else{
		struct noeud_lcrs* child=pere->left_child;
		while(child->right_sibling)child=child->right_sibling;
		child->right_sibling=fils;
	}
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
	fprintf(f,"\nnode%d [%s]",*j, tree->description);
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
				current_chilid=current_chilid->right_sibling;
			}
			}
		}

void inserer_type() {
	strcpy(type, yytext);
}

char* concatener(char*a,char*b){
		char*cat=(char*)malloc(sizeof(char)*(1+strlen(a)+strlen(b)));
		strcat(cat,a);
		strcat(cat,b);
		return cat;
	}
	
struct noeud_lcrs* get_last_sibling(struct noeud_lcrs* tree){
	if(tree->right_sibling)return get_last_sibling(tree->right_sibling);
	return tree;
}

void yyerror(const char *msg) {
    fprintf(stderr, "Erreur de Syntax: %s\n", msg);
    fprintf(stderr, "Le dernier lexème lue est '%s'\n", yytext);
    fprintf(stderr, "L'erreur est apparue dans la ligne %d, column \n", yylineno+1 );
}
