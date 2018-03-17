%{
    #include <stdio.h>
    int yylex(void);
    void yyerror (const char *s);
%}


%union{
    char* token;
}

%token <token> CHAR ELSE WHILE IF INT SHORT DOUBLE RETURN VOID AND OR BITWISEAND BITWISEOR BITWISEXOR MUL COMMA DIV EQ NE GE GT LE LT ASSIGN NOT LBRACE RBRACE RPAR MINUS PLUS MOD SEMI RESERVED ID INTLIT CHRLIT INVCHRLIT UNTCHRLIT REALLIT

%left 

%%
Program: Start;

Start: FunctionDefinition FunctionsAndDeclarations
     | FunctionDeclaration FunctionsAndDeclarations
     | Declaration FunctionsAndDeclarations
;

FunctionsAndDeclarations: FunctionDefinition FunctionsAndDeclarations
                        | FunctionDeclaration FunctionsAndDeclarations
                        | Declaration FunctionsAndDeclarations
                        |
;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody;

TypeSpec: CHRLIT 
        | INTLIT 
        | VOID 
        | SHORT 
        | DOUBLE; 

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI;

FunctionDeclarator: ID LPAR ParameterList RPAR;

ParameterList: ParameterDeclaration ParameterListRep;

ParameterListRep: COMMA ParameterDeclaration ParameterListRep
                | 
;

ParameterDeclaration: TypeSpec
                    | TypeSpec ID
;

FunctionBody: LBRACE RBRACE
            | LBRACE DeclarationsAndStatements RBRACE
;

DeclarationsAndStatements: Statement DeclarationsAndStatements
                         | Declaration DeclarationsAndStatements 
                         | Statement 
                         | Declaration
;

Declaration: TypeSpec Declarator CommaDeclarator SEMI;

CommaDeclarator: COMMA Declarator CommaDeclarator
               |
;

Declarator: ID 
          | ID ASSIGN Expression;

Statement: Expr SEMI
         | SEMI
;

Statement: LBRACE StatementRep RBRACE;

Statement: IF LPAR Expression RPAR Statement;

Statement: WHILE LPAR Expression RPAR Statement;

Statement: RETURN Expression SEMI
         | RETURN SEMI
;

StatementRep: Statement StatementRep
            | 
;

Expression: Expression ASSIGN Expression
          | Expression COMMA Expression
          | Expression PLUS Expression 
          | Expression MINUS Expression 
          | Expression MUL Expression 
          | Expression DIV Expression 
          | Expression MOD Expression 
          | Expression OR Expression 
          | Expression AND Expression 
          | Expression BITWISEAND Expression 
          | Expression BITWISEOR Expression
          | Expression BITWISEXOR Expression 
          | Expression EQ Expression  
          | Expression NE Expression
          | Expression LE Expression 
          | Expression GE Expression 
          | Expression LT Expression  
          | Expression GT Expression 
          | PLUS Expression
          | MINUS Expression
          | NOT Expression
          | ID LPAR Expression ExpressionComma RPAR
          | ID LPAR RPAR
          | ID
          | INTLIT
          | CHRLIT
          | REALLIT
          | LPAR Expression RPAR
;

ExpressionComma: COMMA Expression
             |
;

%%

int main() {
    while(aux){
        yyparse();
    }
    return 0;
}