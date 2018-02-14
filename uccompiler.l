
INTLIT [0-9]+
ID ([a-zA-Z_])([a-zA-Z0-9_])*
CHRLIT [^\n"'"]|\'((\\(n|t|\\|\'\"))|([0-7]{1,3}))\'

/*...definições...*/
%%
{CHRLIT} {printf("CHRLIT\n");}
{INTLIT} {printf("INTLIT!");}
{ID}+ {printf("ID!");}
%%

int main(){

	yylex();

	return 0;
}

int yywrap(){
	return 1;
}