# C_to_DOT_compiler
to run a simple test, open terminal in **/Projet/** folder
```bash
for file in ./Tests/done
do
  make -f Makefile "FILE=$file"
done
```
Seules les fichiers suivantes se compilent correctement 

add.c
compteur.c
cond.c
div.c
done.txt
mul.c
neg.c
sub.c
tableaux.c

Si il nous reste le temps on peut faire un traitement similaire pour que les autres se compilent correctement.
