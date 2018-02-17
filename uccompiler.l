%{
int line = 1, column = 1;
int comment_line, comment_column;
int flag_lexical = 0;
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

CHR2 ([^\n\'\\]|(\\(n|t|\\|\'|\"|[0-7]{1,3})))
CHRLIT 			\'([^\n\'\\]|(\\(n|t|\\|\'|\"|[0-7]{1,3})))\'
INVCHRLIT		(\'({CHR2}{CHR2}+)\')|(\\(.)*)\'?
UNTCHRLIT		\'{CHR2}+

REALLIT (([0-9]+)"."([0-9]+)?([eE][+-]?[0-9]+)?)|"."[0-9]+([eE][+-]?[0-9]+)?|[0-9]+([eE][+-]?[0-9]+)


/*...definições...*/
%%
"/*"					{BEGIN MULTICOMMENT; comment_line = line; comment_column = column; column+=yyleng;}
	<MULTICOMMENT>\n|\r|\r\n 		{line++; column = 1;}
	<MULTICOMMENT><<EOF>>	{printf("Line %d, col %d: unterminated comment\n", comment_line, comment_column); BEGIN 0;}
	<MULTICOMMENT>"*/"	{column+=yyleng; BEGIN 0;}
	<MULTICOMMENT>.		{column+=yyleng;}
\n|\r {line++; column=1;}
\t|" "	{column++;}
"//"[^\n\r]*		{column+=yyleng;}
{RESERVED}	{if(flag_lexical != 0){printf("RESERVED(%s)\n",yytext);} column+=yyleng;}
{CHAR}	{if(flag_lexical != 0){printf("CHAR\n");} column+=yyleng;}
{ELSE}	{if(flag_lexical != 0){printf("ELSE\n");} column+=yyleng;}
{WHILE}	{if(flag_lexical != 0){printf("WHILE\n");} column+=yyleng;}
{IF}	{if(flag_lexical != 0){printf("IF\n");} column+=yyleng;}
{INT}	{if(flag_lexical != 0){printf("INT\n");} column+=yyleng;}
{SHORT}	{if(flag_lexical != 0){printf("SHORT\n");} column+=yyleng;}
{DOUBLE}	{if(flag_lexical != 0){printf("DOUBLE\n");} column+=yyleng;}
{RETURN}	{if(flag_lexical != 0){printf("RETURN\n");} column+=yyleng;}
{VOID} {if(flag_lexical != 0){printf("VOID\n");} column+=yyleng;}
{BITWISEAND} {if(flag_lexical != 0){printf("BITWISEAND\n");} column+=yyleng;}
{BITWISEOR} {if(flag_lexical != 0){printf("BITWISEOR\n");} column+=yyleng;}
{BITWISEXOR} {if(flag_lexical != 0){printf("BITWISEXOR\n");} column+=yyleng;}
{AND} {if(flag_lexical != 0){printf("AND\n");} column+=yyleng;}
{OR} {if(flag_lexical != 0){printf("OR\n");} column+=yyleng;}
{ASSIGN} {if(flag_lexical != 0){printf("ASSIGN\n");} column+=yyleng;}
{NOT} {if(flag_lexical != 0){printf("NOT\n");} column+=yyleng;}
{MUL} {if(flag_lexical != 0){printf("MUL\n");} column+=yyleng;}
{COMMA} {if(flag_lexical != 0){printf("COMMA\n");} column+=yyleng;}
{DIV} {if(flag_lexical != 0){printf("DIV\n");} column+=yyleng;}
{EQ} {if(flag_lexical != 0){printf("EQ\n");} column+=yyleng;}
{NE} {if(flag_lexical != 0){printf("NE\n");} column+=yyleng;}
{GE} {if(flag_lexical != 0){printf("GE\n");} column+=yyleng;}
{GT} {if(flag_lexical != 0){printf("GT\n");} column+=yyleng;}
{LE} {if(flag_lexical != 0){printf("LE\n");} column+=yyleng;}
{LT} {if(flag_lexical != 0){printf("LT\n");} column+=yyleng;}
{LBRACE} {if(flag_lexical != 0){printf("LBRACE\n");} column+=yyleng;}
{LPAR} {if(flag_lexical != 0){printf("LPAR\n");} column+=yyleng;}
{RBRACE} {if(flag_lexical != 0){printf("RBRACE\n");} column+=yyleng;}
{RPAR} {if(flag_lexical != 0){printf("RPAR\n");} column+=yyleng;}
{MINUS} {if(flag_lexical != 0){printf("MINUS\n");} column+=yyleng;}
{PLUS} {if(flag_lexical != 0){printf("PLUS\n");} column+=yyleng;}
{MOD} {if(flag_lexical != 0){printf("MOD\n");} column+=yyleng;}
{SEMI} {if(flag_lexical != 0){printf("SEMI\n");} column+=yyleng;}
{CHRLIT} {if(flag_lexical != 0){printf("CHRLIT(%s)\n",yytext);} column+=yyleng;}

{INVCHRLIT}	{printf("Line %d, col %d: invalid char constant (%s)\n",line,column,yytext);}
{UNTCHRLIT}	{printf("Line %d, col %d: unterminated char constant\n",line,column);}

{INTLIT} {if(flag_lexical != 0){printf("INTLIT(%s)\n",yytext);} column+=yyleng;}
{ID} {if(flag_lexical != 0){printf("ID(%s)\n",yytext);} column+=yyleng;}

{REALLIT}	{if(flag_lexical != 0){printf("REALLIT(%s)\n",yytext);} column+=yyleng;}

.	{printf("Line %d, col %d: illegal character (%c)\n",line,column,yytext[0]); column++;}
%%

int main(int argc, char **argv){
	if (argc > 1){
		if(strcmp(argv[1], "-l") == 0){
			flag_lexical = 1;
		}
		else{
			flag_lexical = 0;
		}
	}
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}