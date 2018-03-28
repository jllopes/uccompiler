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
Program: Start                                                                  {root = create_node("Program", NULL);
                                                                                insert_child(root,$1);}
;                                                                                                          

Start: FunctionDefinition StartAux                                              {$$ = create_node("FuncDefinition", NULL);    insert_child($$, $1);}       
     | FunctionDeclaration StartAux                                             {$$ = create_node("FuncDeclaration", NULL); insert_child($$, $1);}
     | Declaration StartAux                                                     {$$ = create_node("Declaration", NULL); insert_child($$, $1);}
;   

StartAux: StartAux FunctionDefinition                                           {$$ = create_node("FuncDefinition", NULL); insert_child($$, $2);}
        | StartAux FunctionDeclaration                                          {$$ = create_node("FuncDeclaration", NULL); insert_child($$, $2);}
        | StartAux Declaration                                                  {$$ = create_node("Declaration", NULL); insert_child($$, $2);}
        |
;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody                    {$$ = $1; insert_brother($$, $2); insert_brother($$, $3);}
;

FunctionBody: LBRACE RBRACE                                                     {$$ = create_node("FuncBody", NULL);}
            | LBRACE DecAndStatDeclaration DecAndStatStatement RBRACE           {$$ = create_node("FuncBody", NULL); insert_child($$, $2); insert_brother($2,$3);}
            | LBRACE DecAndStatDeclaration RBRACE                               {$$ = create_node("FuncBody", NULL); insert_child($$, $2);}
            | LBRACE DecAndStatStatement RBRACE                                 {$$ = create_node("FuncBody", NULL); insert_child($$, $2);}
;

DecAndStatDeclaration: DecAndStatDeclaration Declaration                        {$$ = $1; insert_brother($$, $2);}
                     | Declaration                                              {$$ = $1;}
;

DecAndStatStatement: DecAndStatStatement Statement                              {$$ = $1; insert_brother($$, $2);}
                   | Statement                                                  {$$ = $1;}
;

StatementError: Statement                                                       {$$ = $1;}
              | error SEMI                                                      {$$ = NULL;}
;

StatementErrorAux: StatementErrorAux StatementError                             {if($1 || $2 != NULL){$$ = create_node("StatList", NULL); if($1 != NULL){insert_child($$, $1); if($2 != NULL){insert_brother($1, $2);}}} else{if($2 != NULL){insert_child($$, $2);}}}
                 | StatementError                                               {if($1 != NULL){$$ = $1;}}
;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI                           {$$ = $1; insert_brother($$, $2);}
;

FunctionDeclarator: ID LPAR ParameterList RPAR                                  {$$ = create_node("Id",$1); insert_brother($$, $3);}
;

ParameterList: ParameterDeclaration ParameterListAux                            {$$ = create_node("ParamList", NULL); insert_child($$, $1); insert_brother($1, $2);}
;

ParameterListAux: COMMA ParameterDeclaration ParameterListAux                   {$$ = $2; insert_brother($$, $3);}
                |                                                               {$$ = NULL;}
;

ParameterDeclaration: TypeSpec ID                                               {$$ = create_node("ParamDeclaration", NULL); insert_child($$, $1); insert_brother($1, create_node("Id",$2));}
                    | TypeSpec                                                  {$$ = create_node("ParamDeclaration", NULL); insert_child($$, $1);}
;

Declaration: TypeSpec DeclarationAux SEMI                                       {$$ = $1; insert_brother($$, $2);}
           | error SEMI                                                         {$$ = NULL;}
;

DeclarationAux: DeclarationAux COMMA Declarator                                 {$$ = $1; insert_brother($$, $3);}
              | Declarator                                                      {$$ = $1;}
;

TypeSpec: CHAR                                                                  {$$ = create_node("Char", NULL);}
        | INT                                                                   {$$ = create_node("Int", NULL);}
        | VOID                                                                  {$$ = create_node("Void", NULL);}
        | SHORT                                                                 {$$ = create_node("Short", NULL);}
        | DOUBLE                                                                {$$ = create_node("Double", NULL);}
;

