/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "symtab.h"
#include "errors.h"

extern int line_num;
extern int yylex();
extern FILE *yyin;
void yyerror(const char *s);

// Variável global para a raiz da AST
ASTNode *root = NULL;


#line 88 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_ELSE = 5,                       /* ELSE  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_ADD = 11,                       /* ADD  */
  YYSYMBOL_SUB = 12,                       /* SUB  */
  YYSYMBOL_MUL = 13,                       /* MUL  */
  YYSYMBOL_DIV = 14,                       /* DIV  */
  YYSYMBOL_LE = 15,                        /* LE  */
  YYSYMBOL_LT = 16,                        /* LT  */
  YYSYMBOL_GE = 17,                        /* GE  */
  YYSYMBOL_GT = 18,                        /* GT  */
  YYSYMBOL_EQ = 19,                        /* EQ  */
  YYSYMBOL_NE = 20,                        /* NE  */
  YYSYMBOL_ATTR = 21,                      /* ATTR  */
  YYSYMBOL_SEMI = 22,                      /* SEMI  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_LBRACE = 24,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 25,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 26,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 27,                  /* RBRACKET  */
  YYSYMBOL_LPAREN = 28,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 29,                    /* RPAREN  */
  YYSYMBOL_UMINUS = 30,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_program = 32,                   /* program  */
  YYSYMBOL_declaration_list = 33,          /* declaration_list  */
  YYSYMBOL_declaration = 34,               /* declaration  */
  YYSYMBOL_var_declaration = 35,           /* var_declaration  */
  YYSYMBOL_type_specifier = 36,            /* type_specifier  */
  YYSYMBOL_fun_declaration = 37,           /* fun_declaration  */
  YYSYMBOL_params = 38,                    /* params  */
  YYSYMBOL_param_list = 39,                /* param_list  */
  YYSYMBOL_param = 40,                     /* param  */
  YYSYMBOL_compound_decl = 41,             /* compound_decl  */
  YYSYMBOL_local_declarations = 42,        /* local_declarations  */
  YYSYMBOL_statement_list = 43,            /* statement_list  */
  YYSYMBOL_statement = 44,                 /* statement  */
  YYSYMBOL_expression_decl = 45,           /* expression_decl  */
  YYSYMBOL_selection_decl = 46,            /* selection_decl  */
  YYSYMBOL_iteration_decl = 47,            /* iteration_decl  */
  YYSYMBOL_return_decl = 48,               /* return_decl  */
  YYSYMBOL_expression = 49,                /* expression  */
  YYSYMBOL_var = 50,                       /* var  */
  YYSYMBOL_simple_expression = 51,         /* simple_expression  */
  YYSYMBOL_relop = 52,                     /* relop  */
  YYSYMBOL_additive_expression = 53,       /* additive_expression  */
  YYSYMBOL_sum = 54,                       /* sum  */
  YYSYMBOL_term = 55,                      /* term  */
  YYSYMBOL_mult = 56,                      /* mult  */
  YYSYMBOL_factor = 57,                    /* factor  */
  YYSYMBOL_activation = 58,                /* activation  */
  YYSYMBOL_args = 59,                      /* args  */
  YYSYMBOL_arg_list = 60                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   97

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  102

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    54,    54,    61,    64,    70,    73,    79,    82,    88,
      91,    97,   103,   106,   112,   115,   121,   124,   130,   136,
     139,   145,   148,   154,   157,   160,   163,   166,   172,   175,
     181,   184,   190,   196,   199,   205,   208,   214,   217,   223,
     226,   232,   233,   234,   235,   236,   237,   241,   244,   250,
     251,   255,   258,   264,   265,   269,   272,   275,   278,   284,
     290,   293,   299,   302
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUM", "ELSE",
  "IF", "INT", "RETURN", "VOID", "WHILE", "ADD", "SUB", "MUL", "DIV", "LE",
  "LT", "GE", "GT", "EQ", "NE", "ATTR", "SEMI", "COMMA", "LBRACE",
  "RBRACE", "LBRACKET", "RBRACKET", "LPAREN", "RPAREN", "UMINUS",
  "$accept", "program", "declaration_list", "declaration",
  "var_declaration", "type_specifier", "fun_declaration", "params",
  "param_list", "param", "compound_decl", "local_declarations",
  "statement_list", "statement", "expression_decl", "selection_decl",
  "iteration_decl", "return_decl", "expression", "var",
  "simple_expression", "relop", "additive_expression", "sum", "term",
  "mult", "factor", "activation", "args", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-14)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      15,   -74,   -74,    10,    15,   -74,   -74,     0,   -74,   -74,
     -74,    16,   -74,    17,    59,    22,     8,    37,    14,    30,
     -74,    50,    48,    49,    15,   -74,    51,   -74,   -74,   -74,
     -74,    15,   -74,    72,     3,   -14,    41,   -74,    52,    11,
      53,   -74,   -74,    13,   -74,   -74,   -74,   -74,   -74,   -74,
      54,    56,   -74,    45,    57,   -74,   -74,    13,    13,    13,
     -74,    60,    13,    55,   -74,    13,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,    13,    13,   -74,   -74,    13,    58,
     -74,    61,    63,    62,   -74,    64,   -74,   -74,   -74,    47,
      57,   -74,   -74,   -74,    13,    26,    26,   -74,    74,   -74,
      26,   -74
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,     0,     7,     0,     0,     0,    10,     0,     0,    12,
      15,     0,    16,     0,     0,     8,     0,    20,    11,    14,
      17,    22,    19,     0,     0,     0,    37,    58,     0,     0,
       0,    29,    18,     0,    24,    21,    23,    25,    26,    27,
       0,    56,    36,    40,    48,    52,    57,     0,    61,     0,
      33,     0,     0,     0,    28,     0,    49,    50,    41,    42,
      44,    43,    45,    46,     0,     0,    53,    54,     0,     0,
      63,     0,    60,     0,    34,     0,    55,    35,    56,    39,
      47,    51,    38,    59,     0,     0,     0,    62,    30,    32,
       0,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,   -74,    79,    65,    21,   -74,   -74,   -74,    68,
      66,   -74,   -74,   -49,   -74,   -74,   -74,   -74,   -39,   -73,
     -74,   -74,    20,   -74,    12,   -74,    19,   -74,   -74,   -74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,     8,    18,    19,    20,
      44,    31,    34,    45,    46,    47,    48,    49,    50,    51,
      52,    74,    53,    75,    54,    78,    55,    56,    81,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      61,    88,    88,    11,    63,    88,    36,    37,    12,    38,
       9,    39,    13,    40,    36,    37,    36,    37,    79,    80,
      83,    15,     1,    85,     2,    41,    87,    27,    42,    36,
      37,    43,    38,    60,    39,    17,    40,   -13,    12,    43,
      22,    43,    13,    23,    14,    17,    98,    99,    41,    21,
      27,   101,    33,    24,    43,    97,    66,    67,    66,    67,
      68,    69,    70,    71,    72,    73,     1,    57,    16,    58,
      76,    77,    25,    27,    26,    35,    64,    65,    30,   100,
      59,    62,    84,    10,    86,    92,    94,    90,     0,    28,
      93,    95,    29,    96,    89,     0,    32,    91
};

