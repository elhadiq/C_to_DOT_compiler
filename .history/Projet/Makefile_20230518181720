output.dot: mycompiler
	$ cat $A| ./mycompiler
	#$ rm -r y.tab.c y.tab.h y.output lex.yy.c result 
	
mycompiler: y.tab.c lex.yy.c
	$ clear;
	$ gcc  y.tab.c -o mycompiler

lex.yy.c:lexer.l
	$ lex lexer.l
	
y.tab.c: parser.y
	$ yacc -v -d parser.y 
	
