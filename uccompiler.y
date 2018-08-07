/*
João Luís Gaspar Lopes
Rúben Telmo Domingues Leal
*/ 
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    #include "sym_table.h"
    int yylex(void);
    void yyerror (char *s);
%}


%union{
    struct Token *token;
    struct Node *node;
}

%token <token> CHAR ELSE WHILE IF INT SHORT DOUBLE RETURN VOID AND OR BITWISEAND BITWISEOR BITWISEXOR MUL COMMA DIV EQ NE GE GT LE LT ASSIGN NOT LBRACE LPAR RBRACE RPAR MINUS PLUS MOD SEMI RESERVED ID INTLIT CHRLIT INVCHRLIT UNTCHRLIT REALLIT

%type <node> Program Start FunctionDefinition FunctionDeclaration Declaration StartAux TypeSpec FunctionDeclarator FunctionBody DeclarationsAndStatements Statement StatementError StatementErrorAux ParameterList ParameterDeclaration ParameterListAux DeclarationAux Declarator ExpressionAux Expression ExpressionSecAux


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
%nonassoc UNARY
%nonassoc IFPREC
%nonassoc ELSE
%%
Program: Start                                                                  {
                                                                                  root = create_node("Program", NULL, 0, 0);
                                                                                  insert_child(root,$1);
                                                                                }
;                                                                                                          

Start: FunctionDefinition StartAux                                              {
                                                                                  $$ = $1; 
                                                                                  insert_brother($$, $2);
                                                                                }       
     | FunctionDeclaration StartAux                                             {
                                                                                  $$ = $1; 
                                                                                  insert_brother($$, $2);
                                                                                }
     | Declaration StartAux                                                     {
                                                                                  if($1 != NULL) {
                                                                                    $$ = $1; 
                                                                                    insert_brother($$, $2);
                                                                                  } else {
                                                                                    $$=$2;
                                                                                  }
                                                                                }
;   

StartAux: StartAux FunctionDefinition                                           {
                                                                                  if($1 != NULL) {
                                                                                    $$ = $1; 
                                                                                    insert_brother($$, $2);
                                                                                  } else {
                                                                                    $$ = $2;
                                                                                  }
                                                                                }
        | StartAux FunctionDeclaration                                          {
                                                                                  if($1 != NULL) {
                                                                                    $$ = $1; 
                                                                                    insert_brother($$, $2);
                                                                                  } else {
                                                                                    $$ = $2;
                                                                                  }
                                                                                }
        | StartAux Declaration                                                  {
                                                                                  if($1 != NULL) {
                                                                                    $$ = $1; 
                                                                                    insert_brother($$, $2);
                                                                                  } else {
                                                                                    $$ = $2;
                                                                                  }
                                                                                }
        |                                                                       {$$ = NULL;}
;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody                    {
                                                                                  $$ = create_node("FuncDefinition", NULL, 0, 0); 
                                                                                  insert_child($$, $1); 
                                                                                  insert_child($$, $2); 
                                                                                  insert_child($$, $3);
                                                                                }
;

FunctionBody: LBRACE RBRACE                                                     {$$ = create_node("FuncBody", NULL, 0, 0);}
            | LBRACE DeclarationsAndStatements RBRACE                           {
                                                                                  $$ = create_node("FuncBody", NULL, 0, 0); 
                                                                                  if($2 != NULL) {
                                                                                    insert_child($$, $2);
                                                                                  }
                                                                                }
;

DeclarationsAndStatements: DeclarationsAndStatements Statement                  {
                                                                                  if($1 != NULL) {
                                                                                    $$ = $1; 
                                                                                    insert_brother($$,$2);
                                                                                  } else {
                                                                                    $$ = $2;
                                                                                  }
                                                                                }
                         | DeclarationsAndStatements Declaration                {
                                                                                  if($1 != NULL) {
                                                                                    $$ = $1; 
                                                                                    insert_brother($$,$2);
                                                                                  } else {
                                                                                    $$ = $2;
                                                                                  }
                                                                                }
                         | Statement                                            {$$=$1;}
                         | Declaration                                          {$$=$1;}
;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI                           {
                                                                                  $$ = create_node("FuncDeclaration", NULL, 0, 0);
                                                                                  insert_child($$, $1); 
                                                                                  insert_child($$, $2);
                                                                                }
;

FunctionDeclarator: ID LPAR ParameterList RPAR                                  {
                                                                                  $$ = create_node("Id",$1->id, $1->line, $1->column); 
                                                                                  insert_brother($$, $3);
                                                                                }
;

ParameterList: ParameterDeclaration ParameterListAux                            {
                                                                                  $$ = create_node("ParamList", NULL, 0, 0); 
                                                                                  insert_child($$, $1); 
                                                                                  insert_child($$, $2);
                                                                                }
;

ParameterListAux: COMMA ParameterDeclaration ParameterListAux                   {
                                                                                  $$ = $2; 
                                                                                  insert_brother($$, $3);
                                                                                }
                |                                                               {$$ = NULL;}
;

