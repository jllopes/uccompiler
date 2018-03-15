lex uccompiler.l
clang-3.8 -Wall -Wno-unused-function -o uccompiler lex.yy.c
zip uccompiler.zip uccompiler.l