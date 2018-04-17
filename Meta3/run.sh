lex uccompiler.l
yacc -d -v uccompiler.y
clang-3.8 -Wall -Wno-unused-function -g -o uccompiler y.tab.c lex.yy.c tree.c -ll -ly
zip uccompiler.zip uccompiler.l uccompiler.y tree.c tree.h