Declarator: ID ASSIGN ExpressionAux                                             {$$ = create_node("Id", $1); insert_brother($$, $3);}
          | ID                                                                  {$$ = create_node("Id", $1);}
;

Statement: ExpressionAux SEMI                                                   {$$ = $1;}
         | SEMI                                                                 {$$ = NULL;}
         | LBRACE StatementErrorAux RBRACE                                      {$$ = $1;}
         | LBRACE RBRACE                                                        {$$ = NULL;}
         | IF LPAR ExpressionAux RPAR StatementError %prec IFPREC               {$$ = create_node("If", NULL); insert_child($$, $3); insert_brother($3, $5); insert_brother($3, NULL);} /* São obrigatórios 3 filhos, no caso de ser só if o terceiro será NULL */
         | IF LPAR ExpressionAux RPAR StatementError ELSE StatementError        {$$ = create_node("If", NULL); insert_child($$, $3); insert_brother($3, $5); insert_brother($3, $7);}
         | WHILE LPAR ExpressionAux RPAR StatementError                         {$$ = create_node("While", NULL); insert_child($$, $3); insert_brother($3, $5);}
         | RETURN ExpressionAux SEMI                                            {$$ = create_node("Return", NULL); insert_child($$, $2);}
         | RETURN SEMI                                                          {$$ = create_node("Return", NULL); insert_child($$, NULL);}
         | LBRACE error RBRACE                                                  {$$ = NULL;}
;   

Expression: Expression ASSIGN Expression                                        {$$ = create_node("Store", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression PLUS Expression                                          {$$ = create_node("Add", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression MINUS Expression                                         {$$ = create_node("Sub", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression MUL Expression                                           {$$ = create_node("Mul", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression DIV Expression                                           {$$ = create_node("Div", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression MOD Expression                                           {$$ = create_node("Mod", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression OR Expression                                            {$$ = create_node("Or", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression AND Expression                                           {$$ = create_node("And", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression BITWISEAND Expression                                    {$$ = create_node("BitWiseAnd", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression BITWISEOR Expression                                     {$$ = create_node("BitWiseOr", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression BITWISEXOR Expression                                    {$$ = create_node("BitWiseXor", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression EQ Expression                                            {$$ = create_node("Eq", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression NE Expression                                            {$$ = create_node("Ne", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression LE Expression                                            {$$ = create_node("Le", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression GE Expression                                            {$$ = create_node("Ge", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression LT Expression                                            {$$ = create_node("Lt", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | Expression GT Expression                                            {$$ = create_node("Gt", NULL); insert_child($$, $1); insert_brother($1, $3);}
          | PLUS Expression                                                     {$$ = create_node("Plus", NULL); insert_child($$, $2);}
          | MINUS Expression                                                    {$$ = create_node("Minus", NULL); insert_child($$, $2);}
          | NOT Expression                                                      {$$ = create_node("Not", NULL); insert_child($$, $2);}
          | ID LPAR Expression ExpressionSecAux RPAR                            {$$ = create_node("Call", $1); insert_child($$, $3); insert_brother($3, $4);}
          | ID LPAR RPAR                                                        {$$ = create_node("Call", $1); insert_child($$, NULL);} /* Tem de ter pelo menos um filho */
          | ID                                                                  {$$ = create_node("Id", $1);}
          | INTLIT                                                              {$$ = create_node("IntLit", $1);}
          | CHRLIT                                                              {$$ = create_node("ChrLit", $1);}
          | REALLIT                                                             {$$ = create_node("RealLit", $1);}
          | LPAR ExpressionAux RPAR                                             {$$ = $2;}
          | LPAR error RPAR                                                     {$$ = NULL;}
          | ID LPAR error RPAR                                                  {$$ = NULL;}
;

ExpressionAux: ExpressionAux COMMA Expression                                   {$$ = create_node("Comma", NULL); insert_child($$, $1); insert_brother($1, $3);}
             | Expression                                                       {$$ = $1;}
;

ExpressionSecAux: ExpressionSecAux COMMA Expression                             {$$ = $1; insert_brother($1, $3);}
                |                                                               {$$ = NULL;}
;

%%