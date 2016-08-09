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
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_IDENT = 258,
     TOK_STRING_LITERAL = 259,
     TOK_INT_LITERAL = 260,
     TOK_SECTION_NAME = 261,
     TOK_SOURCE_NAME = 262,
     TOK_BLOB = 263,
     TOK_DOT_DOT = 264,
     TOK_AND = 265,
     TOK_OR = 266,
     TOK_GEQ = 267,
     TOK_LEQ = 268,
     TOK_EQ = 269,
     TOK_NEQ = 270,
     TOK_POWER = 271,
     TOK_LSHIFT = 272,
     TOK_RSHIFT = 273,
     TOK_INT_SIZE = 274,
     TOK_OPTIONS = 275,
     TOK_CONSTANTS = 276,
     TOK_SOURCES = 277,
     TOK_FILTERS = 278,
     TOK_SECTION = 279,
     TOK_EXTERN = 280,
     TOK_FROM = 281,
     TOK_RAW = 282,
     TOK_LOAD = 283,
     TOK_JUMP = 284,
     TOK_CALL = 285,
     TOK_MODE = 286,
     TOK_ERASE = 287,
     TOK_ALL = 288,
     TOK_IF = 289,
     TOK_ELSE = 290,
     TOK_DEFINED = 291,
     TOK_INFO = 292,
     TOK_WARNING = 293,
     TOK_ERROR = 294,
     TOK_SIZEOF = 295,
     TOK_DCD = 296,
     TOK_HAB = 297,
     TOK_IVT = 298,
     TOK_UNSECURE = 299,
     TOK_RESET = 300,
     TOK_JUMP_SP = 301,
     TOK_ENABLE = 302,
     TOK_KEYBLOB = 303,
     TOK_ENCRYPT = 304,
     TOK_KEYWRAP = 305,
     UNARY_OP = 306
   };
#endif
/* Tokens.  */
#define TOK_IDENT 258
#define TOK_STRING_LITERAL 259
#define TOK_INT_LITERAL 260
#define TOK_SECTION_NAME 261
#define TOK_SOURCE_NAME 262
#define TOK_BLOB 263
#define TOK_DOT_DOT 264
#define TOK_AND 265
#define TOK_OR 266
#define TOK_GEQ 267
#define TOK_LEQ 268
#define TOK_EQ 269
#define TOK_NEQ 270
#define TOK_POWER 271
#define TOK_LSHIFT 272
#define TOK_RSHIFT 273
#define TOK_INT_SIZE 274
#define TOK_OPTIONS 275
#define TOK_CONSTANTS 276
#define TOK_SOURCES 277
#define TOK_FILTERS 278
#define TOK_SECTION 279
#define TOK_EXTERN 280
#define TOK_FROM 281
#define TOK_RAW 282
#define TOK_LOAD 283
#define TOK_JUMP 284
#define TOK_CALL 285
#define TOK_MODE 286
#define TOK_ERASE 287
#define TOK_ALL 288
#define TOK_IF 289
#define TOK_ELSE 290
#define TOK_DEFINED 291
#define TOK_INFO 292
#define TOK_WARNING 293
#define TOK_ERROR 294
#define TOK_SIZEOF 295
#define TOK_DCD 296
#define TOK_HAB 297
#define TOK_IVT 298
#define TOK_UNSECURE 299
#define TOK_RESET 300
#define TOK_JUMP_SP 301
#define TOK_ENABLE 302
#define TOK_KEYBLOB 303
#define TOK_ENCRYPT 304
#define TOK_KEYWRAP 305
#define UNARY_OP 306




/* Copy the first part of user declarations.  */
#line 18 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"

#include "ElftosbLexer.h"
#include "ElftosbAST.h"
#include "Logging.h"
#include "Blob.h"
#include "format_string.h"
#include "Value.h"
#include "ConversionController.h"

using namespace elftosb;

//! Our special location type.
#define YYLTYPE token_loc_t

// this indicates that we're using our own type. it should be unset automatically
// but that's not working for some reason with the .hpp file.
#if defined(YYLTYPE_IS_TRIVIAL)
	#undef YYLTYPE_IS_TRIVIAL
	#define YYLTYPE_IS_TRIVIAL 0
#endif

//! Default location action
#define YYLLOC_DEFAULT(Current, Rhs, N)	\
	do {		\
		if (N)	\
		{		\
			(Current).m_firstLine = YYRHSLOC(Rhs, 1).m_firstLine;	\
			(Current).m_lastLine = YYRHSLOC(Rhs, N).m_lastLine;		\
		}		\
		else	\
		{		\
			(Current).m_firstLine = (Current).m_lastLine = YYRHSLOC(Rhs, 0).m_lastLine;	\
		}		\
	} while (0)

//! Forward declaration of yylex().
static int yylex(YYSTYPE * lvalp, YYLTYPE * yylloc, ElftosbLexer * lexer);

