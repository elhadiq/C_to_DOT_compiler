result/ouput.pdf:ouput.dot
	$ rm -r y.tab.c y.tab.h y.output lex.yy.c  ouput.dot nohup.out
	$ nohup google-chrome result/output.pdf &
	
ouput.dot: mycompiler
	$ cat $A| ./mycompiler
	$ rm -r y.tab.c y.tab.h y.output lex.yy.c
mycompiler: y.tab.c lex.yy.c
	$ clear;
	$ gcc  y.tab.c -o mycompiler

lex.yy.c:../final/lexer.l
	$ lex ../final/lexer.l
	
y.output y.tab.c y.tab.h: ../final/parser.y
	$ yacc -v -d ../final/parser.y

clean:y.tab.c y.tab.h y.output lex.yy.c  ouput.dot nohup.out
	$ rm -r y.tab.c y.tab.h y.output lex.yy.c  ouput.dot nohup.out mycompiler
