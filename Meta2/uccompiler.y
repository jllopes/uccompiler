%{
    #include <stdio.h>
    int yylex(void);
    void yyerror (char *s);
%}


%union{
    char* token;
}

%token <token> CHAR ELSE WHILE IF INT SHORT DOUBLE RETURN VOID AND OR BITWISEAND BITWISEOR BITWISEXOR MUL COMMA DIV EQ NE GE GT LE LT ASSIGN NOT LBRACE LPAR RBRACE RPAR MINUS PLUS MOD SEMI RESERVED ID INTLIT CHRLIT INVCHRLIT UNTCHRLIT REALLIT


%left COMMA
%right ASSIGN
%left OR
%left AND
%left BITWISEOR
%left BITWISEXOR
%left BITWISEAND
%left EQ NE
%left GT GE LT LE
%left MINUS PLUS
%left MUL DIV MOD
%right NOT 

%nonassoc IFPREC
%nonassoc ELSE
%%
Program: Start                                                                  

Start: FunctionDefinition StartAux
     | FunctionDeclaration StartAux
     | Declaration StartAux
;

StartAux: StartAux FunctionDefinition
        | StartAux FunctionDeclaration
        | StartAux Declaration
        |
;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody;

FunctionBody: LBRACE DeclarationsAndStatements RBRACE
            | LBRACE RBRACE
;

DeclarationsAndStatements: Statement DeclarationsAndStatements
                         | Declaration DeclarationsAndStatements
                         | Statement
                         | Declaration
;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI;

FunctionDeclarator: ID LPAR ParameterList RPAR;

ParameterList: ParameterDeclaration ParameterListAux;

ParameterListAux: ParameterListAux COMMA ParameterDeclaration
                |
;

ParameterDeclaration: TypeSpec ID
                    | TypeSpec
;

Declaration: TypeSpec Declarator DeclarationAux SEMI;

DeclarationAux: DeclarationAux COMMA Declarator
              | 
;

TypeSpec: CHAR
        | INT
        | VOID
        | SHORT
        | DOUBLE
;

Declarator: ID
          | ID ASSIGN Expression
;

Statement: Expression SEMI
         | SEMI
         | LBRACE StatementAux RBRACE
         | IF LPAR Expression RPAR Statement %prec IFPREC
         | IF LPAR Expression RPAR Statement ELSE Statement
         | WHILE LPAR Expression RPAR Statement 
         | RETURN Expression SEMI
         | RETURN SEMI
;

StatementAux: StatementAux Statement
            |
;

Expression: Expression PLUS Expression
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
          | ID LPAR Expression RPAR
          | ID LPAR RPAR
          | ID
          | INTLIT
          | CHRLIT
          | REALLIT
          | LPAR Expression RPAR
;
%%