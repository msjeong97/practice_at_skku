/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "minicp.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "minicp.h"

#line 74 "minicp.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "minicp.tab.h".  */
#ifndef YY_YY_MINICP_TAB_H_INCLUDED
# define YY_YY_MINICP_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    UNOP = 258,
    ADDIOP = 259,
    MULTOP = 260,
    RELAOP = 261,
    EQLTOP = 262,
    ID = 263,
    INTNUM = 264,
    FLOATNUM = 265,
    CLASS = 266,
    LPAREN = 267,
    RPAREN = 268,
    LBRACE = 269,
    RBRACE = 270,
    PRIVATE = 271,
    PUBLIC = 272,
    INT = 273,
    FLOAT = 274,
    SEMICOLON = 275,
    COLON = 276,
    EQUAL = 277,
    DOT = 278,
    COMMA = 279,
    MAIN = 280,
    LBRACK = 281,
    RBRACK = 282,
    RETURN = 283,
    WHILE = 284,
    DO = 285,
    FOR = 286,
    IF = 287,
    ELSE = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 9 "minicp.y" /* yacc.c:355  */

	int intnum;
	float floatnum;
	char* str;
	struct Program* _program;
	struct Class* _class;
	struct Member* _member;
	struct VarDecl* _vardecl;
	struct MethodDecl* _methoddecl;
	struct MethodDef* _methoddef;
	struct ClassMethodDef* _classmethoddef;
	struct MainFunc* _mainfunc;
	struct Param* _param;
	struct Ident* _ident;
	struct Type* _type;
	struct CompoundStmt* _compoundstmt;
	struct Stmt* _stmt;
	struct ExprStmt* _exprstmt;
	struct AssignStmt* _assignstmt;
	struct RetStmt* _retstmt;
	struct WhileStmt* _whilestmt;
	struct DoStmt* _dostmt;
	struct ForStmt* _forstmt;
	struct IfStmt* _ifstmt;
	struct Expr* _expr;
	struct OperExpr* _operexpr;
	struct RefExpr* _refexpr;
	struct RefVarExpr* _refvarexpr;
	struct RefCallExpr* _refcallexpr;
	struct IdentExpr* _identexpr;
	struct CallExpr* _callexpr;
	struct Arg* _arg;

#line 182 "minicp.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MINICP_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 199 "minicp.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   334

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  190

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   119,   119,   123,   127,   131,   137,   141,   146,   149,
     152,   155,   160,   163,   166,   169,   172,   175,   178,   181,
     186,   190,   195,   199,   204,   208,   213,   216,   219,   224,
     227,   232,   235,   240,   244,   249,   252,   257,   262,   266,
     271,   276,   279,   284,   287,   290,   295,   298,   301,   304,
     309,   313,   318,   323,   328,   333,   338,   343,   349,   354,
     359,   365,   370,   375,   378,   383,   388,   393,   398,   401,
     406,   411,   416,   421,   428,   431,   434,   437,   440,   443,
     448,   453,   460,   463,   468,   471,   476,   479,   484,   487,
     492,   497
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "UNOP", "ADDIOP", "MULTOP", "RELAOP",
  "EQLTOP", "ID", "INTNUM", "FLOATNUM", "CLASS", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "PRIVATE", "PUBLIC", "INT", "FLOAT", "SEMICOLON",
  "COLON", "EQUAL", "DOT", "COMMA", "MAIN", "LBRACK", "RBRACK", "RETURN",
  "WHILE", "DO", "FOR", "IF", "ELSE", "$accept", "Program", "ClassList",
  "Class", "Member", "VarDeclList", "MethodDeclList", "MethodDefList",
  "VarDecl", "MethodDecl", "MethodDef", "ClassMethodList",
  "ClassMethodDef", "MainFunc", "ParamList", "Param", "Ident", "Type",
  "CompoundStmt", "StmtList", "Stmt", "ExprStmt", "AssignStmt", "RetStmt",
  "WhileStmt", "DoStmt", "ForStmt", "IfStmt", "Expr", "OperExpr",
  "RefExpr", "RefVarExpr", "RefCallExpr", "IdentExpr", "CallExpr",
  "ArgList", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288
};
# endif

