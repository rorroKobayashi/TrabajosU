yacc -vd grammar.y && lex lexer.l && gcc y.tab.c lex.yy.c -lfl -lm && ./a.out