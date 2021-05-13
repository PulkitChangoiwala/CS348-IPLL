parser: parser.tab.c lex.yy.c
	gcc parser.tab.c lex.yy.c -o parser

parser.tab.c: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

clean: 
	rm parser.tab.h
	rm parser.tab.c
	rm lex.yy.c

clean-publish: 
	rm parser.tab.* lex.yy.c parser