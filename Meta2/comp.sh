lex mycalc.l
yacc -d mycalc.y
cc -o mycalc y.tab.c  lex.yy.c