#define YYPACT_NINF -116

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-116)))

#define YYTABLE_NINF -46

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     161,  -116,     6,    15,  -116,    23,   161,  -116,   209,  -116,
    -116,    43,    29,    48,  -116,  -116,   209,  -116,  -116,  -116,
      40,   126,    55,  -116,    59,  -116,    87,    93,   104,   122,
     221,   221,   174,  -116,   138,  -116,    96,   221,   221,   221,
    -116,  -116,  -116,   130,   139,   277,     3,  -116,  -116,   277,
    -116,  -116,    27,   143,    67,   154,   155,   204,   160,  -116,
     234,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,    97,
    -116,   152,   159,  -116,  -116,  -116,    54,  -116,   166,   221,
     221,  -116,   221,  -116,   168,  -116,   183,    -2,   129,  -116,
      20,  -116,  -116,   247,   277,   293,  -116,   116,   277,   170,
     277,   277,  -116,   264,   171,  -116,  -116,   277,   277,   277,
     277,  -116,   192,   277,   104,    18,  -116,   160,   221,   221,
     196,   197,   177,   216,  -116,    17,  -116,   325,    35,    14,
    -116,  -116,   297,   199,   141,   307,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,   153,  -116,   104,   221,  -116,   211,   202,
      24,    61,   203,   218,   225,  -116,   277,  -116,    67,   277,
     277,    67,  -116,  -116,  -116,  -116,   104,    81,  -116,  -116,
      86,  -116,  -116,  -116,   325,  -116,   311,   158,   198,   104,
    -116,  -116,   227,   277,    67,  -116,   321,  -116,    67,  -116
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    45,     0,    43,    44,     0,     0,     7,     0,    34,
       5,     0,     0,     0,     1,     6,     0,     4,    33,     3,
       0,     0,     0,     2,     0,    11,     0,     0,     0,     0,
      19,    19,     0,    37,     0,    43,     0,    18,    17,    16,
      21,    23,    25,     0,     0,     0,    87,    72,    73,     0,
      49,    60,     0,     0,     0,     0,     0,     0,     0,    59,
       0,    51,    52,    53,    54,    55,    56,    57,    58,     0,
      70,    71,    80,    81,    83,    85,     0,    10,     0,    15,
      14,    20,    13,    22,     0,    24,     0,    41,     0,     9,
      87,    74,    80,     0,     0,     0,    64,     0,     0,     0,
       0,     0,    48,     0,    41,    47,    50,     0,     0,     0,
       0,    61,     0,     0,     0,     0,    39,     0,    19,    12,
       0,     0,     0,     0,    28,     0,    89,    91,     0,     0,
      79,    63,     0,     0,     0,     0,    46,    75,    76,    77,
      78,    82,    84,     0,    36,     0,     0,    40,     0,     0,
       0,     0,     0,     0,     0,    88,     0,    86,     0,     0,
       0,     0,    62,    35,    38,     8,     0,     0,    30,    32,
       0,    42,    26,    27,    90,    65,     0,     0,    69,     0,
      29,    31,     0,     0,     0,    66,     0,    68,     0,    67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -116,  -116,  -116,   235,   -25,   219,   215,   -21,   -24,   -34,
     -27,   252,    70,   119,  -115,   107,   144,    52,   -26,   212,
     -51,  -116,  -116,  -116,  -116,  -116,  -116,  -116,   -44,  -116,
    -116,   -32,  -116,   156,   163,  -116
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,    36,    37,    38,    39,    40,    41,
      42,     8,     9,    10,   115,   116,    88,    11,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    92,    73,    74,    75,   128
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,    91,    33,    99,    83,    95,    44,   151,    97,   106,
     122,   -45,    85,    81,    12,    93,    80,    82,   107,   108,
     109,   110,    72,    14,   123,    72,   153,   154,    72,    94,
      45,   145,    93,    81,   167,    90,    47,    48,    32,    49,
      13,   157,   146,    21,   168,    83,    94,    96,   155,   127,
     129,    20,   106,    85,   132,    85,   134,   135,   119,   156,
      22,    24,     1,   137,   138,   139,   140,   114,    28,   143,
      45,    72,    35,     4,   170,    90,    47,    48,    18,    49,
      29,    32,    43,    43,    58,   146,    18,    51,   144,    43,
      84,    86,    85,   148,   179,    52,    53,    54,    55,    56,
      32,   107,   108,   109,   110,   146,   180,   175,    30,    58,
     178,    77,   174,    78,    31,   176,   177,   111,    32,   163,
     107,   108,   109,   110,   169,    17,    72,    19,   117,    72,
      34,    84,    86,   187,    86,    23,   131,   189,    87,   186,
     169,    25,    26,    27,   181,   107,   108,   109,   110,   124,
      76,   125,    72,   181,    89,    98,    72,   107,   108,   109,
     110,   160,   107,   108,   109,   110,   100,   101,   104,     1,
      43,    86,     2,   162,   117,   112,   120,    45,   183,     3,
       4,   113,    46,    47,    48,     1,    49,   118,    32,    50,
     150,   121,    35,     4,    51,    35,     4,   123,   117,   133,
      90,   117,    52,    53,    54,    55,    56,    45,   122,   149,
       1,   159,    46,    47,    48,   166,    49,     1,    32,   102,
      35,     4,    35,     4,    51,   152,   165,     3,     4,     1,
     171,   184,    52,    53,    54,    55,    56,    45,   172,    35,
       4,    15,    90,    47,    48,   173,    49,   185,    32,   105,
      45,    57,    79,   164,    51,    90,    47,    48,    16,    49,
     126,   147,    52,    53,    54,    55,    56,    45,   141,   103,
       0,     0,    90,    47,    48,   142,    49,     0,    32,   136,
      45,     0,     0,     0,    51,    90,    47,    48,     0,    49,
       0,     0,    52,    53,    54,    55,    56,   107,   108,   109,
     110,   107,   108,   109,   110,     0,   130,     0,     0,     0,
     158,   107,   108,   109,   110,   107,   108,   109,   110,     0,
     161,     0,     0,     0,   182,   107,   108,   109,   110,   107,
     108,   109,   110,     0,   188
};

