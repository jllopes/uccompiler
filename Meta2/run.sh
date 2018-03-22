lex uccompiler.l
yacc -d uccompiler.y
clang-3.8 -Wall -Wno-unused-function -g -o uccompiler y.tab.c lex.yy.c -ll -ly
zip uccompiler.zip uccompiler.l uccompiler.y