static const yytype_int8 yycheck[] =
{
      39,    74,    75,     3,    43,    78,     3,     4,    22,     6,
       0,     8,    26,    10,     3,     4,     3,     4,    57,    58,
      59,     4,     7,    62,     9,    22,    65,    24,    25,     3,
       4,    28,     6,    22,     8,    14,    10,    29,    22,    28,
       3,    28,    26,    29,    28,    24,    95,    96,    22,    27,
      24,   100,    31,    23,    28,    94,    11,    12,    11,    12,
      15,    16,    17,    18,    19,    20,     7,    26,     9,    28,
      13,    14,    22,    24,    26,     3,    22,    21,    27,     5,
      28,    28,    22,     4,    29,    27,    23,    75,    -1,    23,
      29,    29,    24,    29,    74,    -1,    31,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     9,    32,    33,    34,    35,    36,    37,     0,
      34,     3,    22,    26,    28,     4,     9,    36,    38,    39,
      40,    27,     3,    29,    23,    22,    26,    24,    41,    40,
      27,    42,    35,    36,    43,     3,     3,     4,     6,     8,
      10,    22,    25,    28,    41,    44,    45,    46,    47,    48,
      49,    50,    51,    53,    55,    57,    58,    26,    28,    28,
      22,    49,    28,    49,    22,    21,    11,    12,    15,    16,
      17,    18,    19,    20,    52,    54,    13,    14,    56,    49,
      49,    59,    60,    49,    22,    49,    29,    49,    50,    53,
      55,    57,    27,    29,    23,    29,    29,    49,    44,    44,
       5,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      36,    37,    38,    38,    39,    39,    40,    40,    41,    42,
      42,    43,    43,    44,    44,    44,    44,    44,    45,    45,
      46,    46,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    52,    52,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    57,    57,    57,    58,
      59,    59,    60,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     6,     1,     1,     3,     1,     2,     4,     4,     2,
       0,     2,     0,     1,     1,     1,     1,     1,     2,     1,
       5,     7,     5,     2,     3,     3,     1,     1,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     4,
       1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* program: declaration_list  */
#line 54 "parser.y"
                     {
        (yyval.node) = ast_new_program((yyvsp[0].node));
        root = (yyval.node);
    }
#line 1206 "parser.tab.c"
    break;

  case 3: /* declaration_list: declaration_list declaration  */
#line 61 "parser.y"
                                 {
        (yyval.node) = ast_append_declaration((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1214 "parser.tab.c"
    break;

  case 4: /* declaration_list: declaration  */
#line 64 "parser.y"
                {
        (yyval.node) = ast_new_declaration_list((yyvsp[0].node));
    }
#line 1222 "parser.tab.c"
    break;

  case 5: /* declaration: var_declaration  */
#line 70 "parser.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1230 "parser.tab.c"
    break;

  case 6: /* declaration: fun_declaration  */
#line 73 "parser.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1238 "parser.tab.c"
    break;

  case 7: /* var_declaration: type_specifier ID SEMI  */
#line 79 "parser.y"
                           {
        (yyval.node) = ast_new_var_decl((yyvsp[-2].node), (yyvsp[-1].string), NULL);
    }
#line 1246 "parser.tab.c"
    break;

  case 8: /* var_declaration: type_specifier ID LBRACKET NUM RBRACKET SEMI  */
#line 82 "parser.y"
                                                 {
        (yyval.node) = ast_new_var_decl((yyvsp[-5].node), (yyvsp[-4].string), ast_new_num((yyvsp[-2].num)));
    }
#line 1254 "parser.tab.c"
    break;

  case 9: /* type_specifier: INT  */
#line 88 "parser.y"
        {
        (yyval.node) = ast_new_type(INT_TYPE);
    }
#line 1262 "parser.tab.c"
    break;

  case 10: /* type_specifier: VOID  */
#line 91 "parser.y"
         {
        (yyval.node) = ast_new_type(VOID_TYPE);
    }
#line 1270 "parser.tab.c"
    break;

  case 11: /* fun_declaration: type_specifier ID LPAREN params RPAREN compound_decl  */
#line 97 "parser.y"
                                                         {
        (yyval.node) = ast_new_fun_decl((yyvsp[-5].node), (yyvsp[-4].string), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1278 "parser.tab.c"
    break;

  case 12: /* params: param_list  */
#line 103 "parser.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1286 "parser.tab.c"
    break;

  case 13: /* params: VOID  */
#line 106 "parser.y"
         {
        (yyval.node) = ast_new_param_list(NULL);
    }
#line 1294 "parser.tab.c"
    break;

  case 14: /* param_list: param_list COMMA param  */
#line 112 "parser.y"
                           {
        (yyval.node) = ast_append_param((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1302 "parser.tab.c"
    break;

  case 15: /* param_list: param  */
#line 115 "parser.y"
          {
        (yyval.node) = ast_new_param_list((yyvsp[0].node));
    }
#line 1310 "parser.tab.c"
    break;

  case 16: /* param: type_specifier ID  */
#line 121 "parser.y"
                      {
        (yyval.node) = ast_new_param((yyvsp[-1].node), (yyvsp[0].string), 0);
    }
#line 1318 "parser.tab.c"
    break;

  case 17: /* param: type_specifier ID LBRACKET RBRACKET  */
#line 124 "parser.y"
                                        {
        (yyval.node) = ast_new_param((yyvsp[-3].node), (yyvsp[-2].string), 1);
    }
#line 1326 "parser.tab.c"
    break;

  case 18: /* compound_decl: LBRACE local_declarations statement_list RBRACE  */
#line 130 "parser.y"
                                                    {
        (yyval.node) = ast_new_compound_stmt((yyvsp[-2].node), (yyvsp[-1].node));
    }
#line 1334 "parser.tab.c"
    break;

  case 19: /* local_declarations: local_declarations var_declaration  */
#line 136 "parser.y"
                                       {
        (yyval.node) = ast_append_local_decl((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1342 "parser.tab.c"
    break;

  case 20: /* local_declarations: %empty  */
#line 139 "parser.y"
                {
        (yyval.node) = NULL;
    }
#line 1350 "parser.tab.c"
    break;

  case 21: /* statement_list: statement_list statement  */
#line 145 "parser.y"
                             {
        (yyval.node) = ast_append_stmt((yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1358 "parser.tab.c"
    break;

  case 22: /* statement_list: %empty  */
#line 148 "parser.y"
                {
        (yyval.node) = NULL;
    }
#line 1366 "parser.tab.c"
    break;

  case 23: /* statement: expression_decl  */
#line 154 "parser.y"
                    {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1374 "parser.tab.c"
    break;

  case 24: /* statement: compound_decl  */
#line 157 "parser.y"
                  {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1382 "parser.tab.c"
    break;

  case 25: /* statement: selection_decl  */
#line 160 "parser.y"
                   {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1390 "parser.tab.c"
    break;

  case 26: /* statement: iteration_decl  */
#line 163 "parser.y"
                   {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1398 "parser.tab.c"
    break;

  case 27: /* statement: return_decl  */
#line 166 "parser.y"
                {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1406 "parser.tab.c"
    break;

  case 28: /* expression_decl: expression SEMI  */
#line 172 "parser.y"
                    {
        (yyval.node) = ast_new_expr_stmt((yyvsp[-1].node));
    }
#line 1414 "parser.tab.c"
    break;

  case 29: /* expression_decl: SEMI  */
#line 175 "parser.y"
         {
        (yyval.node) = ast_new_empty_stmt();
    }
#line 1422 "parser.tab.c"
    break;

  case 30: /* selection_decl: IF LPAREN expression RPAREN statement  */
#line 181 "parser.y"
                                          {
        (yyval.node) = ast_new_if_stmt((yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 1430 "parser.tab.c"
    break;

  case 31: /* selection_decl: IF LPAREN expression RPAREN statement ELSE statement  */
#line 184 "parser.y"
                                                         {
        (yyval.node) = ast_new_if_stmt((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1438 "parser.tab.c"
    break;

  case 32: /* iteration_decl: WHILE LPAREN expression RPAREN statement  */
#line 190 "parser.y"
                                             {
        (yyval.node) = ast_new_while_stmt((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1446 "parser.tab.c"
    break;

  case 33: /* return_decl: RETURN SEMI  */
#line 196 "parser.y"
                {
        (yyval.node) = ast_new_return_stmt(NULL);
    }
#line 1454 "parser.tab.c"
    break;

  case 34: /* return_decl: RETURN expression SEMI  */
#line 199 "parser.y"
                           {
        (yyval.node) = ast_new_return_stmt((yyvsp[-1].node));
    }
#line 1462 "parser.tab.c"
    break;

  case 35: /* expression: var ATTR expression  */
#line 205 "parser.y"
                        {
        (yyval.node) = ast_new_assign((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1470 "parser.tab.c"
    break;

  case 36: /* expression: simple_expression  */
#line 208 "parser.y"
                      {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1478 "parser.tab.c"
    break;

  case 37: /* var: ID  */
#line 214 "parser.y"
       {
        (yyval.node) = ast_new_variable((yyvsp[0].string));
    }
#line 1486 "parser.tab.c"
    break;

  case 38: /* var: ID LBRACKET expression RBRACKET  */
#line 217 "parser.y"
                                    {
        (yyval.node) = ast_new_array_access((yyvsp[-3].string), (yyvsp[-1].node));
    }
#line 1494 "parser.tab.c"
    break;

  case 39: /* simple_expression: additive_expression relop additive_expression  */
#line 223 "parser.y"
                                                  {
        (yyval.node) = ast_new_binop((yyvsp[-1].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1502 "parser.tab.c"
    break;

  case 40: /* simple_expression: additive_expression  */
#line 226 "parser.y"
                        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1510 "parser.tab.c"
    break;

  case 41: /* relop: LE  */
#line 232 "parser.y"
       { (yyval.node) = LE; }
#line 1516 "parser.tab.c"
    break;

  case 42: /* relop: LT  */
#line 233 "parser.y"
       { (yyval.node) = LT; }
#line 1522 "parser.tab.c"
    break;

  case 43: /* relop: GT  */
#line 234 "parser.y"
       { (yyval.node) = GT; }
#line 1528 "parser.tab.c"
    break;

  case 44: /* relop: GE  */
#line 235 "parser.y"
       { (yyval.node) = GE; }
#line 1534 "parser.tab.c"
    break;

  case 45: /* relop: EQ  */
#line 236 "parser.y"
       { (yyval.node) = EQ; }
#line 1540 "parser.tab.c"
    break;

  case 46: /* relop: NE  */
#line 237 "parser.y"
       { (yyval.node) = NE; }
#line 1546 "parser.tab.c"
    break;

  case 47: /* additive_expression: additive_expression sum term  */
#line 241 "parser.y"
                                 {
        (yyval.node) = ast_new_binop((yyvsp[-1].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1554 "parser.tab.c"
    break;

  case 48: /* additive_expression: term  */
#line 244 "parser.y"
         {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1562 "parser.tab.c"
    break;

  case 49: /* sum: ADD  */
#line 250 "parser.y"
        { (yyval.node) = ADD; }
#line 1568 "parser.tab.c"
    break;

  case 50: /* sum: SUB  */
#line 251 "parser.y"
        { (yyval.node) = SUB; }
#line 1574 "parser.tab.c"
    break;

  case 51: /* term: term mult factor  */
#line 255 "parser.y"
                     {
        (yyval.node) = ast_new_binop((yyvsp[-1].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1582 "parser.tab.c"
    break;

  case 52: /* term: factor  */
#line 258 "parser.y"
           {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1590 "parser.tab.c"
    break;

  case 53: /* mult: MUL  */
#line 264 "parser.y"
        { (yyval.node) = MUL; }
#line 1596 "parser.tab.c"
    break;

  case 54: /* mult: DIV  */
#line 265 "parser.y"
        { (yyval.node) = DIV; }
#line 1602 "parser.tab.c"
    break;

  case 55: /* factor: LPAREN expression RPAREN  */
#line 269 "parser.y"
                             {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1610 "parser.tab.c"
    break;

  case 56: /* factor: var  */
#line 272 "parser.y"
        {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1618 "parser.tab.c"
    break;

  case 57: /* factor: activation  */
#line 275 "parser.y"
               {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1626 "parser.tab.c"
    break;

  case 58: /* factor: NUM  */
#line 278 "parser.y"
        {
        (yyval.node) = ast_new_num((yyvsp[0].num));
    }
#line 1634 "parser.tab.c"
    break;

  case 59: /* activation: ID LPAREN args RPAREN  */
#line 284 "parser.y"
                          {
        (yyval.node) = ast_new_fun_call((yyvsp[-3].string), (yyvsp[-1].node));
    }
#line 1642 "parser.tab.c"
    break;

  case 60: /* args: arg_list  */
#line 290 "parser.y"
             {
        (yyval.node) = (yyvsp[0].node);
    }
#line 1650 "parser.tab.c"
    break;

  case 61: /* args: %empty  */
#line 293 "parser.y"
                {
        (yyval.node) = NULL;
    }
#line 1658 "parser.tab.c"
    break;

  case 62: /* arg_list: arg_list COMMA expression  */
#line 299 "parser.y"
                              {
        (yyval.node) = ast_append_arg((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1666 "parser.tab.c"
    break;

  case 63: /* arg_list: expression  */
#line 302 "parser.y"
               {
        (yyval.node) = ast_new_arg_list((yyvsp[0].node));
    }
#line 1674 "parser.tab.c"
    break;


#line 1678 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 307 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "ERRO SINTÁTICO: %s LINHA: %d\n", s, line_num);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    yyparse();
    
    // Imprime a AST após parsing bem-sucedido
    ast_print(root, 0);
    
    fclose(yyin);
    return 0;
}
