output.dot: mycompiler
	$ cat $A| ./mycompiler
	#$ rm -r y.tab.c y.tab.h y.output lex.yy.c result 
	
mycompiler: y.tab.c lex.yy.c
	$ clear;
	$ gcc  y.tab.c -o mycompiler

lex.yy.c:ANSI-C.l
	$ lex ANSI-C.l
	
y.tab.c: miniC.y
	$ yacc -v -d miniC.y 
	
