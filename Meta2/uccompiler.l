/*
João Luís Gaspar Lopes
Rúben Telmo Domingues Leal
*/
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "y.tab.h"
int line = 1, column = 1;
int comment_line, comment_column;
int flag_lexical = 0, flag_syntax = 0, flag_error = 0, flag_tree = 0;
%}
%X MULTICOMMENT
CHAR "char"
ELSE "else"
WHILE "while"
IF "if"
INT "int"
SHORT "short"
DOUBLE "double"
RETURN "return"
VOID "void"
AND "&&"
OR "||"
BITWISEAND "&"
BITWISEOR "|"
BITWISEXOR "^"
MUL "*"
COMMA ","
DIV "/"
EQ "=="
NE "!="
GE ">="
GT ">"
LE "<="
LT "<"
ASSIGN "="
NOT "!"
LBRACE "{"
LPAR "("
RBRACE "}"
RPAR ")"
MINUS "-"
PLUS "+"
MOD "%"
SEMI ";"

RESERVED "auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"inline"|"long"|"register"|"restrict"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"_Bool"|"_Complex"|"_Imaginary"|"["|"]"|"--"|"++"

ID ([a-zA-Z_])([a-zA-Z0-9_])*

INTLIT [0-9]+

CHRLIT 			\'([^\n\r\'\\]|(\\(n|t|\\|\'|\"|[0-7]{1,3})))\'
INVCHRLIT		\'([^\n\r\'\\]*|(\\[^\n\r]))*\'
UNTCHRLIT		\'([^\n\r\'\\]|\\([^\n\r]))*(\\)?

REALLIT (([0-9]+)"."([0-9]+)?([eE][+-]?[0-9]+)?)|"."[0-9]+([eE][+-]?[0-9]+)?|[0-9]+([eE][+-]?[0-9]+)


/*...definições...*/
%%
"/*"								{BEGIN MULTICOMMENT; comment_line = line; comment_column = column; column+=yyleng;}
	<MULTICOMMENT>\n|\r|\r\n 		{line++; column = 1;}
	<MULTICOMMENT><<EOF>>			{printf("Line %d, col %d: unterminated comment\n", comment_line, comment_column); column++; BEGIN 0;}
	<MULTICOMMENT>"*/"				{column+=yyleng; BEGIN 0;}
	<MULTICOMMENT>.					{column+=yyleng;}
\n|\r|\r\n							{line++; column=1;}
\t|" "								{column++;}
<<EOF>>								{column++; return 0;}
"//"[^\n\r]*						{column+=yyleng;}
{RESERVED}							{if(flag_lexical != 0){printf("RESERVED(%s)\n",yytext);} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return RESERVED;};}
{CHAR}								{if(flag_lexical != 0){printf("CHAR\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return CHAR;};}
{ELSE}								{if(flag_lexical != 0){printf("ELSE\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return ELSE;};}
{WHILE}								{if(flag_lexical != 0){printf("WHILE\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return WHILE;};}
{IF}								{if(flag_lexical != 0){printf("IF\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return IF;};}
{INT}								{if(flag_lexical != 0){printf("INT\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return INT;};}
{SHORT}								{if(flag_lexical != 0){printf("SHORT\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return SHORT;};}
{DOUBLE}							{if(flag_lexical != 0){printf("DOUBLE\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return DOUBLE;};}
{RETURN}							{if(flag_lexical != 0){printf("RETURN\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return RETURN;};}
{VOID} 								{if(flag_lexical != 0){printf("VOID\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return VOID;};}
{BITWISEAND} 						{if(flag_lexical != 0){printf("BITWISEAND\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return BITWISEAND;};}
{BITWISEOR} 						{if(flag_lexical != 0){printf("BITWISEOR\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return BITWISEOR;};}
{BITWISEXOR} 						{if(flag_lexical != 0){printf("BITWISEXOR\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return BITWISEXOR;};}
{AND} 								{if(flag_lexical != 0){printf("AND\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return AND;};}
{OR} 								{if(flag_lexical != 0){printf("OR\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return OR;};}
{ASSIGN} 							{if(flag_lexical != 0){printf("ASSIGN\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return ASSIGN;};}
{NOT} 								{if(flag_lexical != 0){printf("NOT\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return NOT;};}
{MUL} 								{if(flag_lexical != 0){printf("MUL\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return MUL;};}
{COMMA} 							{if(flag_lexical != 0){printf("COMMA\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return COMMA;};}
{DIV} 								{if(flag_lexical != 0){printf("DIV\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return DIV;};}
{EQ} 								{if(flag_lexical != 0){printf("EQ\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return EQ;};}
{NE} 								{if(flag_lexical != 0){printf("NE\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return NE;};}
{GE} 								{if(flag_lexical != 0){printf("GE\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return GE;};}
{GT} 								{if(flag_lexical != 0){printf("GT\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return GT;};}
{LE} 								{if(flag_lexical != 0){printf("LE\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return LE;};}
{LT} 								{if(flag_lexical != 0){printf("LT\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return LT;};}
{LBRACE} 							{if(flag_lexical != 0){printf("LBRACE\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return LBRACE;};}
{LPAR} 								{if(flag_lexical != 0){printf("LPAR\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return LPAR;};}
{RBRACE} 							{if(flag_lexical != 0){printf("RBRACE\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return RBRACE;};}
{RPAR} 								{if(flag_lexical != 0){printf("RPAR\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return RPAR;};}
{MINUS} 							{if(flag_lexical != 0){printf("MINUS\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return MINUS;};}
{PLUS} 								{if(flag_lexical != 0){printf("PLUS\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return PLUS;};}
{MOD} 								{if(flag_lexical != 0){printf("MOD\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return MOD;};}
{SEMI} 								{if(flag_lexical != 0){printf("SEMI\n");} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return SEMI;};}
{CHRLIT} 							{if(flag_lexical != 0){printf("CHRLIT(%s)\n",yytext);} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return CHRLIT;};}
{UNTCHRLIT}							{printf("Line %d, col %d: unterminated char constant\n",line,column); column+=yyleng;}
{INVCHRLIT}							{printf("Line %d, col %d: invalid char constant (%s)\n",line,column,yytext); column+=yyleng;}
{INTLIT} 							{if(flag_lexical != 0){printf("INTLIT(%s)\n",yytext);} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return INTLIT;};}
{ID}								{if(flag_lexical != 0){printf("ID(%s)\n",yytext);} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return ID;};}

{REALLIT}							{if(flag_lexical != 0){printf("REALLIT(%s)\n",yytext);} column+=yyleng; if(flag_syntax != 0){yylval.token = (char*)strdup(yytext); return REALLIT;};}

.									{printf("Line %d, col %d: illegal character (%c)\n",line,column,yytext[0]); column+=yyleng;}
%%

int main(int argc, char **argv){
	if (argc > 1){
		if(strcmp(argv[1], "-l") == 0){
			flag_lexical = 1;
			yylex();
		}
		else if(strcmp(argv[1], "-t") == 0){
			flag_tree = 1;
			flag_syntax = 1;
			yyparse();
		}
	}
	else{
		flag_syntax = 1;	
		yyparse();
	}
	if(flag_error == 0 && flag_tree){
		print_tree(root, 0);
	}
	return 0;
}

int yywrap(){
	return 1;
}

void yyerror(char *s){
	//flag_error = 1;
	printf("Line %d, col %d: %s: %s\n", line, (int)(column-yyleng), s, yytext);
}
