result/ouput.pdf:ouput.dot
	$ mkdir -p result
	$ dot -Tpdf output.dot -o result/output.pdf
	$ nohup firefox result/output.pdf &
	
ouput.dot: a.out
	$ cat $A| ./a.out
	$ rm -r y.tab.c y.tab.h y.output lex.yy.c
a.out: y.tab.c lex.yy.c
	$ clear;
	$ gcc  y.tab.c

lex.yy.c:../final/lexer.l
	$ lex ../final/lexer.l
	
y.output y.tab.c y.tab.h: ../final/parser.y
	$ yacc -v -d ../final/parser.y

clean:y.tab.c y.tab.h y.output lex.yy.c  ouput.dot nohup.out
	$ rm -r y.tab.c y.tab.h y.output lex.yy.c  ouput.dot nohup.out
