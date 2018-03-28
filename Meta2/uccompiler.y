/*
João Luís Gaspar Lopes
Rúben Telmo Domingues Leal
*/ 
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    int yylex(void);
    void yyerror (char *s);
%}


%union{
    char* token;
    struct Node *node;
}

%token <token> CHAR ELSE WHILE IF INT SHORT DOUBLE RETURN VOID AND OR BITWISEAND BITWISEOR BITWISEXOR MUL COMMA DIV EQ NE GE GT LE LT ASSIGN NOT LBRACE LPAR RBRACE RPAR MINUS PLUS MOD SEMI RESERVED ID INTLIT CHRLIT INVCHRLIT UNTCHRLIT REALLIT

%type <node> Program Start FunctionDefinition FunctionDeclaration Declaration StartAux TypeSpec FunctionDeclarator FunctionBody DecAndStatDeclaration DecAndStatStatement StatementError Statement StatementErrorAux ParameterList ParameterDeclaration ParameterListAux DeclarationAux Declarator ExpressionAux Expression ExpressionSecAux


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
Program: Start                                                                  {root = create_tree();
                                                                                insert_child(root,$1);}
;                                                                                                          

Start: FunctionDefinition StartAux                                              {$$ = create_node("FunctionDefinition", NULL);    insert_child($$, $1);}       
     | FunctionDeclaration StartAux                                             {$$ = create_node("FunctionDeclaration", NULL); insert_child($$, $1);}
     | Declaration StartAux                                                     {$$ = create_node("Declaration", NULL); insert_child($$, $1);}
;   

StartAux: StartAux FunctionDefinition                                           {$$ = create_node("FuncDefinition", NULL); insert_child($$, $2);}
        | StartAux FunctionDeclaration                                          {$$ = create_node("FunctionDeclaration", NULL); insert_child($$, $2);}
        | StartAux Declaration                                                  {$$ = create_node("Declaration", NULL); insert_child($$, $2);}
        |
;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody                    {$$ = create_node(); insert_brother($$, $2); insert_brother($$, $3);}
;

FunctionBody: LBRACE RBRACE                                                     {$$ = create_node("FuncBody"); insert_child($$, $1); insert_brother($1, $2);}
            | LBRACE DecAndStatDeclaration DecAndStatStatement RBRACE           {$$ = create_node; insert_brother($$, $2); insert_brother($$,$3);}
            | LBRACE DecAndStatDeclaration RBRACE                               {}
            | LBRACE DecAndStatStatement RBRACE                                 {}
;

DecAndStatDeclaration: DecAndStatDeclaration Declaration                        {}
                     | Declaration                                              {}
;

DecAndStatStatement: DecAndStatStatement StatementError                         {}
                   | StatementError                                             {}
;

StatementError: Statement                                                       {}
              | error SEMI                                                      {}
;

StatementErrorAux: StatementErrorAux StatementError                             {}
                 | StatementError                                               {}
;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI                           {}
;

FunctionDeclarator: ID LPAR ParameterList RPAR                                  {}
;

ParameterList: ParameterDeclaration ParameterListAux                            {}
;

ParameterListAux: ParameterListAux COMMA ParameterDeclaration                   {}
                |                                                               {}
;

ParameterDeclaration: TypeSpec ID                                               {}
                    | TypeSpec                                                  {}
;

Declaration: TypeSpec DeclarationAux SEMI                                       {}
           | error SEMI                                                         {}
;

DeclarationAux: DeclarationAux COMMA Declarator                                 {}
              | Declarator                                                      {}
;

TypeSpec: CHAR                                                                  {}
        | INT                                                                   {}
        | VOID                                                                  {}
        | SHORT                                                                 {}
        | DOUBLE                                                                {}
;

Declarator: ID ASSIGN ExpressionAux                                             {}
          | ID                                                                  {}
;

Statement: ExpressionAux SEMI                                                   {}
         | SEMI                                                                 {}
         | LBRACE StatementErrorAux RBRACE                                      {}
         | LBRACE RBRACE                                                        {}
         | IF LPAR ExpressionAux RPAR StatementError %prec IFPREC               {}
         | IF LPAR ExpressionAux RPAR StatementError ELSE StatementError        {}
         | WHILE LPAR ExpressionAux RPAR StatementError                         {}
         | RETURN ExpressionAux SEMI                                            {}
         | RETURN SEMI                                                          {}
         | LBRACE error RBRACE                                                  {}
;   

Expression: Expression ASSIGN Expression                                        {}
          | Expression PLUS Expression                                          {}
          | Expression MINUS Expression                                         {}
          | Expression MUL Expression                                           {}
          | Expression DIV Expression                                           {}
          | Expression MOD Expression                                           {}
          | Expression OR Expression                                            {}
          | Expression AND Expression                                           {}
          | Expression BITWISEAND Expression                                    {}
          | Expression BITWISEOR Expression                                     {}
          | Expression BITWISEXOR Expression                                    {}
          | Expression EQ Expression                                            {}
          | Expression NE Expression                                            {}
          | Expression LE Expression                                            {}
          | Expression GE Expression                                            {}
          | Expression LT Expression                                            {}
          | Expression GT Expression                                            {}
          | PLUS Expression                                                     {}
          | MINUS Expression                                                    {}
          | NOT Expression                                                      {}
          | ID LPAR Expression ExpressionSecAux RPAR                            {}
          | ID LPAR RPAR                                                        {}
          | ID                                                                  {}
          | INTLIT                                                              {}
          | CHRLIT                                                              {}
          | REALLIT                                                             {}
          | LPAR ExpressionAux RPAR                                             {}
          | LPAR error RPAR                                                     {}
          | ID LPAR error RPAR                                                  {}
;

ExpressionAux: ExpressionAux COMMA Expression                                   {}
             | Expression                                                       {}
;

ExpressionSecAux: ExpressionSecAux COMMA Expression                             {}
                |                                                               {}
;

%%