static const yytype_int16 yycheck[] =
{
      32,    45,    28,    54,    38,    49,    31,   122,    52,    60,
      12,     8,    39,    37,     8,    12,    37,    38,     4,     5,
       6,     7,    54,     0,    26,    57,     9,    10,    60,    26,
       3,    13,    12,    57,   149,     8,     9,    10,    14,    12,
      25,    27,    24,    14,    20,    79,    26,    20,    13,    93,
      94,     8,   103,    80,    98,    82,   100,   101,    79,    24,
      12,    21,     8,   107,   108,   109,   110,    13,    13,   113,
       3,   103,    18,    19,    13,     8,     9,    10,     8,    12,
      21,    14,    30,    31,    32,    24,    16,    20,   114,    37,
      38,    39,   119,   118,    13,    28,    29,    30,    31,    32,
      14,     4,     5,     6,     7,    24,    20,   158,    21,    57,
     161,    15,   156,    17,    21,   159,   160,    20,    14,   145,
       4,     5,     6,     7,   150,     6,   158,     8,    76,   161,
       8,    79,    80,   184,    82,    16,    20,   188,     8,   183,
     166,    15,    16,    17,   170,     4,     5,     6,     7,    20,
      12,    22,   184,   179,    15,    12,   188,     4,     5,     6,
       7,    20,     4,     5,     6,     7,    12,    12,     8,     8,
     118,   119,    11,    20,   122,    23,     8,     3,    20,    18,
      19,    22,     8,     9,    10,     8,    12,    21,    14,    15,
      13,     8,    18,    19,    20,    18,    19,    26,   146,    29,
       8,   149,    28,    29,    30,    31,    32,     3,    12,    12,
       8,    12,     8,     9,    10,    13,    12,     8,    14,    15,
      18,    19,    18,    19,    20,     9,    15,    18,    19,     8,
      27,    33,    28,    29,    30,    31,    32,     3,    20,    18,
      19,     6,     8,     9,    10,    20,    12,    20,    14,    15,
       3,    32,    37,   146,    20,     8,     9,    10,     6,    12,
      13,   117,    28,    29,    30,    31,    32,     3,   112,    57,
      -1,    -1,     8,     9,    10,   112,    12,    -1,    14,    15,
       3,    -1,    -1,    -1,    20,     8,     9,    10,    -1,    12,
      -1,    -1,    28,    29,    30,    31,    32,     4,     5,     6,
       7,     4,     5,     6,     7,    -1,    13,    -1,    -1,    -1,
      13,     4,     5,     6,     7,     4,     5,     6,     7,    -1,
      13,    -1,    -1,    -1,    13,     4,     5,     6,     7,     4,
       5,     6,     7,    -1,    13
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    11,    18,    19,    35,    36,    37,    45,    46,
      47,    51,     8,    25,     0,    37,    45,    47,    46,    47,
       8,    14,    12,    47,    21,    15,    16,    17,    13,    21,
      21,    21,    14,    52,     8,    18,    38,    39,    40,    41,
      42,    43,    44,    51,    38,     3,     8,     9,    10,    12,
      15,    20,    28,    29,    30,    31,    32,    39,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    12,    15,    17,    40,
      41,    42,    41,    43,    51,    44,    51,     8,    50,    15,
       8,    62,    65,    12,    26,    62,    20,    62,    12,    54,
      12,    12,    15,    53,     8,    15,    54,     4,     5,     6,
       7,    20,    23,    22,    13,    48,    49,    51,    21,    41,
       8,     8,    12,    26,    20,    22,    13,    62,    69,    62,
      13,    20,    62,    29,    62,    62,    15,    62,    62,    62,
      62,    67,    68,    62,    52,    13,    24,    50,    38,    12,
      13,    48,     9,     9,    10,    13,    24,    27,    13,    12,
      20,    13,    20,    52,    49,    15,    13,    48,    20,    52,
      13,    27,    20,    20,    62,    54,    62,    62,    54,    13,
      20,    52,    13,    20,    33,    20,    62,    54,    13,    54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    35,    35,    35,    36,    36,    37,    37,
      37,    37,    38,    38,    38,    38,    38,    38,    38,    38,
      39,    39,    40,    40,    41,    41,    42,    42,    42,    43,
      43,    44,    44,    45,    45,    46,    46,    47,    48,    48,
      49,    50,    50,    51,    51,    51,    52,    52,    52,    52,
      53,    53,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    56,    57,    57,    58,    59,    60,    61,    61,
      62,    62,    62,    62,    63,    63,    63,    63,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      69,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     1,     2,     1,    10,     7,
       7,     4,     3,     2,     2,     2,     1,     1,     1,     0,
       2,     1,     2,     1,     2,     1,     5,     5,     3,     6,
       5,     6,     5,     2,     1,     9,     8,     5,     3,     1,
       2,     1,     4,     1,     1,     1,     4,     3,     3,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     4,     3,     2,     5,     7,     9,     7,     5,
       1,     1,     1,     1,     2,     3,     3,     3,     3,     3,
       1,     1,     3,     1,     3,     1,     4,     1,     4,     3,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 119 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._program) = new_program((yyvsp[-2]._class),(yyvsp[-1]._classmethoddef),(yyvsp[0]._mainfunc));
		head = (yyval._program);
	}