// Forward declaration of error handling function.
static void yyerror(YYLTYPE * yylloc, ElftosbLexer * lexer, CommandFileASTNode ** resultAST, const char * error);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 62 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
{
	int m_num;
	elftosb::SizedIntegerValue * m_int;
	Blob * m_blob;
	std::string * m_str;
	elftosb::ASTNode * m_ast;	// must use full name here because this is put into *.tab.hpp
}
/* Line 193 of yacc.c.  */
#line 249 "/Users/MADUser1/Library/Developer/Xcode/DerivedData/elftosb-dxrbhxxtpndhpgdxujwltedpntjq/Build/Intermediates/elftosb.build/Debug/elftosb.build/DerivedSources/elftosb_parser.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 274 "/Users/MADUser1/Library/Developer/Xcode/DerivedData/elftosb-dxrbhxxtpndhpgdxujwltedpntjq/Build/Intermediates/elftosb.build/Debug/elftosb.build/DerivedSources/elftosb_parser.tab.cpp"

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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   543

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
/* YYNRULES -- Number of states.  */
#define YYNSTATES  288

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,     2,     2,    73,    23,     2,
       9,    10,    71,    69,    16,    70,    20,    72,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    18,    17,
      25,    15,    19,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    13,     2,    14,    68,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    11,    24,    12,    22,     2,     2,     2,
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
       5,     6,     7,     8,    21,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    74
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    13,    15,    17,    19,
      24,    29,    31,    34,    37,    38,    42,    50,    52,    55,
      57,    58,    62,    67,    69,    72,    76,    77,    81,    88,
      92,    93,    95,    99,   103,   105,   108,   115,   118,   119,
     121,   122,   126,   130,   132,   135,   138,   140,   142,   144,
     146,   147,   149,   152,   155,   157,   158,   160,   162,   164,
     166,   168,   170,   172,   174,   179,   181,   182,   184,   186,
     188,   190,   194,   199,   201,   203,   205,   209,   211,   214,
     217,   218,   220,   222,   227,   229,   230,   234,   239,   244,
     246,   248,   250,   252,   256,   259,   260,   263,   267,   271,
     273,   274,   280,   288,   296,   299,   301,   305,   308,   311,
     314,   321,   326,   329,   330,   332,   336,   338,   340,   342,
     346,   350,   354,   358,   362,   366,   370,   374,   377,   382,
     386,   391,   393,   397,   400,   402,   404,   406,   410,   414,
     418,   422,   426,   430,   434,   438,   442,   446,   450,   452,
     456,   460,   465,   470,   475,   478,   481
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      76,     0,    -1,    77,    95,    -1,    78,    -1,    77,    78,
      -1,    79,    -1,    80,    -1,    88,    -1,    84,    -1,    37,
      11,    81,    12,    -1,    38,    11,    81,    12,    -1,    82,
      -1,    81,    82,    -1,    83,    17,    -1,    -1,     3,    15,
     131,    -1,    65,     9,   133,    10,    11,    85,    12,    -1,
      86,    -1,    85,    86,    -1,    87,    -1,    -1,     9,   113,
      10,    -1,    39,    11,    89,    12,    -1,    90,    -1,    89,
      90,    -1,    91,    92,    17,    -1,    -1,     3,    15,     4,
      -1,     3,    15,    42,     9,   133,    10,    -1,     9,    93,
      10,    -1,    -1,    94,    -1,    93,    16,    94,    -1,     3,
      15,   131,    -1,    96,    -1,    95,    96,    -1,    41,     9,
     133,    97,    10,    99,    -1,    17,    98,    -1,    -1,    93,
      -1,    -1,    30,   107,    17,    -1,    11,   100,    12,    -1,
     101,    -1,   100,   101,    -1,   104,    17,    -1,   121,    -1,
     122,    -1,   123,    -1,   128,    -1,    -1,   103,    -1,   102,
     103,    -1,   104,    17,    -1,   128,    -1,    -1,   105,    -1,
     114,    -1,   119,    -1,   124,    -1,   127,    -1,   125,    -1,
     115,    -1,   126,    -1,    45,   106,   107,   110,    -1,     3,
      -1,    -1,   133,    -1,     4,    -1,     7,    -1,   108,    -1,
     108,    43,     7,    -1,     7,    13,   108,    14,    -1,     8,
      -1,   112,    -1,   109,    -1,   108,    16,   109,    -1,     6,
      -1,    22,     6,    -1,    19,   111,    -1,    -1,    20,    -1,
     130,    -1,    60,     9,   113,    10,    -1,    93,    -1,    -1,
     116,   117,   118,    -1,    59,   116,   130,   118,    -1,    63,
     133,   117,   118,    -1,    47,    -1,    46,    -1,     7,    -1,
     133,    -1,     9,   133,    10,    -1,     9,    10,    -1,    -1,
      49,   130,    -1,    49,   120,    50,    -1,    49,    61,    50,
      -1,     3,    -1,    -1,    43,     7,    11,   102,    12,    -1,
      66,     9,   133,    10,    11,   102,    12,    -1,    67,     9,
     133,    10,    11,   102,    12,    -1,    48,   133,    -1,    62,
      -1,    64,   120,   130,    -1,    54,     4,    -1,    55,     4,
      -1,    56,     4,    -1,    51,   132,    11,   100,    12,   129,
      -1,    52,    11,   100,    12,    -1,    52,   128,    -1,    -1,
     133,    -1,   133,    21,   133,    -1,   132,    -1,     4,    -1,
     133,    -1,   132,    25,   132,    -1,   132,    19,   132,    -1,
     132,    29,   132,    -1,   132,    30,   132,    -1,   132,    31,
     132,    -1,   132,    32,   132,    -1,   132,    27,   132,    -1,
     132,    28,   132,    -1,    26,   132,    -1,     3,     9,     7,
      10,    -1,     9,   132,    10,    -1,    53,     9,     3,    10,
      -1,   135,    -1,     7,    18,     3,    -1,    18,     3,    -1,
     137,    -1,     3,    -1,   134,    -1,   135,    69,   135,    -1,
     135,    70,   135,    -1,   135,    71,   135,    -1,   135,    72,
     135,    -1,   135,    73,   135,    -1,   135,    33,   135,    -1,
     135,    23,   135,    -1,   135,    24,   135,    -1,   135,    68,
     135,    -1,   135,    34,   135,    -1,   135,    35,   135,    -1,
     136,    -1,   135,    20,    36,    -1,     9,   135,    10,    -1,
      57,     9,   134,    10,    -1,    57,     9,     3,    10,    -1,
      57,     9,     7,    10,    -1,    69,   135,    -1,    70,   135,
      -1,     5,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   176,   176,   186,   192,   200,   201,   202,   203,   206,
     212,   218,   224,   231,   232,   235,   242,   250,   256,   263,
     264,   267,   279,   285,   291,   299,   311,   314,   319,   327,
     328,   332,   338,   346,   353,   359,   366,   381,   386,   392,
     397,   403,   409,   417,   423,   431,   432,   433,   434,   435,
     436,   439,   445,   453,   454,   455,   458,   459,   460,   461,
     462,   463,   464,   465,   468,   487,   492,   495,   499,   504,
     509,   514,   519,   524,   529,   534,   540,   548,   553,   560,
     565,   571,   576,   582,   594,   595,   598,   627,   664,   684,
     685,   688,   693,   700,   701,   702,   705,   710,   725,   734,
     739,   743,   750,   759,   768,   775,   782,   791,   796,   801,
     808,   819,   823,   830,   833,   838,   845,   849,   856,   860,
     867,   874,   881,   888,   895,   902,   909,   916,   921,   926,
     931,   938,   941,   946,   954,   958,   963,   974,   981,   988,
     995,  1002,  1009,  1016,  1023,  1030,  1037,  1044,  1051,  1055,
    1060,  1065,  1070,  1075,  1082,  1086,  1093
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"identifier\"", "\"string\"",
  "\"integer\"", "\"section name\"", "\"source name\"",
  "\"binary object\"", "'('", "')'", "'{'", "'}'", "'['", "']'", "'='",
  "','", "';'", "':'", "'>'", "'.'", "\"..\"", "'~'", "'&'", "'|'", "'<'",
  "'!'", "\"&&\"", "\"||\"", "\">=\"", "\"<=\"", "\"==\"", "\"!=\"",
  "\"**\"", "\"<<\"", "\">>\"", "\"integer size\"", "\"options\"",
  "\"constants\"", "\"sources\"", "\"filters\"", "\"section\"",
  "\"extern\"", "\"from\"", "\"raw\"", "\"load\"", "\"jump\"", "\"call\"",
  "\"mode\"", "\"erase\"", "\"all\"", "\"if\"", "\"else\"", "\"defined\"",
  "\"info\"", "\"warning\"", "\"error\"", "\"sizeof\"", "\"dcd\"",
  "\"hab\"", "\"ivt\"", "\"unsecure\"", "\"reset\"", "\"jump_sp\"",
  "\"enable\"", "\"keyblob\"", "\"encrypt\"", "\"keywrap\"", "'^'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "UNARY_OP", "$accept", "command_file",
  "blocks_list", "pre_section_block", "options_block", "constants_block",
  "const_def_list", "const_def_list_elem", "const_def", "keyblob_block",
  "keyblob_def_list", "keyblob_def_list_elem", "keyblob_def",
  "sources_block", "source_def_list", "source_def_list_elem", "source_def",
  "source_attrs_opt", "source_attr_list", "source_attr_list_elem",
  "section_defs", "section_def", "section_options_opt",
  "source_attr_list_opt", "section_contents", "full_stmt_list",
  "full_stmt_list_elem", "basic_stmt_list", "basic_stmt_list_elem",
  "basic_stmt", "load_stmt", "load_opt", "load_data", "section_list",
  "section_list_elem", "load_target_opt", "load_target", "ivt_def",
  "assignment_list_opt", "call_stmt", "jump_sp_stmt", "call_or_jump",
  "call_target", "call_arg_opt", "erase_stmt", "mem_opt", "from_stmt",
  "encrypt_stmt", "keywrap_stmt", "mode_stmt", "reset_stmt", "enable_stmt",
  "message_stmt", "if_stmt", "else_opt", "address_or_range", "const_expr",
  "bool_expr", "int_const_expr", "symbol_ref", "expr", "unary_expr",
  "int_value", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,    40,
      41,   123,   125,    91,    93,    61,    44,    59,    58,    62,
      46,   264,   126,    38,   124,    60,    33,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,    94,    43,
      45,    42,    47,    37,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    77,    77,    78,    78,    78,    78,    79,
      80,    81,    81,    82,    82,    83,    84,    85,    85,    86,
      86,    87,    88,    89,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    94,    95,    95,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   101,   101,   101,   101,   101,
     101,   102,   102,   103,   103,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   105,   106,   106,   107,   107,   107,
     107,   107,   107,   107,   107,   108,   108,   109,   109,   110,
     110,   111,   111,   112,   113,   113,   114,   114,   115,   116,
     116,   117,   117,   118,   118,   118,   119,   119,   119,   120,
     120,   121,   122,   123,   124,   125,   126,   127,   127,   127,
     128,   129,   129,   129,   130,   130,   131,   131,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   133,   134,   134,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   136,   136,   137
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,     1,     1,     1,     1,     4,
       4,     1,     2,     2,     0,     3,     7,     1,     2,     1,
       0,     3,     4,     1,     2,     3,     0,     3,     6,     3,
       0,     1,     3,     3,     1,     2,     6,     2,     0,     1,
       0,     3,     3,     1,     2,     2,     1,     1,     1,     1,
       0,     1,     2,     2,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     0,     1,     1,     1,
       1,     3,     4,     1,     1,     1,     3,     1,     2,     2,
       0,     1,     1,     4,     1,     0,     3,     4,     4,     1,
       1,     1,     1,     3,     2,     0,     2,     3,     3,     1,
       0,     5,     7,     7,     2,     1,     3,     2,     2,     2,
       6,     4,     2,     0,     1,     3,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     4,     3,
       4,     1,     3,     2,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     4,     4,     4,     2,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     3,     5,     6,
       8,     7,    14,    14,    26,     0,     1,     0,     4,     2,
      34,     0,     0,    11,     0,     0,     0,     0,    23,    30,
     135,   156,     0,     0,     0,     0,     0,     0,     0,   136,
     131,   148,   134,     0,    35,     0,     9,    12,    13,    10,
       0,    22,    24,     0,     0,     0,     0,   133,     0,   154,
     155,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,   135,   117,     0,     0,     0,
      15,   116,   118,    27,     0,     0,     0,    31,    25,   132,
     150,     0,     0,     0,    20,   149,   143,   144,   142,   146,
     147,   145,   137,   138,   139,   140,   141,    40,     0,     0,
       0,   131,   127,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,     0,   152,   153,   151,    85,
       0,    17,    19,    39,    37,     0,     0,   129,     0,   120,
     119,   125,   126,   121,   122,   123,   124,     0,    33,    32,
      84,     0,    16,    18,    50,     0,    36,   128,   130,    28,
      21,     0,    66,    90,    89,     0,   100,     0,     0,     0,
       0,     0,   105,     0,   100,     0,     0,     0,    43,     0,
      56,    57,    62,     0,    58,    46,    47,    48,    59,    61,
      63,    60,    49,    68,    77,    69,    73,     0,     0,     0,
      70,    75,    74,    67,     0,    65,     0,   104,   135,     0,
       0,    96,   114,     0,   107,   108,   109,     0,     0,    99,
       0,     0,     0,    42,    44,    45,    91,    95,    92,     0,
      78,    85,    41,     0,     0,    55,    80,    98,    97,     0,
      50,    95,    95,   106,     0,     0,     0,    86,     0,     0,
      76,    71,     0,    51,     0,    54,     0,    64,   115,     0,
      87,    88,     0,     0,    94,     0,    72,    83,   101,    52,
      53,    81,    79,    82,   113,    55,    55,    93,     0,   110,
       0,     0,    50,   112,   102,   103,     0,   111
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,     9,    22,    23,    24,    10,
     130,   131,   132,    11,    27,    28,    29,    54,   150,    87,
      19,    20,   108,   134,   156,   177,   178,   252,   253,   179,
     180,   206,   199,   200,   201,   257,   272,   202,   151,   181,
     182,   183,   227,   247,   184,   210,   185,   186,   187,   188,
     189,   190,   191,   192,   279,   211,    80,    81,    82,    39,
      40,    41,    42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -226
