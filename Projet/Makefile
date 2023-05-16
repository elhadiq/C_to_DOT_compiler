output.dot: mycompiler
	$ cat $A| ./mycompiler>>$A.reslt
	$ rm -r y.tab.c y.tab.h y.output lex.yy.c
	
mycompiler: y.tab.c lex.yy.c
	$ clear;
	$ gcc  y.tab.c -o mycompiler

lex.yy.c:lexer.l
	$ lex lexer.l
	
y.tab.c: parser.y
	$ yacc -v -d parser.y 
	
clean: lex.yy.c mycompiler y.tab.c y.tab.h y.output
	$ rm -r lex.yy.c y.tab.c y.tab.h y.output