#line 1436 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 123 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._program) = new_program(NULL,(yyvsp[-1]._classmethoddef),(yyvsp[0]._mainfunc));
		head = (yyval._program);
	}
#line 1445 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 127 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._program) = new_program((yyvsp[-1]._class),NULL,(yyvsp[0]._mainfunc));
		head = (yyval._program);
	}
#line 1454 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 131 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._program) = new_program(NULL,NULL,(yyvsp[0]._mainfunc));
		head = (yyval._program);
	}
#line 1463 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 137 "minicp.y" /* yacc.c:1646  */
    {// classlist value's prev is not null, 
		push_into_class_list((yyvsp[-1]._class),(yyvsp[0]._class));
		(yyval._class) = (yyvsp[0]._class);
	}
#line 1472 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 141 "minicp.y" /* yacc.c:1646  */
    {// prev = NULL 
		(yyval._class) = (yyvsp[0]._class);
	}
#line 1480 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 146 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._class) = new_class((yyvsp[-8].str),(yyvsp[-4]._member),(yyvsp[-1]._member));
	}
#line 1488 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 149 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._class) = new_class((yyvsp[-5].str),NULL,(yyvsp[-1]._member));
	}
#line 1496 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 152 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._class) = new_class((yyvsp[-5].str),(yyvsp[-1]._member),NULL);
	}