static const yytype_int16 yypact[] =
{
     184,    19,    56,    74,   120,   148,    98,  -226,  -226,  -226,
    -226,  -226,   139,   139,   161,   116,  -226,   160,  -226,   133,
    -226,   163,    85,  -226,   140,   105,   164,   135,  -226,   172,
    -226,  -226,   166,   116,   185,   178,   116,   116,   179,  -226,
     279,  -226,  -226,   116,  -226,     9,  -226,  -226,  -226,  -226,
      17,  -226,  -226,   187,   183,   201,   142,  -226,    87,  -226,
    -226,   197,   173,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   208,   218,  -226,    29,    29,   219,
    -226,   511,  -226,  -226,   220,   215,    93,  -226,  -226,  -226,
    -226,   223,    15,   229,   233,  -226,   295,   126,   147,     4,
       4,   287,    40,    40,   226,   226,   226,   187,   237,   243,
     467,   142,  -226,   255,    29,    29,    29,    29,    29,    29,
      29,    29,   116,     9,  -226,   187,  -226,  -226,  -226,   187,
      72,  -226,  -226,   248,  -226,    57,   256,  -226,   257,  -226,
    -226,   313,   313,  -226,  -226,  -226,  -226,   261,  -226,  -226,
     248,   262,  -226,  -226,   398,     1,  -226,  -226,  -226,  -226,
    -226,   267,   272,  -226,  -226,   116,    45,    29,   275,   278,
     280,   107,  -226,   116,   283,   274,   286,   189,  -226,   299,
    -226,  -226,  -226,   123,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,    13,  -226,   294,   308,   301,
       6,  -226,  -226,  -226,   281,  -226,     1,  -226,   269,   273,
     276,  -226,   303,   482,  -226,  -226,  -226,   116,   123,  -226,
     116,   116,   116,  -226,  -226,  -226,   166,   316,  -226,    58,
    -226,   187,  -226,    58,   320,   470,   312,  -226,  -226,   116,
     398,   316,   316,  -226,   323,   331,    86,  -226,    37,   336,
    -226,  -226,   324,  -226,   337,  -226,   113,  -226,  -226,   214,
    -226,  -226,   342,   344,  -226,   352,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,   311,   470,   470,  -226,    18,  -226,
     349,   369,   398,  -226,  -226,  -226,   242,  -226
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -226,  -226,  -226,   368,  -226,  -226,   363,   102,  -226,  -226,
    -226,   247,  -226,  -226,  -226,   355,  -226,  -226,   -42,   259,
    -226,   366,  -226,  -226,  -226,  -225,  -176,  -131,  -180,   154,
    -226,  -226,   186,   162,   157,  -226,  -226,  -226,   168,  -226,
    -226,   222,   191,   -70,  -226,   227,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,    59,  -226,  -200,   284,   -75,   -15,   361,
     403,  -226,  -226
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -100
static const yytype_int16 yytable[] =
{
      38,   224,   110,   112,    30,   193,    31,   194,   195,   196,
      33,    86,    75,    76,    31,   259,    32,   241,    77,    34,
     243,    83,   233,   197,    62,   127,   229,    34,    74,   282,
      12,    55,    75,    55,    31,    78,    32,    65,    77,   139,
     140,   141,   142,   143,   144,   145,   146,    34,   208,   234,
      31,   266,    32,   233,    33,    78,   273,   286,    35,    84,
      62,   198,    79,    34,   194,   133,    35,    13,   154,   167,
      36,    37,   269,    69,    70,    71,    72,    73,    36,    37,
     197,   129,    79,   224,   152,    14,    35,   155,    21,    30,
      91,    31,   213,    32,    92,    33,   264,    46,    36,    37,
     269,   269,    35,   124,    34,    34,   209,   147,    21,   125,
     224,    71,    72,    73,    36,    37,    30,    49,    31,    30,
      32,    31,    33,    32,    47,    33,    30,    47,    31,    15,
     226,    34,    33,   271,    34,     1,     2,     3,    26,    17,
     203,    34,    21,    35,   280,   281,    62,    51,    16,    63,
     207,   212,    90,   163,   164,    36,    37,    48,   218,    65,
      66,    67,    62,     4,    26,    63,    64,    62,   228,    43,
      35,   260,   261,    35,    17,    65,    66,    67,    45,    50,
      35,    53,    36,    37,    55,    36,    37,    58,    57,    61,
      85,   203,    36,    37,    68,    69,    70,    71,    72,    73,
      88,   223,   212,   228,    89,   212,   244,   245,    94,    95,
      68,    69,    70,    71,    72,    73,    69,    70,    71,    72,
      73,     1,     2,     3,   258,   107,   274,   109,   113,   122,
     123,   265,   161,   126,   162,   163,   164,   165,   166,   128,
     167,   212,   129,   168,   169,   170,    62,   135,   171,     4,
     136,   172,   173,   174,   287,   175,   176,   161,   138,   162,
     163,   164,   165,   166,   125,   167,   157,   158,   168,   169,
     170,   159,   160,   171,   204,   205,   172,   173,   174,   214,
     175,   176,   215,   221,   216,   161,   219,   162,   163,   164,
     165,   166,   235,   167,   255,   222,   168,   169,   170,    62,
     230,   171,    63,    64,   172,   173,   174,    62,   175,   176,
      63,   255,    65,    66,    67,    62,   225,   231,   232,   -99,
      65,    66,    67,   237,   239,   246,   238,   251,    65,    66,
      67,   256,   114,   262,   255,   255,   268,   283,   115,   255,
     255,   263,   118,   119,   120,   121,   267,    68,    69,    70,
      71,    72,    73,   275,   270,   276,    69,    70,    71,    72,
      73,   284,   277,   278,    69,    70,    71,    72,    73,   162,
     163,   164,   165,   166,    18,   167,    25,   153,   168,   169,
     170,   285,    52,   171,   149,    44,   172,   173,   174,   254,
     250,   248,   236,   217,   162,   163,   164,   165,   166,   249,
     167,   220,     0,   168,   169,   170,   254,   148,   171,   242,
       0,   172,   173,   174,   162,   163,   164,   165,   166,    93,
     167,     0,     0,   168,   169,   170,     0,     0,   171,   254,
     254,   172,   173,   174,   254,   254,    56,     0,     0,    59,
      60,   161,     0,   162,   163,   164,   165,   166,     0,   167,
       0,     0,   168,   169,   170,     0,     0,   171,     0,     0,
     172,   173,   174,     0,   175,   176,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   137,     0,     0,
     111,     0,     0,     0,     0,     0,   114,     0,     0,     0,
       0,     0,   115,   240,   116,   117,   118,   119,   120,   121,
       0,   114,     0,     0,     0,     0,     0,   115,     0,   116,
     117,   118,   119,   120,   121,   162,   163,   164,   165,   166,
       0,   167,     0,     0,   168,   169,   170,     0,     0,   171,
     114,     0,   172,   173,   174,     0,   115,     0,   116,   117,
     118,   119,   120,   121
};

static const yytype_int16 yycheck[] =
{
      15,   177,    77,    78,     3,     4,     5,     6,     7,     8,
       9,    53,     3,     4,     5,   240,     7,   217,     9,    18,
     220,     4,    16,    22,    20,    10,    13,    18,    43,    11,
      11,    18,     3,    18,     5,    26,     7,    33,     9,   114,
     115,   116,   117,   118,   119,   120,   121,    18,     3,    43,
       5,    14,     7,    16,     9,    26,   256,   282,    57,    42,
      20,    60,    53,    18,     6,   107,    57,    11,    11,    51,
      69,    70,   252,    69,    70,    71,    72,    73,    69,    70,
      22,     9,    53,   259,    12,    11,    57,    30,     3,     3,
       3,     5,   167,     7,     7,     9,    10,    12,    69,    70,
     280,   281,    57,    10,    18,    18,    61,   122,     3,    16,
     286,    71,    72,    73,    69,    70,     3,    12,     5,     3,
       7,     5,     9,     7,    22,     9,     3,    25,     5,     9,
       7,    18,     9,    20,    18,    37,    38,    39,     3,    41,
     155,    18,     3,    57,   275,   276,    20,    12,     0,    23,
     165,   166,    10,    46,    47,    69,    70,    17,   173,    33,
      34,    35,    20,    65,     3,    23,    24,    20,   183,     9,
      57,   241,   242,    57,    41,    33,    34,    35,    15,    15,
      57,     9,    69,    70,    18,    69,    70,     9,     3,    10,
       3,   206,    69,    70,    68,    69,    70,    71,    72,    73,
      17,    12,   217,   218,     3,   220,   221,   222,    11,    36,
      68,    69,    70,    71,    72,    73,    69,    70,    71,    72,
      73,    37,    38,    39,   239,    17,    12,     9,     9,     9,
      15,   246,    43,    10,    45,    46,    47,    48,    49,    10,
      51,   256,     9,    54,    55,    56,    20,    10,    59,    65,
       7,    62,    63,    64,    12,    66,    67,    43,     3,    45,
      46,    47,    48,    49,    16,    51,    10,    10,    54,    55,
      56,    10,    10,    59,     7,     3,    62,    63,    64,     4,
      66,    67,     4,     9,     4,    43,     3,    45,    46,    47,
      48,    49,    11,    51,   235,     9,    54,    55,    56,    20,
       6,    59,    23,    24,    62,    63,    64,    20,    66,    67,
      23,   252,    33,    34,    35,    20,    17,     9,    17,    50,
      33,    34,    35,    50,    21,     9,    50,     7,    33,    34,
      35,    19,    19,    10,   275,   276,    12,   278,    25,   280,
     281,    10,    29,    30,    31,    32,    10,    68,    69,    70,
      71,    72,    73,    11,    17,    11,    69,    70,    71,    72,
      73,    12,    10,    52,    69,    70,    71,    72,    73,    45,
      46,    47,    48,    49,     6,    51,    13,   130,    54,    55,
      56,    12,    27,    59,   125,    19,    62,    63,    64,   235,
     233,   229,   206,   171,    45,    46,    47,    48,    49,   231,
      51,   174,    -1,    54,    55,    56,   252,   123,    59,   218,
      -1,    62,    63,    64,    45,    46,    47,    48,    49,    58,
      51,    -1,    -1,    54,    55,    56,    -1,    -1,    59,   275,
     276,    62,    63,    64,   280,   281,    33,    -1,    -1,    36,
      37,    43,    -1,    45,    46,    47,    48,    49,    -1,    51,
      -1,    -1,    54,    55,    56,    -1,    -1,    59,    -1,    -1,
      62,    63,    64,    -1,    66,    67,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    10,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    25,    11,    27,    28,    29,    30,    31,    32,
      -1,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,
      28,    29,    30,    31,    32,    45,    46,    47,    48,    49,
      -1,    51,    -1,    -1,    54,    55,    56,    -1,    -1,    59,
      19,    -1,    62,    63,    64,    -1,    25,    -1,    27,    28,
      29,    30,    31,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,    39,    65,    76,    77,    78,    79,    80,
      84,    88,    11,    11,    11,     9,     0,    41,    78,    95,
      96,     3,    81,    82,    83,    81,     3,    89,    90,    91,
       3,     5,     7,     9,    18,    57,    69,    70,   133,   134,
     135,   136,   137,     9,    96,    15,    12,    82,    17,    12,
      15,    12,    90,     9,    92,    18,   135,     3,     9,   135,
     135,    10,    20,    23,    24,    33,    34,    35,    68,    69,
      70,    71,    72,    73,   133,     3,     4,     9,    26,    53,
     131,   132,   133,     4,    42,     3,    93,    94,    17,     3,
      10,     3,     7,   134,    11,    36,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,    17,    97,     9,
     132,   135,   132,     9,    19,    25,    27,    28,    29,    30,
      31,    32,     9,    15,    10,    16,    10,    10,    10,     9,
      85,    86,    87,    93,    98,    10,     7,    10,     3,   132,
     132,   132,   132,   132,   132,   132,   132,   133,   131,    94,
      93,   113,    12,    86,    11,    30,    99,    10,    10,    10,
      10,    43,    45,    46,    47,    48,    49,    51,    54,    55,
      56,    59,    62,    63,    64,    66,    67,   100,   101,   104,
     105,   114,   115,   116,   119,   121,   122,   123,   124,   125,
     126,   127,   128,     4,     6,     7,     8,    22,    60,   107,
     108,   109,   112,   133,     7,     3,   106,   133,     3,    61,
     120,   130,   133,   132,     4,     4,     4,   116,   133,     3,
     120,     9,     9,    12,   101,    17,     7,   117,   133,    13,
       6,     9,    17,    16,    43,    11,   107,    50,    50,    21,
      11,   130,   117,   130,   133,   133,     9,   118,   108,   113,
     109,     7,   102,   103,   104,   128,    19,   110,   133,   100,
     118,   118,    10,    10,    10,   133,    14,    10,    12,   103,
      17,    20,   111,   130,    12,    11,    11,    10,    52,   129,
     102,   102,    11,   128,    12,    12,   100,    12
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
      yyerror (&yylloc, lexer, resultAST, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, lexer)
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
		  Type, Value, Location, lexer, resultAST); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ElftosbLexer * lexer, CommandFileASTNode ** resultAST)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, lexer, resultAST)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    ElftosbLexer * lexer;
    CommandFileASTNode ** resultAST;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (lexer);
  YYUSE (resultAST);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ElftosbLexer * lexer, CommandFileASTNode ** resultAST)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, lexer, resultAST)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    ElftosbLexer * lexer;
    CommandFileASTNode ** resultAST;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, lexer, resultAST);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, ElftosbLexer * lexer, CommandFileASTNode ** resultAST)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, lexer, resultAST)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    ElftosbLexer * lexer;
    CommandFileASTNode ** resultAST;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , lexer, resultAST);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, lexer, resultAST); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, ElftosbLexer * lexer, CommandFileASTNode ** resultAST)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, lexer, resultAST)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    ElftosbLexer * lexer;
    CommandFileASTNode ** resultAST;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (lexer);
  YYUSE (resultAST);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* "\"identifier\"" */
