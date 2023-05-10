all: a.out
	$ echo "\n\n\n";clear;cat $A| ./a.out;echo "\n\n\n"
	$ rm -r y.tab.c y.tab.h y.output lex.yy.c
a.out: y.tab.c lex.yy.c
	$ gcc  y.tab.c

lex.yy.c:lex.l
	$ lex ./src/LexAnalyser.l
	
	
y.output y.tab.c y.tab.h:./src/Parseur.y
	$ yacc -v -d ./src/Parseur.y

clean:y.tab.c y.output lex.yy.c
	$ rm -r y.tab.c y.output lex.yy.c