#line 1504 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 155 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._class) = new_class((yyvsp[-2].str),NULL,NULL);
	}
#line 1512 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 160 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._member) = new_member((yyvsp[-2]._vardecl),(yyvsp[-1]._methoddecl),(yyvsp[0]._methoddef));
	}
#line 1520 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 163 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._member) = new_member(NULL,(yyvsp[-1]._methoddecl),(yyvsp[0]._methoddef));
	}
#line 1528 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 166 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._member) = new_member((yyvsp[-1]._vardecl),NULL,(yyvsp[0]._methoddef));
	}
#line 1536 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 169 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._member) = new_member((yyvsp[-1]._vardecl),(yyvsp[0]._methoddecl),NULL);
	}
#line 1544 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 172 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._member) = new_member(NULL,NULL,(yyvsp[0]._methoddef));
	}
#line 1552 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 175 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._member) = new_member(NULL,(yyvsp[0]._methoddecl),NULL);
	}
#line 1560 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 178 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._member) = new_member((yyvsp[0]._vardecl),NULL,NULL);
	}
#line 1568 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 181 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._member) = new_member(NULL,NULL,NULL);
	}
#line 1576 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 186 "minicp.y" /* yacc.c:1646  */
    {
		push_into_vardecl_list((yyvsp[-1]._vardecl),(yyvsp[0]._vardecl));
		(yyval._vardecl) = (yyvsp[0]._vardecl);
	}
#line 1585 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 190 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._vardecl) = (yyvsp[0]._vardecl);
	}
#line 1593 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 195 "minicp.y" /* yacc.c:1646  */
    {
		push_into_methoddecl_list((yyvsp[-1]._methoddecl),(yyvsp[0]._methoddecl));
		(yyval._methoddecl) = (yyvsp[0]._methoddecl);
	}
#line 1602 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 199 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._methoddecl) = (yyvsp[0]._methoddecl);
	}
#line 1610 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 204 "minicp.y" /* yacc.c:1646  */
    {
		push_into_methoddef_list((yyvsp[-1]._methoddef),(yyvsp[0]._methoddef));
		(yyval._methoddef) = (yyvsp[0]._methoddef);
	}
#line 1619 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 208 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._methoddef) = (yyvsp[0]._methoddef);
	}
#line 1627 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 213 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._vardecl) = new_vardecl((yyvsp[-4]._type),(yyvsp[-3]._ident),(yyvsp[-1].str),eAsInt);
	}
