%{
    #include <stdio.h>
    int yylex(void);
    void yyerror (char *s);
%}


%union{
    char* token;
}

%token <token> CHAR ELSE WHILE IF INT SHORT DOUBLE RETURN VOID AND OR BITWISEAND BITWISEOR BITWISEXOR MUL COMMA DIV EQ NE GE GT LE LT ASSIGN NOT LBRACE LPAR RBRACE RPAR MINUS PLUS MOD SEMI RESERVED ID INTLIT CHRLIT INVCHRLIT UNTCHRLIT REALLIT

%nonassoc IFPREC
%nonassoc IFELSE
%left COMMA
%right ASSIGN
%left OR
%left AND
%left EQ NE
%left GT GE LT LE
%left MINUS PLUS
%left DIV MOD
%right NOT 
%right UNARY
%left LPAR

%%
Program: Start                                                                  

Start: FunctionDefinition StartAux
     | FunctionDeclaration StartAux
     | Declaration StartAux
;

StartAux: FunctionDefinition StartAux
        | FunctionDeclaration StartAux
        | Declaration StartAux
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

ParameterListAux: COMMA ParameterDeclaration ParameterListAux
                |
;

ParameterDeclaration: TypeSpec ID
                    | TypeSpec
;

Declaration: TypeSpec Declarator DeclarationAux SEMI;

DeclarationAux: COMMA Declarator DeclarationAux
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
         | IF LPAR Expression RPAR Statement
         | IF LPAR Expression RPAR Statement ELSE Statement
         | WHILE LPAR Expression RPAR Statement
         | RETURN Expression SEMI
         | RETURN SEMI
;

StatementAux: Statement StatementAux
            |
;

Expression: Expression ExpressionAux Expression
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

ExpressionAux: ASSIGN
             | COMMA
             | PLUS
             | MINUS
             | MUL
             | DIV
             | MOD
             | OR
             | AND
             | BITWISEAND
             | BITWISEOR
             | BITWISEXOR
             | EQ
             | NE
             | LE
             | GE
             | LT
             | GT
;

%%