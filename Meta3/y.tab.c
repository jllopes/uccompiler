/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 5 "uccompiler.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    #include "sym_table.h"
    int yylex(void);
    void yyerror (char *s);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 15 "uccompiler.y"
{
    struct Token *token;
    struct Node *node;
}
/* Line 193 of yacc.c.  */
#line 198 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 211 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   444

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    17,    20,    23,
      24,    28,    31,    35,    38,    41,    43,    45,    49,    54,
      57,    61,    62,    65,    67,    72,    75,    79,    80,    82,
      84,    86,    88,    90,    94,    96,    99,   101,   105,   108,
     114,   122,   128,   132,   135,   139,   142,   144,   146,   149,
     153,   157,   161,   165,   169,   173,   177,   181,   185,   189,
     193,   197,   201,   205,   209,   213,   217,   220,   223,   226,
     232,   236,   238,   240,   242,   244,   248,   252,   257,   261,
     263,   267
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    47,    -1,    49,    48,    -1,    52,    48,
      -1,    57,    48,    -1,    48,    49,    -1,    48,    52,    -1,
      48,    57,    -1,    -1,    59,    53,    50,    -1,    28,    30,
      -1,    28,    51,    30,    -1,    51,    61,    -1,    51,    57,
      -1,    61,    -1,    57,    -1,    59,    53,    35,    -1,    37,
      29,    54,    31,    -1,    56,    55,    -1,    18,    56,    55,
      -1,    -1,    59,    37,    -1,    59,    -1,    59,    60,    58,
      35,    -1,     1,    35,    -1,    58,    18,    60,    -1,    -1,
       3,    -1,     7,    -1,    11,    -1,     8,    -1,     9,    -1,
      37,    26,    65,    -1,    37,    -1,    65,    35,    -1,    35,
      -1,    28,    62,    30,    -1,    28,    30,    -1,     6,    29,
      65,    31,    63,    -1,     6,    29,    65,    31,    63,     4,
      63,    -1,     5,    29,    65,    31,    63,    -1,    10,    65,
      35,    -1,    10,    35,    -1,    28,     1,    30,    -1,    62,
      63,    -1,    63,    -1,    61,    -1,     1,    35,    -1,    64,
      26,    64,    -1,    64,    33,    64,    -1,    64,    32,    64,
      -1,    64,    17,    64,    -1,    64,    19,    64,    -1,    64,
      34,    64,    -1,    64,    13,    64,    -1,    64,    12,    64,
      -1,    64,    14,    64,    -1,    64,    15,    64,    -1,    64,
      16,    64,    -1,    64,    20,    64,    -1,    64,    21,    64,
      -1,    64,    24,    64,    -1,    64,    22,    64,    -1,    64,
      25,    64,    -1,    64,    23,    64,    -1,    33,    64,    -1,
      32,    64,    -1,    27,    64,    -1,    37,    29,    64,    66,
      31,    -1,    37,    29,    31,    -1,    37,    -1,    38,    -1,
      39,    -1,    42,    -1,    29,    65,    31,    -1,    29,     1,
      31,    -1,    37,    29,     1,    31,    -1,    65,    18,    64,
      -1,    64,    -1,    66,    18,    64,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    41,    41,    47,    51,    55,    65,    73,    81,    89,
      92,   100,   101,   109,   117,   125,   126,   129,   136,   142,
     149,   153,   156,   161,   167,   174,   177,   185,   188,   189,
     190,   191,   192,   195,   199,   205,   206,   207,   215,   216,
     229,   248,   260,   264,   268,   271,   279,   282,   283,   286,
     299,   312,   324,   336,   347,   358,   369,   380,   391,   402,
     413,   424,   435,   446,   457,   468,   479,   487,   495,   503,
     513,   517,   518,   519,   520,   521,   522,   523,   526,   538,
     541,   550
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "ELSE", "WHILE", "IF", "INT",
  "SHORT", "DOUBLE", "RETURN", "VOID", "AND", "OR", "BITWISEAND",
  "BITWISEOR", "BITWISEXOR", "MUL", "COMMA", "DIV", "EQ", "NE", "GE", "GT",
  "LE", "LT", "ASSIGN", "NOT", "LBRACE", "LPAR", "RBRACE", "RPAR", "MINUS",
  "PLUS", "MOD", "SEMI", "RESERVED", "ID", "INTLIT", "CHRLIT", "INVCHRLIT",
  "UNTCHRLIT", "REALLIT", "UNARY", "IFPREC", "$accept", "Program", "Start",
  "StartAux", "FunctionDefinition", "FunctionBody",
  "DeclarationsAndStatements", "FunctionDeclaration", "FunctionDeclarator",
  "ParameterList", "ParameterListAux", "ParameterDeclaration",
  "Declaration", "DeclarationAux", "TypeSpec", "Declarator", "Statement",
  "StatementErrorAux", "StatementError", "Expression", "ExpressionAux",
  "ExpressionSecAux", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    47,    47,    47,    48,    48,    48,    48,
      49,    50,    50,    51,    51,    51,    51,    52,    53,    54,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    59,
      59,    59,    59,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    62,    62,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    65,    65,
      66,    66
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     0,
       3,     2,     3,     2,     2,     1,     1,     3,     4,     2,
       3,     0,     2,     1,     4,     2,     3,     0,     1,     1,
       1,     1,     1,     3,     1,     2,     1,     3,     2,     5,
       7,     5,     3,     2,     3,     2,     1,     1,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     5,
       3,     1,     1,     1,     1,     3,     3,     4,     3,     1,
       3,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    28,    29,    31,    32,    30,     0,     2,     9,
       9,     9,     0,    25,     1,     0,     0,     0,    34,     0,
      27,     6,     7,     8,     0,     0,     0,    17,    10,     0,
       0,     0,     0,     0,    71,    72,    73,    74,    79,    33,
       0,    21,    23,     0,     0,     0,     0,    11,    36,     0,
      16,     0,    15,     0,     0,    24,    68,     0,     0,    67,
      66,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,    19,    22,     0,     0,    43,     0,     0,    38,
      47,     0,    46,    12,    14,    13,    34,    35,    26,    76,
      75,     0,    70,    81,    56,    55,    57,    58,    59,    52,
      53,    60,    61,    63,    65,    62,    64,    49,    51,    50,
      54,    78,    21,     0,     0,    42,    44,    48,     0,    37,
      45,    77,     0,    20,     0,     0,     0,    69,    41,    39,
      80,     0,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,    15,    21,    28,    49,    22,    19,    40,
      82,    41,    23,    29,    12,    20,    90,    91,    92,    38,
      53,   132
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -85
static const yytype_int16 yypact[] =
{
     433,   -17,   -85,   -85,   -85,   -85,   -85,    25,   -85,   -85,
     -85,   -85,    19,   -85,   -85,   400,   412,   424,    89,   -12,
     -85,   -85,   -85,   -85,   360,   158,    62,   -85,   -85,    -5,
     360,   199,   360,   360,    48,   -85,   -85,   -85,   230,   -85,
      51,    60,    49,    55,    59,   -18,   118,   -85,   -85,   102,
     -85,    61,   -85,    41,    61,   -85,   -85,    85,    56,   -85,
     -85,   183,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     -85,   158,   -85,   -85,   360,   360,   -85,    67,    23,   -85,
     -85,   153,   -85,   -85,   -85,   -85,    91,   -85,   -85,   -85,
     -85,    90,   -85,   230,   274,   253,   334,   295,   316,   -85,
     -85,   352,   352,    47,    47,    47,    47,   230,    -7,    -7,
     -85,   230,    60,    65,    96,   -85,   -85,   -85,    58,   -85,
     -85,   -85,   107,   -85,   169,   169,   360,   -85,   -85,   116,
     230,   169,   -85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -85,   -85,   -85,    44,   122,   -85,   -85,   126,   -85,   -85,
      11,    68,    26,   -85,   -21,    82,   -20,   -85,   -84,   -30,
     -23,   -85
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -6
static const yytype_int16 yytable[] =
{
      56,    39,    59,    60,    42,    51,    52,   130,    58,    30,
      67,    31,    68,    54,    32,    33,    26,    86,    13,    34,
      35,    36,    87,    27,    37,    14,    11,    78,    51,    95,
      55,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     138,   139,    50,   126,    16,    17,    18,   142,   127,    79,
      42,   123,   124,     1,    67,     2,    68,    43,    44,     3,
       4,     5,    45,     6,    79,    94,    97,    61,    81,    76,
      77,    78,    80,    79,    84,    79,    83,   100,    85,    30,
      46,    31,    47,   127,    32,    33,   134,    48,    96,    34,
      35,    36,   125,     1,    37,     2,   140,    43,    44,     3,
       4,     5,    45,     6,    79,    24,    99,    24,    25,    88,
     141,   131,     9,    43,    44,   136,    10,   135,    45,    30,
      46,    31,    93,   133,    32,    33,    98,    48,   137,    34,
      35,    36,     0,     0,    37,    30,    46,    31,    89,   122,
      32,    33,     0,    48,   128,    34,    35,    36,    43,    44,
      37,     2,     0,    45,     0,     3,     4,     5,     0,     6,
     128,     0,     0,     0,    43,    44,     0,     0,     0,    45,
      30,    46,    31,   129,   101,    32,    33,     0,    48,     0,
      34,    35,    36,     0,     0,    37,    30,    46,    31,     0,
      57,    32,    33,     0,    48,     0,    34,    35,    36,     0,
      30,    37,    31,     0,   102,    32,    33,     0,     0,     0,
      34,    35,    36,     0,     0,    37,    30,     0,    31,     0,
       0,    32,    33,     0,     0,     0,    34,    35,    36,     0,
       0,    37,    62,    63,    64,    65,    66,    67,     0,    68,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,     0,    76,    77,    78,    62,     0,    64,    65,    66,
      67,     0,    68,    69,    70,    71,    72,    73,    74,     0,
       0,     0,     0,     0,     0,    76,    77,    78,    64,    65,
      66,    67,     0,    68,    69,    70,    71,    72,    73,    74,
       0,     0,     0,     0,     0,     0,    76,    77,    78,    64,
       0,    66,    67,     0,    68,    69,    70,    71,    72,    73,
      74,     0,     0,     0,     0,     0,     0,    76,    77,    78,
      64,     0,     0,    67,     0,    68,    69,    70,    71,    72,
      73,    74,     0,     0,     0,     0,     0,     0,    76,    77,
      78,    67,     0,    68,    69,    70,    71,    72,    73,    74,
       0,     0,     0,     0,     0,     0,    76,    77,    78,    67,
       0,    68,     0,     0,    71,    72,    73,    74,     0,     0,
       0,     0,     0,     0,    76,    77,    78,    30,     0,    31,
       0,     0,    32,    33,     0,     0,     0,    34,    35,    36,
      -3,     1,    37,     2,     0,     0,     0,     3,     4,     5,
       0,     6,    -4,     1,     0,     2,     0,     0,     0,     3,
       4,     5,     0,     6,    -5,     1,     0,     2,     0,     0,
       0,     3,     4,     5,     1,     6,     2,     0,     0,     0,
       3,     4,     5,     0,     6
};

static const yytype_int16 yycheck[] =
{
      30,    24,    32,    33,    25,    26,    26,    91,    31,    27,
      17,    29,    19,    18,    32,    33,    28,    35,    35,    37,
      38,    39,    45,    35,    42,     0,     0,    34,    49,    49,
      35,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
     134,   135,    26,    30,    10,    11,    37,   141,    35,    18,
      81,    84,    85,     1,    17,     3,    19,     5,     6,     7,
       8,     9,    10,    11,    18,    49,    35,    29,    18,    32,
      33,    34,    31,    18,    29,    18,    37,    31,    29,    27,
      28,    29,    30,    35,    32,    33,    31,    35,    37,    37,
      38,    39,    35,     1,    42,     3,   136,     5,     6,     7,
       8,     9,    10,    11,    18,    26,    31,    26,    29,     1,
       4,    31,     0,     5,     6,    18,     0,    31,    10,    27,
      28,    29,    30,   122,    32,    33,    54,    35,    31,    37,
      38,    39,    -1,    -1,    42,    27,    28,    29,    30,    81,
      32,    33,    -1,    35,     1,    37,    38,    39,     5,     6,
      42,     3,    -1,    10,    -1,     7,     8,     9,    -1,    11,
       1,    -1,    -1,    -1,     5,     6,    -1,    -1,    -1,    10,
      27,    28,    29,    30,     1,    32,    33,    -1,    35,    -1,
      37,    38,    39,    -1,    -1,    42,    27,    28,    29,    -1,
       1,    32,    33,    -1,    35,    -1,    37,    38,    39,    -1,
      27,    42,    29,    -1,    31,    32,    33,    -1,    -1,    -1,
      37,    38,    39,    -1,    -1,    42,    27,    -1,    29,    -1,
      -1,    32,    33,    -1,    -1,    -1,    37,    38,    39,    -1,
      -1,    42,    12,    13,    14,    15,    16,    17,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    12,    -1,    14,    15,    16,
      17,    -1,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    34,    14,    15,
      16,    17,    -1,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    14,
      -1,    16,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      14,    -1,    -1,    17,    -1,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    17,    -1,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    17,
      -1,    19,    -1,    -1,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    27,    -1,    29,
      -1,    -1,    32,    33,    -1,    -1,    -1,    37,    38,    39,
       0,     1,    42,     3,    -1,    -1,    -1,     7,     8,     9,
      -1,    11,     0,     1,    -1,     3,    -1,    -1,    -1,     7,
       8,     9,    -1,    11,     0,     1,    -1,     3,    -1,    -1,
      -1,     7,     8,     9,     1,    11,     3,    -1,    -1,    -1,
       7,     8,     9,    -1,    11
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     7,     8,     9,    11,    46,    47,    49,
      52,    57,    59,    35,     0,    48,    48,    48,    37,    53,
      60,    49,    52,    57,    26,    29,    28,    35,    50,    58,
      27,    29,    32,    33,    37,    38,    39,    42,    64,    65,
      54,    56,    59,     5,     6,    10,    28,    30,    35,    51,
      57,    59,    61,    65,    18,    35,    64,     1,    65,    64,
      64,    29,    12,    13,    14,    15,    16,    17,    19,    20,
      21,    22,    23,    24,    25,    26,    32,    33,    34,    18,
      31,    18,    55,    37,    29,    29,    35,    65,     1,    30,
      61,    62,    63,    30,    57,    61,    37,    35,    60,    31,
      31,     1,    31,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    56,    65,    65,    35,    30,    35,     1,    30,
      63,    31,    66,    55,    31,    31,    18,    31,    63,    63,
      64,     4,    63
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 41 "uccompiler.y"
    {
                                                                                  root = create_node("Program", NULL, 0, 0);
                                                                                  insert_child(root,(yyvsp[(1) - (1)].node));
                                                                                }
    break;

  case 3:
#line 47 "uccompiler.y"
    {
                                                                                  (yyval.node) = (yyvsp[(1) - (2)].node); 
                                                                                  insert_brother((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                }
    break;

  case 4:
#line 51 "uccompiler.y"
    {
                                                                                  (yyval.node) = (yyvsp[(1) - (2)].node); 
                                                                                  insert_brother((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                }
    break;

  case 5:
#line 55 "uccompiler.y"
    {
                                                                                  if((yyvsp[(1) - (2)].node) != NULL) {
                                                                                    (yyval.node) = (yyvsp[(1) - (2)].node); 
                                                                                    insert_brother((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                  } else {
                                                                                    (yyval.node)=(yyvsp[(2) - (2)].node);
                                                                                  }
                                                                                }
    break;

  case 6:
#line 65 "uccompiler.y"
    {
                                                                                  if((yyvsp[(1) - (2)].node) != NULL) {
                                                                                    (yyval.node) = (yyvsp[(1) - (2)].node); 
                                                                                    insert_brother((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                  } else {
                                                                                    (yyval.node) = (yyvsp[(2) - (2)].node);
                                                                                  }
                                                                                }
    break;

  case 7:
#line 73 "uccompiler.y"
    {
                                                                                  if((yyvsp[(1) - (2)].node) != NULL) {
                                                                                    (yyval.node) = (yyvsp[(1) - (2)].node); 
                                                                                    insert_brother((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                  } else {
                                                                                    (yyval.node) = (yyvsp[(2) - (2)].node);
                                                                                  }
                                                                                }
    break;

  case 8:
#line 81 "uccompiler.y"
    {
                                                                                  if((yyvsp[(1) - (2)].node) != NULL) {
                                                                                    (yyval.node) = (yyvsp[(1) - (2)].node); 
                                                                                    insert_brother((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                  } else {
                                                                                    (yyval.node) = (yyvsp[(2) - (2)].node);
                                                                                  }
                                                                                }
    break;

  case 9:
#line 89 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 10:
#line 92 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("FuncDefinition", NULL, 0, 0); 
                                                                                  insert_child((yyval.node), (yyvsp[(1) - (3)].node)); 
                                                                                  insert_child((yyval.node), (yyvsp[(2) - (3)].node)); 
                                                                                  insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                }
    break;

  case 11:
#line 100 "uccompiler.y"
    {(yyval.node) = create_node("FuncBody", NULL, 0, 0);}
    break;

  case 12:
#line 101 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("FuncBody", NULL, 0, 0); 
                                                                                  if((yyvsp[(2) - (3)].node) != NULL) {
                                                                                    insert_child((yyval.node), (yyvsp[(2) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 13:
#line 109 "uccompiler.y"
    {
                                                                                  if((yyvsp[(1) - (2)].node) != NULL) {
                                                                                    (yyval.node) = (yyvsp[(1) - (2)].node); 
                                                                                    insert_brother((yyval.node),(yyvsp[(2) - (2)].node));
                                                                                  } else {
                                                                                    (yyval.node) = (yyvsp[(2) - (2)].node);
                                                                                  }
                                                                                }
    break;

  case 14:
#line 117 "uccompiler.y"
    {
                                                                                  if((yyvsp[(1) - (2)].node) != NULL) {
                                                                                    (yyval.node) = (yyvsp[(1) - (2)].node); 
                                                                                    insert_brother((yyval.node),(yyvsp[(2) - (2)].node));
                                                                                  } else {
                                                                                    (yyval.node) = (yyvsp[(2) - (2)].node);
                                                                                  }
                                                                                }
    break;

  case 15:
#line 125 "uccompiler.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 16:
#line 126 "uccompiler.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);}
    break;

  case 17:
#line 129 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("FuncDeclaration", NULL, 0, 0);
                                                                                  insert_child((yyval.node), (yyvsp[(1) - (3)].node)); 
                                                                                  insert_child((yyval.node), (yyvsp[(2) - (3)].node));
                                                                                }
    break;

  case 18:
#line 136 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Id",(yyvsp[(1) - (4)].token)->id, (yyvsp[(1) - (4)].token)->line, (yyvsp[(1) - (4)].token)->column); 
                                                                                  insert_brother((yyval.node), (yyvsp[(3) - (4)].node));
                                                                                }
    break;

  case 19:
#line 142 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("ParamList", NULL, 0, 0); 
                                                                                  insert_child((yyval.node), (yyvsp[(1) - (2)].node)); 
                                                                                  insert_child((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                }
    break;

  case 20:
#line 149 "uccompiler.y"
    {
                                                                                  (yyval.node) = (yyvsp[(2) - (3)].node); 
                                                                                  insert_brother((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                }
    break;

  case 21:
#line 153 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 22:
#line 156 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("ParamDeclaration", NULL, 0, 0); 
                                                                                  insert_child((yyval.node), (yyvsp[(1) - (2)].node)); 
                                                                                  insert_child((yyval.node), create_node("Id",(yyvsp[(2) - (2)].token)->id, (yyvsp[(2) - (2)].token)->line, (yyvsp[(2) - (2)].token)->column));
                                                                                }
    break;

  case 23:
#line 161 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("ParamDeclaration", NULL, 0, 0); 
                                                                                  insert_child((yyval.node), (yyvsp[(1) - (1)].node));
                                                                                }
    break;

  case 24:
#line 167 "uccompiler.y"
    {
                                                                                  (yyval.node) = (yyvsp[(2) - (4)].node); 
                                                                                  if((yyvsp[(3) - (4)].node) != NULL) {
                                                                                    insert_brother((yyval.node), (yyvsp[(3) - (4)].node));
                                                                                  } 
                                                                                  insert_first_child((yyval.node), (yyvsp[(1) - (4)].node));
                                                                                }
    break;

  case 25:
#line 174 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 26:
#line 177 "uccompiler.y"
    {
                                                                                  if((yyvsp[(1) - (3)].node) != NULL) {
                                                                                    (yyval.node) = (yyvsp[(1) - (3)].node); 
                                                                                    insert_brother((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  } else {
                                                                                    (yyval.node) = (yyvsp[(3) - (3)].node);
                                                                                  }
                                                                                }
    break;

  case 27:
#line 185 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 28:
#line 188 "uccompiler.y"
    {(yyval.node) = create_node("Char", NULL, (yyvsp[(1) - (1)].token)->line, (yyvsp[(1) - (1)].token)->column);}
    break;

  case 29:
#line 189 "uccompiler.y"
    {(yyval.node) = create_node("Int", NULL, (yyvsp[(1) - (1)].token)->line, (yyvsp[(1) - (1)].token)->column);}
    break;

  case 30:
#line 190 "uccompiler.y"
    {(yyval.node) = create_node("Void", NULL, (yyvsp[(1) - (1)].token)->line, (yyvsp[(1) - (1)].token)->column);}
    break;

  case 31:
#line 191 "uccompiler.y"
    {(yyval.node) = create_node("Short", NULL, (yyvsp[(1) - (1)].token)->line, (yyvsp[(1) - (1)].token)->column);}
    break;

  case 32:
#line 192 "uccompiler.y"
    {(yyval.node) = create_node("Double", NULL, (yyvsp[(1) - (1)].token)->line, (yyvsp[(1) - (1)].token)->column);}
    break;

  case 33:
#line 195 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Declaration", NULL, 0, 0); 
                                                                                  insert_child((yyval.node),create_node("Id", (yyvsp[(1) - (3)].token)->id, (yyvsp[(1) - (3)].token)->line, (yyvsp[(1) - (3)].token)->column)); 
                                                                                  insert_child((yyval.node), (yyvsp[(3) - (3)].node));}
    break;

  case 34:
#line 199 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Declaration", NULL, 0, 0); 
                                                                                  insert_child((yyval.node), create_node("Id", (yyvsp[(1) - (1)].token)->id, (yyvsp[(1) - (1)].token)->line, (yyvsp[(1) - (1)].token)->column));
                                                                                }
    break;

  case 35:
#line 205 "uccompiler.y"
    {(yyval.node) = (yyvsp[(1) - (2)].node);}
    break;

  case 36:
#line 206 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 37:
#line 207 "uccompiler.y"
    {
                                                                                  if((yyvsp[(2) - (3)].node) != NULL && (yyvsp[(2) - (3)].node)->brother != NULL) {
                                                                                    (yyval.node) = create_node("StatList", NULL, 0, 0); 
                                                                                    insert_child((yyval.node), (yyvsp[(2) - (3)].node));
                                                                                  } else {
                                                                                    (yyval.node) = (yyvsp[(2) - (3)].node);
                                                                                  }
                                                                                }
    break;

  case 38:
#line 215 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 39:
#line 216 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("If", NULL, (yyvsp[(1) - (5)].token)->line, (yyvsp[(1) - (5)].token)->column); 
                                                                                  insert_child((yyval.node), (yyvsp[(3) - (5)].node)); 
                                                                                  if((yyvsp[(5) - (5)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else if((yyvsp[(5) - (5)].node) != NULL && (yyvsp[(5) - (5)].node)->brother != NULL) {
                                                                                    insert_child((yyval.node), create_node("StatList", NULL, 0, 0)); 
                                                                                    insert_child((yyval.node)->child->brother, (yyvsp[(5) - (5)].node));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(5) - (5)].node));
                                                                                  } 
                                                                                  insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                }
    break;

  case 40:
#line 229 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("If", NULL, (yyvsp[(1) - (7)].token)->line, (yyvsp[(1) - (7)].token)->column); 
                                                                                  insert_child((yyval.node), (yyvsp[(3) - (7)].node)); 
                                                                                  if((yyvsp[(5) - (7)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else if((yyvsp[(5) - (7)].node) != NULL && (yyvsp[(5) - (7)].node)->brother != NULL) {
                                                                                    insert_child((yyval.node), create_node("StatList", NULL, 0, 0)); 
                                                                                    insert_child((yyval.node)->child->brother, (yyvsp[(5) - (7)].node));
                                                                                  } else{
                                                                                    insert_child((yyval.node), (yyvsp[(5) - (7)].node));
                                                                                  } if((yyvsp[(7) - (7)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else if((yyvsp[(7) - (7)].node) != NULL && (yyvsp[(7) - (7)].node)->brother != NULL) {
                                                                                    insert_child((yyval.node), create_node("StatList", NULL, 0, 0)); 
                                                                                    insert_child((yyval.node)->child->brother->brother, (yyvsp[(7) - (7)].node));
                                                                                  } else{
                                                                                    insert_child((yyval.node), (yyvsp[(7) - (7)].node));
                                                                                  }
                                                                                }
    break;

  case 41:
#line 248 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("While", NULL, (yyvsp[(1) - (5)].token)->line, (yyvsp[(1) - (5)].token)->column); 
                                                                                  if((yyvsp[(3) - (5)].node)!=NULL) {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (5)].node));
                                                                                  } else {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } if((yyvsp[(5) - (5)].node) != NULL) {
                                                                                    insert_child((yyval.node), (yyvsp[(5) - (5)].node));
                                                                                  } else {
                                                                                  insert_child((yyval.node), create_node("Null",NULL, 0, 0));
                                                                                  }
                                                                                }
    break;

  case 42:
#line 260 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Return", NULL, (yyvsp[(1) - (3)].token)->line, (yyvsp[(1) - (3)].token)->column);
                                                                                  insert_child((yyval.node), (yyvsp[(2) - (3)].node));
                                                                                }
    break;

  case 43:
#line 264 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Return", NULL, (yyvsp[(1) - (2)].token)->line, (yyvsp[(1) - (2)].token)->column); 
                                                                                  insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                }
    break;

  case 44:
#line 268 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 45:
#line 271 "uccompiler.y"
    {
                                                                                  if((yyvsp[(1) - (2)].node) != NULL) {
                                                                                    (yyval.node) = (yyvsp[(1) - (2)].node); 
                                                                                    insert_brother((yyval.node),(yyvsp[(2) - (2)].node));
                                                                                  } else {
                                                                                    (yyval.node) = (yyvsp[(2) - (2)].node);
                                                                                  }
                                                                                }
    break;

  case 46:
#line 279 "uccompiler.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 47:
#line 282 "uccompiler.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 48:
#line 283 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 49:
#line 286 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Store", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column);
                                                                                  if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } 
                                                                                  if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 50:
#line 299 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Add", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); 
                                                                                  if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } 
                                                                                  if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 51:
#line 312 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Sub", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column);
                                                                                  if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 52:
#line 324 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Mul", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); 
                                                                                  if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 53:
#line 336 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Div", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 54:
#line 347 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Mod", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 55:
#line 358 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Or", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 56:
#line 369 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("And", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 57:
#line 380 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("BitWiseAnd", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 58:
#line 391 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("BitWiseOr", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 59:
#line 402 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("BitWiseXor", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 60:
#line 413 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Eq", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 61:
#line 424 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Ne", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 62:
#line 435 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Le", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 63:
#line 446 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Ge", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 64:
#line 457 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Lt", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 65:
#line 468 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Gt", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); if((yyvsp[(1) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } if((yyvsp[(3) - (3)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  }
                                                                                }
    break;

  case 66:
#line 479 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Plus", NULL, (yyvsp[(1) - (2)].token)->line, (yyvsp[(1) - (2)].token)->column); 
                                                                                  if((yyvsp[(2) - (2)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                  }
                                                                                }
    break;

  case 67:
#line 487 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Minus", NULL, (yyvsp[(1) - (2)].token)->line, (yyvsp[(1) - (2)].token)->column);
                                                                                  if((yyvsp[(2) - (2)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                  }
                                                                                }
    break;

  case 68:
#line 495 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Not", NULL, (yyvsp[(1) - (2)].token)->line, (yyvsp[(1) - (2)].token)->column);
                                                                                  if((yyvsp[(2) - (2)].node) == NULL) {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } else {
                                                                                    insert_child((yyval.node), (yyvsp[(2) - (2)].node));
                                                                                  }
                                                                                }
    break;

  case 69:
#line 503 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Call", NULL, 0, 0); 
                                                                                  insert_child((yyval.node), create_node("Id", (yyvsp[(1) - (5)].token)->id, (yyvsp[(1) - (5)].token)->line, (yyvsp[(1) - (5)].token)->column)); 
                                                                                  if((yyvsp[(3) - (5)].node)!=NULL) {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (5)].node));
                                                                                  } 
                                                                                  if((yyvsp[(4) - (5)].node)!=NULL) {
                                                                                    insert_child((yyval.node), (yyvsp[(4) - (5)].node));
                                                                                  }
                                                                                }
    break;

  case 70:
#line 513 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Call", NULL, 0, 0); 
                                                                                  insert_child((yyval.node), create_node("Id", (yyvsp[(1) - (3)].token)->id, (yyvsp[(1) - (3)].token)->line, (yyvsp[(1) - (3)].token)->column));
                                                                                }
    break;

  case 71:
#line 517 "uccompiler.y"
    {(yyval.node) = create_node("Id", (yyvsp[(1) - (1)].token)->id, (yyvsp[(1) - (1)].token)->line, (yyvsp[(1) - (1)].token)->column);}
    break;

  case 72:
#line 518 "uccompiler.y"
    {(yyval.node) = create_node("IntLit", (yyvsp[(1) - (1)].token)->id, (yyvsp[(1) - (1)].token)->line, (yyvsp[(1) - (1)].token)->column);}
    break;

  case 73:
#line 519 "uccompiler.y"
    {(yyval.node) = create_node("ChrLit", (yyvsp[(1) - (1)].token)->id, (yyvsp[(1) - (1)].token)->line, (yyvsp[(1) - (1)].token)->column);}
    break;

  case 74:
#line 520 "uccompiler.y"
    {(yyval.node) = create_node("RealLit", (yyvsp[(1) - (1)].token)->id, (yyvsp[(1) - (1)].token)->line, (yyvsp[(1) - (1)].token)->column);}
    break;

  case 75:
#line 521 "uccompiler.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);}
    break;

  case 76:
#line 522 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 77:
#line 523 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 78:
#line 526 "uccompiler.y"
    {
                                                                                  (yyval.node) = create_node("Comma", NULL, (yyvsp[(2) - (3)].token)->line, (yyvsp[(2) - (3)].token)->column); 
                                                                                  if((yyvsp[(1) - (3)].node) != NULL) {
                                                                                    insert_child((yyval.node), (yyvsp[(1) - (3)].node));
                                                                                  } else {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  } if((yyvsp[(3) - (3)].node) != NULL) {
                                                                                    insert_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  } else {
                                                                                    insert_child((yyval.node), create_node("Null", NULL, 0, 0));
                                                                                  }
                                                                                }
    break;

  case 79:
#line 538 "uccompiler.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 80:
#line 541 "uccompiler.y"
    {
                                                                                  if((yyvsp[(1) - (3)].node) != NULL) {
                                                                                    (yyval.node) = (yyvsp[(1) - (3)].node); insert_brother((yyval.node), (yyvsp[(3) - (3)].node));
                                                                                  } else if((yyvsp[(3) - (3)].node) != NULL) {
                                                                                    (yyval.node) = (yyvsp[(3) - (3)].node);
                                                                                  } else {
                                                                                    (yyval.node) = create_node("Null", NULL, 0, 0);
                                                                                  }
                                                                                }
    break;

  case 81:
#line 550 "uccompiler.y"
    {(yyval.node) = NULL;}
    break;


/* Line 1267 of yacc.c.  */
#line 2390 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 553 "uccompiler.y"