#line 1635 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 216 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._vardecl) = new_vardecl((yyvsp[-4]._type),(yyvsp[-3]._ident),(yyvsp[-1].str),eAsFloat);
	}
#line 1643 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 219 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._vardecl) = new_vardecl((yyvsp[-2]._type),(yyvsp[-1]._ident),NULL,eNon);
	}
#line 1651 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 224 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._methoddecl) = new_methoddecl((yyvsp[-5]._type),(yyvsp[-4].str),(yyvsp[-2]._param));
	}
#line 1659 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 227 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._methoddecl) = new_methoddecl((yyvsp[-4]._type),(yyvsp[-3].str),NULL);
	}
#line 1667 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 232 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._methoddef) = new_methoddef((yyvsp[-5]._type),(yyvsp[-4].str),(yyvsp[-2]._param),(yyvsp[0]._compoundstmt));
	}
#line 1675 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 235 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._methoddef) = new_methoddef((yyvsp[-4]._type),(yyvsp[-3].str),NULL,(yyvsp[0]._compoundstmt));
	}
#line 1683 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 240 "minicp.y" /* yacc.c:1646  */
    {
		push_into_classmethod_list((yyvsp[-1]._classmethoddef),(yyvsp[0]._classmethoddef));
		(yyval._classmethoddef) = (yyvsp[0]._classmethoddef);
	}
#line 1692 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 244 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._classmethoddef) = (yyvsp[0]._classmethoddef);
	}
#line 1700 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 249 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._classmethoddef) = new_classmethoddef((yyvsp[-8]._type),(yyvsp[-7].str),(yyvsp[-4].str),(yyvsp[-2]._param),(yyvsp[0]._compoundstmt));
	}
#line 1708 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 252 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._classmethoddef) = new_classmethoddef((yyvsp[-7]._type),(yyvsp[-6].str),(yyvsp[-3].str),NULL,(yyvsp[0]._compoundstmt));
	}
#line 1716 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 257 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._mainfunc) = new_mainfunc((yyvsp[0]._compoundstmt));
	}
#line 1724 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 262 "minicp.y" /* yacc.c:1646  */
    {
		push_into_param_list((yyvsp[-2]._param),(yyvsp[0]._param));
		(yyval._param) = (yyvsp[0]._param);
	}
#line 1733 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 266 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._param) = (yyvsp[0]._param);
	}
#line 1741 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 271 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._param) = new_param((yyvsp[-1]._type),(yyvsp[0]._ident));
	}
#line 1749 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 276 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._ident) = new_ident((yyvsp[0].str),NULL);
	}
#line 1757 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 279 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._ident) = new_ident((yyvsp[-3].str),(yyvsp[-1].str));
	}
#line 1765 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 284 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._type) = new_type((yyvsp[0].str),eInt);
	}
#line 1773 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 287 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._type) = new_type((yyvsp[0].str),eFloat);
	}
#line 1781 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 290 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._type) = new_type((yyvsp[0].str),eClass);
	}
#line 1789 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 295 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._compoundstmt) = new_compoundstmt((yyvsp[-2]._vardecl),(yyvsp[-1]._stmt));
	}
#line 1797 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 298 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._compoundstmt) = new_compoundstmt(NULL,(yyvsp[-1]._stmt));
	}
#line 1805 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 301 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._compoundstmt) = new_compoundstmt((yyvsp[-1]._vardecl),NULL);
	}
#line 1813 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 304 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._compoundstmt) = new_compoundstmt(NULL,NULL);
	}
#line 1821 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 309 "minicp.y" /* yacc.c:1646  */
    {
		push_into_stmt_list((yyvsp[-1]._stmt),(yyvsp[0]._stmt));
		(yyval._stmt) = (yyvsp[0]._stmt);
	}
#line 1830 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 313 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._stmt) = (yyvsp[0]._stmt);
	}