ParameterDeclaration: TypeSpec ID                                               {
                                                                                  $$ = create_node("ParamDeclaration", NULL, 0, 0); 
                                                                                  insert_child($$, $1); 
                                                                                  insert_child($$, create_node("Id",$2->id, $2->line, $2->column));
                                                                                }
                    | TypeSpec                                                  {
                                                                                  $$ = create_node("ParamDeclaration", NULL, 0, 0); 
                                                                                  insert_child($$, $1);
                                                                                }
;

Declaration: TypeSpec Declarator DeclarationAux SEMI                            {
                                                                                  $$ = $2; 
                                                                                  if($3 != NULL) {
                                                                                    insert_brother($$, $3);
                                                                                  } 
                                                                                  insert_first_child($$, $1);
                                                                                }
           | error SEMI                                                         {$$ = NULL;}
;

DeclarationAux: DeclarationAux COMMA Declarator                                 {
                                                                                  if($1 != NULL) {
                                                                                    $$ = $1; 
                                                                                    insert_brother($$, $3);
                                                                                  } else {
                                                                                    $$ = $3;
                                                                                  }
                                                                                }
              |                                                                 {$$ = NULL;}
;

TypeSpec: CHAR                                                                  {$$ = create_node("Char", NULL, $1->line, $1->column);}
        | INT                                                                   {$$ = create_node("Int", NULL, $1->line, $1->column);}
        | VOID                                                                  {$$ = create_node("Void", NULL, $1->line, $1->column);}
        | SHORT                                                                 {$$ = create_node("Short", NULL, $1->line, $1->column);}
        | DOUBLE                                                                {$$ = create_node("Double", NULL, $1->line, $1->column);}
;

Declarator: ID ASSIGN ExpressionAux                                             {
                                                                                  $$ = create_node("Declaration", NULL, 0, 0); 
                                                                                  insert_child($$,create_node("Id", $1->id, $1->line, $1->column)); 
                                                                                  insert_child($$, $3);}
          | ID                                                                  {
                                                                                  $$ = create_node("Declaration", NULL, 0, 0); 
                                                                                  insert_child($$, create_node("Id", $1->id, $1->line, $1->column));
                                                                                }
;