#line 172 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
	{ delete (yyvaluep->m_str); };
#line 1521 "/Users/MADUser1/Library/Developer/Xcode/DerivedData/elftosb-dxrbhxxtpndhpgdxujwltedpntjq/Build/Intermediates/elftosb.build/Debug/elftosb.build/DerivedSources/elftosb_parser.tab.cpp"
	break;
      case 4: /* "\"string\"" */
#line 172 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
	{ delete (yyvaluep->m_str); };
#line 1526 "/Users/MADUser1/Library/Developer/Xcode/DerivedData/elftosb-dxrbhxxtpndhpgdxujwltedpntjq/Build/Intermediates/elftosb.build/Debug/elftosb.build/DerivedSources/elftosb_parser.tab.cpp"
	break;
      case 5: /* "\"integer\"" */
#line 172 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
	{ delete (yyvaluep->m_int); };
#line 1531 "/Users/MADUser1/Library/Developer/Xcode/DerivedData/elftosb-dxrbhxxtpndhpgdxujwltedpntjq/Build/Intermediates/elftosb.build/Debug/elftosb.build/DerivedSources/elftosb_parser.tab.cpp"
	break;
      case 6: /* "\"section name\"" */
#line 172 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
	{ delete (yyvaluep->m_str); };
#line 1536 "/Users/MADUser1/Library/Developer/Xcode/DerivedData/elftosb-dxrbhxxtpndhpgdxujwltedpntjq/Build/Intermediates/elftosb.build/Debug/elftosb.build/DerivedSources/elftosb_parser.tab.cpp"
	break;
      case 7: /* "\"source name\"" */