#line 1838 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 318 "minicp.y" /* yacc.c:1646  */
    {
		union union_stmt s;
		s.exprStmt = (yyvsp[0]._exprstmt);
		(yyval._stmt) = new_stmt(s,eExpr);
	}
#line 1848 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 323 "minicp.y" /* yacc.c:1646  */
    {
		union union_stmt s;
		s.assignStmt = (yyvsp[0]._assignstmt);
		(yyval._stmt) = new_stmt(s,eAssign);
	}
#line 1858 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 328 "minicp.y" /* yacc.c:1646  */
    {
		union union_stmt s;
		s.retStmt = (yyvsp[0]._retstmt);
		(yyval._stmt) = new_stmt(s,eRet);
	}
#line 1868 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 333 "minicp.y" /* yacc.c:1646  */
    {
		union union_stmt s;
		s.whileStmt = (yyvsp[0]._whilestmt);
		(yyval._stmt) = new_stmt(s,eWhile);
	}
#line 1878 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 338 "minicp.y" /* yacc.c:1646  */
    {
		union union_stmt s;
		s.doStmt = (yyvsp[0]._dostmt);
		(yyval._stmt) = new_stmt(s,eDo);
	}
#line 1888 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 343 "minicp.y" /* yacc.c:1646  */
    {

		union union_stmt s;
		s.forStmt = (yyvsp[0]._forstmt);
		(yyval._stmt) = new_stmt(s,eFor);
	}
#line 1899 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 349 "minicp.y" /* yacc.c:1646  */
    {
		union union_stmt s;
		s.ifStmt = (yyvsp[0]._ifstmt);
		(yyval._stmt) = new_stmt(s,eIf);
	}
#line 1909 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 354 "minicp.y" /* yacc.c:1646  */
    {
		union union_stmt s;
		s.compoundStmt = (yyvsp[0]._compoundstmt);
		(yyval._stmt) = new_stmt(s,eCompound);
	}
#line 1919 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 359 "minicp.y" /* yacc.c:1646  */
    {
		union union_stmt s;
		(yyval._stmt) = new_stmt(s,eSemi);
	}
#line 1928 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 365 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._exprstmt) = new_exprstmt((yyvsp[-1]._expr));
	}
#line 1936 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 370 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._assignstmt) = new_assignstmt((yyvsp[-3]._refvarexpr),(yyvsp[-1]._expr));
	}
#line 1944 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 375 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._retstmt) = new_retstmt((yyvsp[-1]._expr));
	}
#line 1952 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 378 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._retstmt) = new_retstmt(NULL);
	}
#line 1960 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 383 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._whilestmt) = new_whilestmt((yyvsp[-2]._expr),(yyvsp[0]._stmt));
	}
#line 1968 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 388 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._dostmt) = new_dostmt((yyvsp[-5]._stmt),(yyvsp[-2]._expr));
	}
#line 1976 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 393 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._forstmt) = new_forstmt((yyvsp[-6]._expr),(yyvsp[-4]._expr),(yyvsp[-2]._expr),(yyvsp[0]._stmt));
	}
#line 1984 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 398 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._ifstmt) = new_ifstmt((yyvsp[-4]._expr),(yyvsp[-2]._stmt),(yyvsp[0]._stmt));
	}
#line 1992 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 401 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._ifstmt) = new_ifstmt((yyvsp[-2]._expr),(yyvsp[0]._stmt),NULL);
	}
#line 2000 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 406 "minicp.y" /* yacc.c:1646  */
    {
		union union_expr e;
		e.operExpr = (yyvsp[0]._operexpr);
		(yyval._expr) = new_expr(e,eOper);
	}
#line 2010 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 411 "minicp.y" /* yacc.c:1646  */
    {
		union union_expr e;
		e.refExpr = (yyvsp[0]._refexpr);
		(yyval._expr) = new_expr(e,eRef);
	}
