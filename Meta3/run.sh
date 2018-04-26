lex uccompiler.l
yacc -d -v uccompiler.y
clang-3.8 -Wall -Wno-unused-function -g -o uccompiler y.tab.c lex.yy.c tree.c sym_table.c -ll -ly
zip uccompiler.zip uccompiler.l uccompiler.y tree.c tree.h sym_table.c sym_table.h
./uccompiler < test_enunciado.uc