#line 172 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
	{ delete (yyvaluep->m_str); };
#line 1541 "/Users/MADUser1/Library/Developer/Xcode/DerivedData/elftosb-dxrbhxxtpndhpgdxujwltedpntjq/Build/Intermediates/elftosb.build/Debug/elftosb.build/DerivedSources/elftosb_parser.tab.cpp"
	break;
      case 8: /* "\"binary object\"" */
#line 172 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
	{ delete (yyvaluep->m_blob); };
#line 1546 "/Users/MADUser1/Library/Developer/Xcode/DerivedData/elftosb-dxrbhxxtpndhpgdxujwltedpntjq/Build/Intermediates/elftosb.build/Debug/elftosb.build/DerivedSources/elftosb_parser.tab.cpp"
	break;
      case 36: /* "\"integer size\"" */
#line 172 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
	{ delete (yyvaluep->m_int); };
#line 1551 "/Users/MADUser1/Library/Developer/Xcode/DerivedData/elftosb-dxrbhxxtpndhpgdxujwltedpntjq/Build/Intermediates/elftosb.build/Debug/elftosb.build/DerivedSources/elftosb_parser.tab.cpp"
	break;

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
int yyparse (ElftosbLexer * lexer, CommandFileASTNode ** resultAST);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






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
yyparse (ElftosbLexer * lexer, CommandFileASTNode ** resultAST)
#else
int
yyparse (lexer, resultAST)
    ElftosbLexer * lexer;
    CommandFileASTNode ** resultAST;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;

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

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

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
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 177 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							CommandFileASTNode * commandFile = new CommandFileASTNode();
							commandFile->setBlocks(dynamic_cast<ListASTNode*>((yyvsp[(1) - (2)].m_ast)));
							commandFile->setSections(dynamic_cast<ListASTNode*>((yyvsp[(2) - (2)].m_ast)));
							commandFile->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
							*resultAST = commandFile;
						;}
    break;

  case 3:
#line 187 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ListASTNode * list = new ListASTNode();
							list->appendNode((yyvsp[(1) - (1)].m_ast));
							(yyval.m_ast) = list;
						;}
    break;

  case 4:
#line 193 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							dynamic_cast<ListASTNode*>((yyvsp[(1) - (2)].m_ast))->appendNode((yyvsp[(2) - (2)].m_ast));
							(yyval.m_ast) = (yyvsp[(1) - (2)].m_ast);
						;}
    break;

  case 5:
#line 200 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 6:
#line 201 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 7:
#line 202 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 8:
#line 203 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 9:
#line 207 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new OptionsBlockASTNode(dynamic_cast<ListASTNode *>((yyvsp[(3) - (4)].m_ast)));
							;}
    break;

  case 10:
#line 213 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new ConstantsBlockASTNode(dynamic_cast<ListASTNode *>((yyvsp[(3) - (4)].m_ast)));
							;}
    break;

  case 11:
#line 219 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ListASTNode * list = new ListASTNode();
								list->appendNode((yyvsp[(1) - (1)].m_ast));
								(yyval.m_ast) = list;
							;}
    break;

  case 12:
#line 225 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								dynamic_cast<ListASTNode*>((yyvsp[(1) - (2)].m_ast))->appendNode((yyvsp[(2) - (2)].m_ast));
								(yyval.m_ast) = (yyvsp[(1) - (2)].m_ast);
							;}
    break;

  case 13:
#line 231 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (2)].m_ast); ;}
    break;

  case 14:
#line 232 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 15:
#line 236 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new AssignmentASTNode((yyvsp[(1) - (3)].m_str), (yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 16:
#line 243 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							KeyblobBlockASTNode * keyblob = new KeyblobBlockASTNode(dynamic_cast<ListASTNode *>((yyvsp[(6) - (7)].m_ast)));
							keyblob->setKeyblobNumberExpr(dynamic_cast<ExprASTNode *>((yyvsp[(3) - (7)].m_ast)));
							(yyval.m_ast) = keyblob;
						;}
    break;

  case 17:
#line 251 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ListASTNode * list = new ListASTNode();
							list->appendNode((yyvsp[(1) - (1)].m_ast));
							(yyval.m_ast) = list;
						;}
    break;

  case 18:
#line 257 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							dynamic_cast<ListASTNode*>((yyvsp[(1) - (2)].m_ast))->appendNode((yyvsp[(2) - (2)].m_ast));
							(yyval.m_ast) = (yyvsp[(1) - (2)].m_ast);
						;}
    break;

  case 19:
#line 263 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 20:
#line 264 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 21:
#line 268 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								KeyblobEntryASTNode * entry = new KeyblobEntryASTNode();
								if ((yyvsp[(2) - (3)].m_ast))
								{
									entry->setFieldAssignments(dynamic_cast<ListASTNode*>((yyvsp[(2) - (3)].m_ast)));
								}
								entry->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
								(yyval.m_ast) = entry;
							;}
    break;

  case 22:
#line 280 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							(yyval.m_ast) = new SourcesBlockASTNode(dynamic_cast<ListASTNode *>((yyvsp[(3) - (4)].m_ast)));
						;}
    break;

  case 23:
#line 286 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ListASTNode * list = new ListASTNode();
							list->appendNode((yyvsp[(1) - (1)].m_ast));
							(yyval.m_ast) = list;
						;}
    break;

  case 24:
#line 292 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							dynamic_cast<ListASTNode*>((yyvsp[(1) - (2)].m_ast))->appendNode((yyvsp[(2) - (2)].m_ast));
							(yyval.m_ast) = (yyvsp[(1) - (2)].m_ast);
						;}
    break;

  case 25:
#line 300 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								// tell the lexer that this is the name of a source file
								SourceDefASTNode * node = dynamic_cast<SourceDefASTNode*>((yyvsp[(1) - (3)].m_ast));
								if ((yyvsp[(2) - (3)].m_ast))
								{
									node->setAttributes(dynamic_cast<ListASTNode*>((yyvsp[(2) - (3)].m_ast)));
								}
								node->setLocation(node->getLocation(), (yylsp[(3) - (3)]));
								lexer->addSourceName(node->getName());
								(yyval.m_ast) = (yyvsp[(1) - (3)].m_ast);
							;}
    break;

  case 26:
#line 311 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 27:
#line 315 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new PathSourceDefASTNode((yyvsp[(1) - (3)].m_str), (yyvsp[(3) - (3)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 28:
#line 320 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new ExternSourceDefASTNode((yyvsp[(1) - (6)].m_str), dynamic_cast<ExprASTNode*>((yyvsp[(5) - (6)].m_ast)));
								(yyval.m_ast)->setLocation((yylsp[(1) - (6)]), (yylsp[(6) - (6)]));
							;}
    break;

  case 29:
#line 327 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(2) - (3)].m_ast); ;}
    break;

  case 30:
#line 328 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 31:
#line 333 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ListASTNode * list = new ListASTNode();
								list->appendNode((yyvsp[(1) - (1)].m_ast));
								(yyval.m_ast) = list;
							;}
    break;

  case 32:
#line 339 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								dynamic_cast<ListASTNode*>((yyvsp[(1) - (3)].m_ast))->appendNode((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = (yyvsp[(1) - (3)].m_ast);
							;}
    break;

  case 33:
#line 347 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new AssignmentASTNode((yyvsp[(1) - (3)].m_str), (yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 34:
#line 354 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ListASTNode * list = new ListASTNode();
								list->appendNode((yyvsp[(1) - (1)].m_ast));
								(yyval.m_ast) = list;
							;}
    break;

  case 35:
#line 360 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								dynamic_cast<ListASTNode*>((yyvsp[(1) - (2)].m_ast))->appendNode((yyvsp[(2) - (2)].m_ast));
								(yyval.m_ast) = (yyvsp[(1) - (2)].m_ast);
							;}
    break;

  case 36:
#line 367 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								SectionContentsASTNode * sectionNode = dynamic_cast<SectionContentsASTNode*>((yyvsp[(6) - (6)].m_ast));
								if (sectionNode)
								{
									ExprASTNode * exprNode = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (6)].m_ast));
									sectionNode->setSectionNumberExpr(exprNode);
									sectionNode->setOptions(dynamic_cast<ListASTNode*>((yyvsp[(4) - (6)].m_ast)));
									sectionNode->setLocation((yylsp[(1) - (6)]), sectionNode->getLocation());
								}
								(yyval.m_ast) = (yyvsp[(6) - (6)].m_ast);
							;}
    break;

  case 37:
#line 382 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(2) - (2)].m_ast);
							;}
    break;

  case 38:
#line 386 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = NULL;
							;}
    break;

  case 39:
#line 393 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(1) - (1)].m_ast);
							;}
    break;

  case 40:
#line 397 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = NULL;
							;}
    break;

  case 41:
#line 404 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								DataSectionContentsASTNode * dataSection = new DataSectionContentsASTNode((yyvsp[(2) - (3)].m_ast));
								dataSection->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
								(yyval.m_ast) = dataSection;
							;}
    break;

  case 42:
#line 410 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ListASTNode * listNode = dynamic_cast<ListASTNode*>((yyvsp[(2) - (3)].m_ast));
								(yyval.m_ast) = new BootableSectionContentsASTNode(listNode);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 43:
#line 418 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ListASTNode * list = new ListASTNode();
								list->appendNode((yyvsp[(1) - (1)].m_ast));
								(yyval.m_ast) = list;
							;}
    break;

  case 44:
#line 424 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								dynamic_cast<ListASTNode*>((yyvsp[(1) - (2)].m_ast))->appendNode((yyvsp[(2) - (2)].m_ast));
								(yyval.m_ast) = (yyvsp[(1) - (2)].m_ast);
							;}
    break;

  case 45:
#line 431 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (2)].m_ast); ;}
    break;

  case 46:
#line 432 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 47:
#line 433 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 48:
#line 434 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 49:
#line 435 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 50:
#line 436 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 51:
#line 440 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ListASTNode * list = new ListASTNode();
								list->appendNode((yyvsp[(1) - (1)].m_ast));
								(yyval.m_ast) = list;
							;}
    break;

  case 52:
#line 446 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								dynamic_cast<ListASTNode*>((yyvsp[(1) - (2)].m_ast))->appendNode((yyvsp[(2) - (2)].m_ast));
								(yyval.m_ast) = (yyvsp[(1) - (2)].m_ast);
							;}
    break;

  case 53:
#line 453 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (2)].m_ast); ;}
    break;

  case 54:
#line 454 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 55:
#line 455 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 56:
#line 458 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 57:
#line 459 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 58:
#line 460 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 59:
#line 461 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 60:
#line 462 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 61:
#line 463 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 62:
#line 464 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 63:
#line 465 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 64:
#line 469 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								LoadStatementASTNode * stmt = new LoadStatementASTNode();
								stmt->setLoadOption((yyvsp[(2) - (4)].m_ast));
								stmt->setData((yyvsp[(3) - (4)].m_ast));
								stmt->setTarget((yyvsp[(4) - (4)].m_ast));
								// set char locations for the statement
								if ((yyvsp[(4) - (4)].m_ast))
								{
									stmt->setLocation((yylsp[(1) - (4)]), (yylsp[(4) - (4)]));
								}
								else
								{
									stmt->setLocation((yylsp[(1) - (4)]), (yylsp[(3) - (4)]));
								}
								(yyval.m_ast) = stmt;
							;}
    break;

  case 65:
#line 488 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new StringConstASTNode((yyvsp[(1) - (1)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 66:
#line 492 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 67:
#line 496 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(1) - (1)].m_ast);
							;}
    break;

  case 68:
#line 500 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new StringConstASTNode((yyvsp[(1) - (1)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 69:
#line 505 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new SourceASTNode((yyvsp[(1) - (1)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 70:
#line 510 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new SectionMatchListASTNode(dynamic_cast<ListASTNode*>((yyvsp[(1) - (1)].m_ast)));
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 71:
#line 515 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new SectionMatchListASTNode(dynamic_cast<ListASTNode*>((yyvsp[(1) - (3)].m_ast)), (yyvsp[(3) - (3)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 72:
#line 520 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new SectionMatchListASTNode(dynamic_cast<ListASTNode*>((yyvsp[(3) - (4)].m_ast)), (yyvsp[(1) - (4)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (4)]), (yylsp[(4) - (4)]));
							;}
    break;

  case 73:
#line 525 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new BlobConstASTNode((yyvsp[(1) - (1)].m_blob));
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 74:
#line 530 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							;}
    break;

  case 75:
#line 535 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ListASTNode * list = new ListASTNode();
								list->appendNode((yyvsp[(1) - (1)].m_ast));
								(yyval.m_ast) = list;
							;}
    break;

  case 76:
#line 541 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								dynamic_cast<ListASTNode*>((yyvsp[(1) - (3)].m_ast))->appendNode((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = (yyvsp[(1) - (3)].m_ast);
							;}
    break;

  case 77:
#line 549 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new SectionASTNode((yyvsp[(1) - (1)].m_str), SectionASTNode::kInclude);
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 78:
#line 554 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new SectionASTNode((yyvsp[(2) - (2)].m_str), SectionASTNode::kExclude);
								(yyval.m_ast)->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
							;}
    break;

  case 79:
#line 561 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(2) - (2)].m_ast);
							;}
    break;

  case 80:
#line 565 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new NaturalLocationASTNode();
//								$$->setLocation();
							;}
    break;

  case 81:
#line 572 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new NaturalLocationASTNode();
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 82:
#line 577 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(1) - (1)].m_ast);
							;}
    break;

  case 83:
#line 583 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								IVTConstASTNode * ivt = new IVTConstASTNode();
								if ((yyvsp[(3) - (4)].m_ast))
								{
									ivt->setFieldAssignments(dynamic_cast<ListASTNode*>((yyvsp[(3) - (4)].m_ast)));
								}
								ivt->setLocation((yylsp[(1) - (4)]), (yylsp[(4) - (4)]));
								(yyval.m_ast) = ivt;
							;}
    break;

  case 84:
#line 594 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 85:
#line 595 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 86:
#line 599 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								CallStatementASTNode * stmt = new CallStatementASTNode();
								switch ((yyvsp[(1) - (3)].m_num))
								{
									case 1:
										stmt->setCallType(CallStatementASTNode::kCallType);
										break;
									case 2:
										stmt->setCallType(CallStatementASTNode::kJumpType);
										break;
									default:
										yyerror(&yylloc, lexer, resultAST, "invalid call_or_jump value");
										YYABORT;
										break;
								}
								stmt->setTarget((yyvsp[(2) - (3)].m_ast));
								stmt->setArgument((yyvsp[(3) - (3)].m_ast));
								stmt->setIsHAB(false);
								if ((yyvsp[(3) - (3)].m_ast))
								{
									stmt->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
								}
								else
								{
									stmt->setLocation((yylsp[(1) - (3)]), (yylsp[(2) - (3)]));
								}
								(yyval.m_ast) = stmt;
							;}
    break;

  case 87:
#line 628 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								if (!elftosb::g_enableHABSupport)
								{
									yyerror(&yylloc, lexer, resultAST, "HAB features not supported with the selected family");
									YYABORT;
								}
								
								CallStatementASTNode * stmt = new CallStatementASTNode();
								switch ((yyvsp[(2) - (4)].m_num))
								{
									case 1:
										stmt->setCallType(CallStatementASTNode::kCallType);
										break;
									case 2:
										stmt->setCallType(CallStatementASTNode::kJumpType);
										break;
									default:
										yyerror(&yylloc, lexer, resultAST, "invalid call_or_jump value");
										YYABORT;
										break;
								}
								stmt->setTarget((yyvsp[(3) - (4)].m_ast));
								stmt->setArgument((yyvsp[(4) - (4)].m_ast));
								stmt->setIsHAB(true);
								if ((yyvsp[(4) - (4)].m_ast))
								{
									stmt->setLocation((yylsp[(1) - (4)]), (yylsp[(4) - (4)]));
								}
								else
								{
									stmt->setLocation((yylsp[(1) - (4)]), (yylsp[(3) - (4)]));
								}
								(yyval.m_ast) = stmt;
							;}
    break;

  case 88:
#line 665 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							CallStatementASTNode * stmt = new CallStatementASTNode();
							stmt->setCallType(CallStatementASTNode::kJumpType);
							stmt->setStackPointer((yyvsp[(2) - (4)].m_ast));
							stmt->setTarget((yyvsp[(3) - (4)].m_ast));
							stmt->setArgument((yyvsp[(4) - (4)].m_ast));
							stmt->setIsHAB(false);
							if ((yyvsp[(4) - (4)].m_ast))
							{
								stmt->setLocation((yylsp[(1) - (4)]), (yylsp[(4) - (4)]));
							}
							else
							{
								stmt->setLocation((yylsp[(1) - (4)]), (yylsp[(3) - (4)]));
							}
							(yyval.m_ast) = stmt;
						;}
    break;

  case 89:
#line 684 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_num) = 1; ;}
    break;

  case 90:
#line 685 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_num) = 2; ;}
    break;

  case 91:
#line 689 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new SymbolASTNode(NULL, (yyvsp[(1) - (1)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 92:
#line 694 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new AddressRangeASTNode((yyvsp[(1) - (1)].m_ast), NULL);
								(yyval.m_ast)->setLocation((yyvsp[(1) - (1)].m_ast));
							;}
    break;

  case 93:
#line 700 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(2) - (3)].m_ast); ;}
    break;

  case 94:
#line 701 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 95:
#line 702 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 96:
#line 706 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new EraseStatementASTNode((yyvsp[(2) - (2)].m_ast));
								(yyval.m_ast)->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
							;}
    break;

  case 97:
#line 711 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								EraseStatementASTNode * eraseNode = new EraseStatementASTNode();
								eraseNode->setEraseAll(true);
								eraseNode->setMemOption((yyvsp[(2) - (3)].m_ast));
								if ((yyvsp[(2) - (3)].m_ast))
								{
									eraseNode->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
								}
								else
								{
									eraseNode->setLocation((yylsp[(1) - (3)]), (yylsp[(2) - (3)]));
								}
								(yyval.m_ast) = eraseNode;
							;}
    break;

  case 98:
#line 726 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								EraseStatementASTNode * eraseNode = new EraseStatementASTNode();
								eraseNode->setEraseAllUnsecure(true);
								eraseNode->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
								(yyval.m_ast) = eraseNode;
							;}
    break;

  case 99:
#line 735 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new StringConstASTNode((yyvsp[(1) - (1)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 100:
#line 739 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 101:
#line 744 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new FromStatementASTNode((yyvsp[(2) - (5)].m_str), dynamic_cast<ListASTNode*>((yyvsp[(4) - (5)].m_ast)));
								(yyval.m_ast)->setLocation((yylsp[(1) - (5)]), (yylsp[(5) - (5)]));
							;}
    break;

  case 102:
#line 751 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								EncryptStatementASTNode * encryptNode = new EncryptStatementASTNode(dynamic_cast<ListASTNode*>((yyvsp[(6) - (7)].m_ast)));
								encryptNode->setKeyblobNumberExpr(dynamic_cast<ExprASTNode *>((yyvsp[(3) - (7)].m_ast)));
								encryptNode->setLocation((yylsp[(1) - (7)]), (yylsp[(7) - (7)]));
								(yyval.m_ast) = encryptNode;
							;}
    break;

  case 103:
#line 760 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								KeywrapStatementASTNode * keywrapNode = new KeywrapStatementASTNode(dynamic_cast<ListASTNode*>((yyvsp[(6) - (7)].m_ast)));
								keywrapNode->setKeyblobNumberExpr(dynamic_cast<ExprASTNode *>((yyvsp[(3) - (7)].m_ast)));
								keywrapNode->setLocation((yylsp[(1) - (7)]), (yylsp[(7) - (7)]));
								(yyval.m_ast) = keywrapNode;
							;}
    break;

  case 104:
#line 769 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new ModeStatementASTNode(dynamic_cast<ExprASTNode*>((yyvsp[(2) - (2)].m_ast)));
								(yyval.m_ast)->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
							;}
    break;

  case 105:
#line 776 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new ResetStatementASTNode();
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]), (yylsp[(1) - (1)]));
							;}
    break;

  case 106:
#line 783 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								MemEnableStatementASTNode * enableNode = new MemEnableStatementASTNode((yyvsp[(3) - (3)].m_ast));
								enableNode->setMemOption((yyvsp[(2) - (3)].m_ast));
								enableNode->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
								(yyval.m_ast) = enableNode;
							;}
    break;

  case 107:
#line 792 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new MessageStatementASTNode(MessageStatementASTNode::kInfo, (yyvsp[(2) - (2)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
							;}
    break;

  case 108:
#line 797 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new MessageStatementASTNode(MessageStatementASTNode::kWarning, (yyvsp[(2) - (2)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
							;}
    break;

  case 109:
#line 802 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new MessageStatementASTNode(MessageStatementASTNode::kError, (yyvsp[(2) - (2)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
							;}
    break;

  case 110:
#line 809 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								IfStatementASTNode * ifStmt = new IfStatementASTNode();
								ifStmt->setConditionExpr(dynamic_cast<ExprASTNode*>((yyvsp[(2) - (6)].m_ast)));
								ifStmt->setIfStatements(dynamic_cast<ListASTNode*>((yyvsp[(4) - (6)].m_ast)));
								ifStmt->setElseStatements(dynamic_cast<ListASTNode*>((yyvsp[(6) - (6)].m_ast)));
								ifStmt->setLocation((yylsp[(1) - (6)]), (yylsp[(6) - (6)]));
								(yyval.m_ast) = ifStmt;
							;}
    break;

  case 111:
#line 820 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(3) - (4)].m_ast);
							;}
    break;

  case 112:
#line 824 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ListASTNode * list = new ListASTNode();
								list->appendNode((yyvsp[(2) - (2)].m_ast));
								(yyval.m_ast) = list;
								(yyval.m_ast)->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
							;}
    break;

  case 113:
#line 830 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = NULL; ;}
    break;

  case 114:
#line 834 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new AddressRangeASTNode((yyvsp[(1) - (1)].m_ast), NULL);
								(yyval.m_ast)->setLocation((yyvsp[(1) - (1)].m_ast));
							;}
    break;

  case 115:
#line 839 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new AddressRangeASTNode((yyvsp[(1) - (3)].m_ast), (yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 116:
#line 846 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(1) - (1)].m_ast);
							;}
    break;

  case 117:
#line 850 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new StringConstASTNode((yyvsp[(1) - (1)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 118:
#line 857 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							(yyval.m_ast) = (yyvsp[(1) - (1)].m_ast);
						;}
    break;

  case 119:
#line 861 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
							ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
							(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kLessThan, right);
							(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
						;}
    break;

  case 120:
#line 868 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
							ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
							(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kGreaterThan, right);
							(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
						;}
    break;

  case 121:
#line 875 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
							ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
							(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kGreaterThanEqual, right);
							(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
						;}
    break;

  case 122:
#line 882 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
							ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
							(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kLessThanEqual, right);
							(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
						;}
    break;

  case 123:
#line 889 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
							ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
							(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kEqual, right);
							(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
						;}
    break;

  case 124:
#line 896 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
							ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
							(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kNotEqual, right);
							(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
						;}
    break;

  case 125:
#line 903 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
							ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
							(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kBooleanAnd, right);
							(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
						;}
    break;

  case 126:
#line 910 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
							ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
							(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kBooleanOr, right);
							(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
						;}
    break;

  case 127:
#line 917 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							(yyval.m_ast) = new BooleanNotExprASTNode(dynamic_cast<ExprASTNode*>((yyvsp[(2) - (2)].m_ast)));
							(yyval.m_ast)->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
						;}
    break;

  case 128:
#line 922 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							(yyval.m_ast) = new SourceFileFunctionASTNode((yyvsp[(1) - (4)].m_str), (yyvsp[(3) - (4)].m_str));
							(yyval.m_ast)->setLocation((yylsp[(1) - (4)]), (yylsp[(4) - (4)]));
						;}
    break;

  case 129:
#line 927 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							(yyval.m_ast) = (yyvsp[(2) - (3)].m_ast);
							(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
						;}
    break;

  case 130:
#line 932 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							(yyval.m_ast) = new DefinedOperatorASTNode((yyvsp[(3) - (4)].m_str));
							(yyval.m_ast)->setLocation((yylsp[(1) - (4)]), (yylsp[(4) - (4)]));
						;}
    break;

  case 131:
#line 938 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    { (yyval.m_ast) = (yyvsp[(1) - (1)].m_ast); ;}
    break;

  case 132:
#line 942 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new SymbolASTNode((yyvsp[(3) - (3)].m_str), (yyvsp[(1) - (3)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 133:
#line 947 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new SymbolASTNode((yyvsp[(2) - (2)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
							;}
    break;

  case 134:
#line 955 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(1) - (1)].m_ast);
							;}
    break;

  case 135:
#line 959 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new VariableExprASTNode((yyvsp[(1) - (1)].m_str));
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 136:
#line 964 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new SymbolRefExprASTNode(dynamic_cast<SymbolASTNode*>((yyvsp[(1) - (1)].m_ast)));
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;

  case 137:
#line 975 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kAdd, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 138:
#line 982 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kSubtract, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 139:
#line 989 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kMultiply, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 140:
#line 996 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kDivide, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 141:
#line 1003 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kModulus, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 142:
#line 1010 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kPower, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 143:
#line 1017 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kBitwiseAnd, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 144:
#line 1024 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kBitwiseOr, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 145:
#line 1031 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kBitwiseXor, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 146:
#line 1038 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kShiftLeft, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 147:
#line 1045 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								ExprASTNode * left = dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast));
								ExprASTNode * right = dynamic_cast<ExprASTNode*>((yyvsp[(3) - (3)].m_ast));
								(yyval.m_ast) = new BinaryOpExprASTNode(left, BinaryOpExprASTNode::kShiftRight, right);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 148:
#line 1052 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(1) - (1)].m_ast);
							;}
    break;

  case 149:
#line 1056 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new IntSizeExprASTNode(dynamic_cast<ExprASTNode*>((yyvsp[(1) - (3)].m_ast)), (yyvsp[(3) - (3)].m_int)->getWordSize());
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 150:
#line 1061 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(2) - (3)].m_ast);
								(yyval.m_ast)->setLocation((yylsp[(1) - (3)]), (yylsp[(3) - (3)]));
							;}
    break;

  case 151:
#line 1066 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							(yyval.m_ast) = new SizeofOperatorASTNode(dynamic_cast<SymbolASTNode*>((yyvsp[(3) - (4)].m_ast)));
							(yyval.m_ast)->setLocation((yylsp[(1) - (4)]), (yylsp[(4) - (4)]));
						;}
    break;

  case 152:
#line 1071 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							(yyval.m_ast) = new SizeofOperatorASTNode((yyvsp[(3) - (4)].m_str));
							(yyval.m_ast)->setLocation((yylsp[(1) - (4)]), (yylsp[(4) - (4)]));
						;}
    break;

  case 153:
#line 1076 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
							(yyval.m_ast) = new SizeofOperatorASTNode((yyvsp[(3) - (4)].m_str));
							(yyval.m_ast)->setLocation((yylsp[(1) - (4)]), (yylsp[(4) - (4)]));
						;}
    break;

  case 154:
#line 1083 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = (yyvsp[(2) - (2)].m_ast);
							;}
    break;

  case 155:
#line 1087 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new NegativeExprASTNode(dynamic_cast<ExprASTNode*>((yyvsp[(2) - (2)].m_ast)));
								(yyval.m_ast)->setLocation((yylsp[(1) - (2)]), (yylsp[(2) - (2)]));
							;}
    break;

  case 156:
#line 1094 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"
    {
								(yyval.m_ast) = new IntConstExprASTNode((yyvsp[(1) - (1)].m_int)->getValue(), (yyvsp[(1) - (1)].m_int)->getWordSize());
								(yyval.m_ast)->setLocation((yylsp[(1) - (1)]));
							;}
    break;


/* Line 1267 of yacc.c.  */
#line 3161 "/Users/MADUser1/Library/Developer/Xcode/DerivedData/elftosb-dxrbhxxtpndhpgdxujwltedpntjq/Build/Intermediates/elftosb.build/Debug/elftosb.build/DerivedSources/elftosb_parser.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
      yyerror (&yylloc, lexer, resultAST, YY_("syntax error"));
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
	    yyerror (&yylloc, lexer, resultAST, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, lexer, resultAST, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc, lexer, resultAST);
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

  yyerror_range[0] = yylsp[1-yylen];
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, lexer, resultAST);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

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
  yyerror (&yylloc, lexer, resultAST, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, lexer, resultAST);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, lexer, resultAST);
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


#line 1100 "/Users/MADUser1/elftosb/elftosb2/elftosb_parser.y"


/* code goes here */

static int yylex(YYSTYPE * lvalp, YYLTYPE * yylloc, ElftosbLexer * lexer)
{
	int token = lexer->yylex();
	*yylloc = lexer->getLocation();
	lexer->getSymbolValue(lvalp);
	return token;
}

static void yyerror(YYLTYPE * yylloc, ElftosbLexer * lexer, CommandFileASTNode ** resultAST, const char * error)
{
	throw syntax_error(format_string("line %d: %s\n", yylloc->m_firstLine, error));
}