#line 2020 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 416 "minicp.y" /* yacc.c:1646  */
    {
		union union_expr e;
		e.intnum = (yyvsp[0].str);
		(yyval._expr) = new_expr(e,eIntnum);
	}
#line 2030 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 421 "minicp.y" /* yacc.c:1646  */
    {
		union union_expr e;
		e.floatnum = (yyvsp[0].str);
		(yyval._expr) = new_expr(e,eFloatnum);
	}
#line 2040 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 428 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._operexpr) = new_operexpr((yyvsp[0]._expr),(yyvsp[-1].str),NULL,eUn);// 0 for unop
	}
#line 2048 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 431 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._operexpr) = new_operexpr((yyvsp[-2]._expr),(yyvsp[-1].str),(yyvsp[0]._expr),eAddi);// 1 for addiop
	}
#line 2056 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 434 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._operexpr) = new_operexpr((yyvsp[-2]._expr),(yyvsp[-1].str),(yyvsp[0]._expr),eMult);// 2 for multop
	}
#line 2064 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 437 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._operexpr) = new_operexpr((yyvsp[-2]._expr),(yyvsp[-1].str),(yyvsp[0]._expr),eRela);// 3 for relaop
	}
#line 2072 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 440 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._operexpr) = new_operexpr((yyvsp[-2]._expr),(yyvsp[-1].str),(yyvsp[0]._expr),eEqlt);// 4 for eqltop
	}
#line 2080 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 443 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._operexpr) = new_operexpr((yyvsp[-1]._expr),NULL,NULL,eBracket);// 5 for paren
	}
#line 2088 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 448 "minicp.y" /* yacc.c:1646  */
    {
		union union_refexpr r;
		r.refVarExpr = (yyvsp[0]._refvarexpr);
		(yyval._refexpr) = new_refexpr(r,eVar);
	}
#line 2098 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 453 "minicp.y" /* yacc.c:1646  */
    {
		union union_refexpr r;
		r.refCallExpr = (yyvsp[0]._refcallexpr);
		(yyval._refexpr) = new_refexpr(r,eCall);
	}
#line 2108 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 460 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._refvarexpr) = new_refvarexpr((yyvsp[-2]._refexpr),(yyvsp[0]._identexpr));
	}
#line 2116 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 463 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._refvarexpr) = new_refvarexpr(NULL,(yyvsp[0]._identexpr));
	}
#line 2124 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 468 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._refcallexpr) = new_refcallexpr((yyvsp[-2]._refexpr),(yyvsp[0]._callexpr));
	}
#line 2132 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 471 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._refcallexpr) = new_refcallexpr(NULL,(yyvsp[0]._callexpr));
	}
#line 2140 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 476 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._identexpr) = new_identexpr((yyvsp[-3].str),(yyvsp[-1]._expr));
	}
#line 2148 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 479 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._identexpr) = new_identexpr((yyvsp[0].str),NULL);
	}
#line 2156 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 484 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._callexpr) = new_callexpr((yyvsp[-3].str),(yyvsp[-1]._arg));
	}
#line 2164 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 487 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._callexpr) = new_callexpr((yyvsp[-2].str),NULL);
	}
#line 2172 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 492 "minicp.y" /* yacc.c:1646  */
    {
		struct Arg* sub_arg = new_arg((yyvsp[0]._expr));
		push_into_arg_list((yyvsp[-2]._arg),sub_arg);
		(yyval._arg) = sub_arg;
	}
#line 2182 "minicp.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 497 "minicp.y" /* yacc.c:1646  */
    {
		(yyval._arg) = new_arg((yyvsp[0]._expr));
	}
#line 2190 "minicp.tab.c" /* yacc.c:1646  */
    break;


#line 2194 "minicp.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 501 "minicp.y" /* yacc.c:1906  */

int yyerror (char *s) {
	return fprintf(stderr, "%s!\n", s);
}
