/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHAR = 258,
     ELSE = 259,
     WHILE = 260,
     IF = 261,
     INT = 262,
     SHORT = 263,
     DOUBLE = 264,
     RETURN = 265,
     VOID = 266,
     AND = 267,
     OR = 268,
     BITWISEAND = 269,
     BITWISEOR = 270,
     BITWISEXOR = 271,
     MUL = 272,
     COMMA = 273,
     DIV = 274,
     EQ = 275,
     NE = 276,
     GE = 277,
     GT = 278,
     LE = 279,
     LT = 280,
     ASSIGN = 281,
     NOT = 282,
     LBRACE = 283,
     LPAR = 284,
     RBRACE = 285,
     RPAR = 286,
     MINUS = 287,
     PLUS = 288,
     MOD = 289,
     SEMI = 290,
     RESERVED = 291,
     ID = 292,
     INTLIT = 293,
     CHRLIT = 294,
     INVCHRLIT = 295,
     UNTCHRLIT = 296,
     REALLIT = 297,
     UNARY = 298,
     IFPREC = 299
   };
#endif
/* Tokens.  */
#define CHAR 258
#define ELSE 259
#define WHILE 260
#define IF 261
#define INT 262
#define SHORT 263
#define DOUBLE 264
#define RETURN 265
#define VOID 266
#define AND 267
#define OR 268
#define BITWISEAND 269
#define BITWISEOR 270
#define BITWISEXOR 271
#define MUL 272
#define COMMA 273
#define DIV 274
#define EQ 275
#define NE 276
#define GE 277
#define GT 278
#define LE 279
#define LT 280
#define ASSIGN 281
#define NOT 282
#define LBRACE 283
#define LPAR 284
#define RBRACE 285
#define RPAR 286
#define MINUS 287
#define PLUS 288
#define MOD 289
#define SEMI 290
#define RESERVED 291
#define ID 292
#define INTLIT 293
#define CHRLIT 294
#define INVCHRLIT 295
#define UNTCHRLIT 296
#define REALLIT 297
#define UNARY 298
#define IFPREC 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "uccompiler.y"
{
    struct Token *token;
    struct Node *node;
}
/* Line 1529 of yacc.c.  */
#line 142 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;