Statement: ExpressionAux SEMI                                                   {$$ = $1;}
         | SEMI                                                                 {$$ = NULL;}
         | LBRACE StatementErrorAux RBRACE                                      {
                                                                                  if($2 != NULL && $2->brother != NULL) {
                                                                                    $$ = create_node("StatList", NULL, 0, 0); 
                                                                                    insert_child($$, $2);
                                                                                  } else {
                                                                                    $$ = $2;
                                                                                  }
                                                                                }
         | LBRACE RBRACE                                                        {$$ = NULL;}
         | IF LPAR ExpressionAux RPAR StatementError %prec IFPREC               {
                                                                                  $$ = create_node("If", NULL, $1->line, $1->column); 
                                                                                  insert_child($$, $3); 
                                                                                  if($5 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else if($5 != NULL && $5->brother != NULL) {
                                                                                    insert_child($$, create_node("StatList", NULL, 0, 0)); 
                                                                                    insert_child($$->child->brother, $5);
                                                                                  } else {
                                                                                    insert_child($$, $5);
                                                                                  } 
                                                                                  insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                }
         | IF LPAR ExpressionAux RPAR StatementError ELSE StatementError        {
                                                                                  $$ = create_node("If", NULL, $1->line, $1->column); 
                                                                                  insert_child($$, $3); 
                                                                                  if($5 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else if($5 != NULL && $5->brother != NULL) {
                                                                                    insert_child($$, create_node("StatList", NULL, 0, 0)); 
                                                                                    insert_child($$->child->brother, $5);
                                                                                  } else{
                                                                                    insert_child($$, $5);
                                                                                  } if($7 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else if($7 != NULL && $7->brother != NULL) {
                                                                                    insert_child($$, create_node("StatList", NULL, 0, 0)); 
                                                                                    insert_child($$->child->brother->brother, $7);
                                                                                  } else{
                                                                                    insert_child($$, $7);
                                                                                  }
                                                                                }
         | WHILE LPAR ExpressionAux RPAR StatementError                         {
                                                                                  $$ = create_node("While", NULL, $1->line, $1->column); 
                                                                                  if($3!=NULL) {
                                                                                    insert_child($$, $3);
                                                                                  } else {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } if($5 != NULL) {
                                                                                    insert_child($$, $5);
                                                                                  } else {
                                                                                  insert_child($$, create_node("Null",NULL, 0, 0));
                                                                                  }
                                                                                }
         | RETURN ExpressionAux SEMI                                            {
                                                                                  $$ = create_node("Return", NULL, $1->line, $1->column);
                                                                                  insert_child($$, $2);
                                                                                }
         | RETURN SEMI                                                          {
                                                                                  $$ = create_node("Return", NULL, $1->line, $1->column); 
                                                                                  insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                }
         | LBRACE error RBRACE                                                  {$$ = NULL;}
;   

StatementErrorAux: StatementErrorAux StatementError                             {
                                                                                  if($1 != NULL) {
                                                                                    $$ = $1; 
                                                                                    insert_brother($$,$2);
                                                                                  } else {
                                                                                    $$ = $2;
                                                                                  }
                                                                                }
            | StatementError                                                    {$$ = $1;}
;

StatementError: Statement                                                       {$$ = $1;}
               | error SEMI                                                     {$$ = NULL;}
;

Expression: Expression ASSIGN Expression                                        {
                                                                                  $$ = create_node("Store", NULL, $2->line, $2->column);
                                                                                  if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } 
                                                                                  if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression PLUS Expression                                          {
                                                                                  $$ = create_node("Add", NULL, $2->line, $2->column); 
                                                                                  if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } 
                                                                                  if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression MINUS Expression                                         {
                                                                                  $$ = create_node("Sub", NULL, $2->line, $2->column);
                                                                                  if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression MUL Expression                                           {
                                                                                  $$ = create_node("Mul", NULL, $2->line, $2->column); 
                                                                                  if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression DIV Expression                                           {
                                                                                  $$ = create_node("Div", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression MOD Expression                                           {
                                                                                  $$ = create_node("Mod", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression OR Expression                                            {
                                                                                  $$ = create_node("Or", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression AND Expression                                           {
                                                                                  $$ = create_node("And", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression BITWISEAND Expression                                    {
                                                                                  $$ = create_node("BitWiseAnd", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression BITWISEOR Expression                                     {
                                                                                  $$ = create_node("BitWiseOr", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression BITWISEXOR Expression                                    {
                                                                                  $$ = create_node("BitWiseXor", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression EQ Expression                                            {
                                                                                  $$ = create_node("Eq", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression NE Expression                                            {
                                                                                  $$ = create_node("Ne", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression LE Expression                                            {
                                                                                  $$ = create_node("Le", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression GE Expression                                            {
                                                                                  $$ = create_node("Ge", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression LT Expression                                            {
                                                                                  $$ = create_node("Lt", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | Expression GT Expression                                            {
                                                                                  $$ = create_node("Gt", NULL, $2->line, $2->column); if($1 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $1);
                                                                                  } if($3 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $3);
                                                                                  }
                                                                                }
          | PLUS Expression %prec UNARY                                         {
                                                                                  $$ = create_node("Plus", NULL, $1->line, $1->column); 
                                                                                  if($2 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $2);
                                                                                  }
                                                                                }
          | MINUS Expression %prec UNARY                                        {
                                                                                  $$ = create_node("Minus", NULL, $1->line, $1->column);
                                                                                  if($2 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $2);
                                                                                  }
                                                                                }
          | NOT Expression                                                      {
                                                                                  $$ = create_node("Not", NULL, $1->line, $1->column);
                                                                                  if($2 == NULL) {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child($$, $2);
                                                                                  }
                                                                                }
          | ID LPAR Expression ExpressionSecAux RPAR                            {
                                                                                  $$ = create_node("Call", NULL, 0, 0); 
                                                                                  insert_child($$, create_node("Id", $1->id, $1->line, $1->column)); 
                                                                                  if($3!=NULL) {
                                                                                    insert_child($$, $3);
                                                                                  } 
                                                                                  if($4!=NULL) {
                                                                                    insert_child($$, $4);
                                                                                  }
                                                                                }
          | ID LPAR RPAR                                                        {
                                                                                  $$ = create_node("Call", NULL, 0, 0); 
                                                                                  insert_child($$, create_node("Id", $1->id, $1->line, $1->column));
                                                                                }
          | ID                                                                  {$$ = create_node("Id", $1->id, $1->line, $1->column);}
          | INTLIT                                                              {$$ = create_node("IntLit", $1->id, $1->line, $1->column);}
          | CHRLIT                                                              {$$ = create_node("ChrLit", $1->id, $1->line, $1->column);}
          | REALLIT                                                             {$$ = create_node("RealLit", $1->id, $1->line, $1->column);}
          | LPAR ExpressionAux RPAR                                             {$$ = $2;}
          | LPAR error RPAR                                                     {$$ = NULL;}
          | ID LPAR error RPAR                                                  {$$ = NULL;}
;

ExpressionAux: ExpressionAux COMMA Expression                                   {
                                                                                  $$ = create_node("Comma", NULL, $2->line, $2->column); 
                                                                                  if($1 != NULL) {
                                                                                    insert_child($$, $1);
                                                                                  } else {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  } if($3 != NULL) {
                                                                                    insert_child($$, $3);
                                                                                  } else {
                                                                                    insert_child($$, create_node("Null", NULL, 0, 0));
                                                                                  }
                                                                                }
             | Expression                                                       {$$ = $1;}
;

ExpressionSecAux: ExpressionSecAux COMMA Expression                             {
                                                                                  if($1 != NULL) {
                                                                                    $$ = $1; insert_brother($$, $3);
                                                                                  } else if($3 != NULL) {
                                                                                    $$ = $3;
                                                                                  } else {
                                                                                    $$ = create_node("Null", NULL, 0, 0);
                                                                                  }
                                                                                }
                |                                                               {$$ = NULL;}
;

%%