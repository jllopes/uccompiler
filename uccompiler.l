%{
int line = 1, column = 1;
int lexical = 0;
%}

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

CHRLIT \'([^\n\']|(\\(n|t|\\|\'|\"))|([0-7]{1,3}))\'

REALLIT (([0-9]+)"."(([0-9]+)?([eE][+-]?[0-9]+)?))|((".")?[0-9]+([eE][+-]?[0-9]+))

/*...definições...*/
%%
\n|\r {line++; column=1;}
\t|" "	{column++;}
{RESERVED}	{printf("RESERVED(%s)\n",yytext); column+=yyleng;}
{CHAR}	{printf("CHAR\n"); column+=yyleng;}
{ELSE}	{printf("ELSE\n"); column+=yyleng;}
{WHILE}	{printf("WHILE\n"); column+=yyleng;}
{IF}	{printf("IF\n"); column+=yyleng;}
{INT}	{printf("INT\n"); column+=yyleng;}
{SHORT}	{printf("SHORT\n"); column+=yyleng;}
{DOUBLE}	{printf("DOUBLE\n"); column+=yyleng;}
{RETURN}	{printf("RETURN\n"); column+=yyleng;}
{VOID} {printf("VOID\n"); column+=yyleng;}
{BITWISEAND} {printf("BITWISEAND\n"); column+=yyleng;}
{BITWISEOR} {printf("BITWISEOR\n"); column+=yyleng;}
{BITWISEXOR} {printf("BITWISEXOR\n"); column+=yyleng;}
{AND} {printf("AND\n"); column+=yyleng;}
{OR} {printf("OR\n"); column+=yyleng;}
{ASSIGN} {printf("ASSIGN\n"); column+=yyleng;}
{NOT} {printf("NOT\n"); column+=yyleng;}
{MUL} {printf("MUL\n"); column+=yyleng;}
{COMMA} {printf("COMMA\n"); column+=yyleng;}
{DIV} {printf("DIV\n"); column+=yyleng;}
{EQ} {printf("EQ\n"); column+=yyleng;}
{NE} {printf("NE\n"); column+=yyleng;}
{GE} {printf("GE\n"); column+=yyleng;}
{GT} {printf("GT\n"); column+=yyleng;}
{LE} {printf("LE\n"); column+=yyleng;}
{LT} {printf("LT\n"); column+=yyleng;}
{LBRACE} {printf("LBRACE\n"); column+=yyleng;}
{LPAR} {printf("LPAR\n"); column+=yyleng;}
{RBRACE} {printf("RBRACE\n"); column+=yyleng;}
{RPAR} {printf("RPAR\n"); column+=yyleng;}
{MINUS} {printf("MINUS\n"); column+=yyleng;}
{PLUS} {printf("PLUS\n"); column+=yyleng;}
{MOD} {printf("MOD\n"); column+=yyleng;}
{SEMI} {printf("SEMI\n"); column+=yyleng;}
{CHRLIT} {printf("CHRLIT(%s)\n",yytext); column+=yyleng;}
{INTLIT} {printf("INTLIT(%s)\n",yytext); column+=yyleng;}
{ID} {printf("ID(%s)\n",yytext); column+=yyleng;}
{REALLIT}	{printf("REALLIT\n"); column+=yyleng;}
.	{printf("Line %d, col %d: illegal character (%s)\n",line,column,yytext);}
%%

int main(){
	yylex();
	return 0;
}

int yywrap(){
	return 1;
}