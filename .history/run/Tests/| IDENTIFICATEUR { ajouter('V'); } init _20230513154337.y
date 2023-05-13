| IDENTIFICATEUR { ajouter('V'); } init { 
	$1.nd = faire_noeud(NULL, NULL, $1.nom); 
	$$.nd = faire_noeud($1.nd, $3.nd, ":="); 
	sprintf(code3v[DOT_index++], "%s = %s\n", $1.nom, $3.nom);
}