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

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include "ast.hpp"
#include "tokens.hpp"

extern int yylex(void);
extern int yylineno;
void yyerror(const char* s);

AST::Program* g_program = nullptr;

#line 87 "parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CLASS = 3,                      /* CLASS  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_IS = 5,                         /* IS  */
  YYSYMBOL_END = 6,                        /* END  */
  YYSYMBOL_METHOD = 7,                     /* METHOD  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_THEN = 10,                      /* THEN  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_ELSEIF = 12,                    /* ELSEIF  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_DO = 14,                        /* DO  */
  YYSYMBOL_TRUE = 15,                      /* TRUE  */
  YYSYMBOL_FALSE = 16,                     /* FALSE  */
  YYSYMBOL_COLON = 17,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 18,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_LPAREN = 20,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 21,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 22,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 23,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 24,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 25,                  /* RBRACKET  */
  YYSYMBOL_ASSIGN = 26,                    /* ASSIGN  */
  YYSYMBOL_ARROW = 27,                     /* ARROW  */
  YYSYMBOL_PLUS = 28,                      /* PLUS  */
  YYSYMBOL_MINUS = 29,                     /* MINUS  */
  YYSYMBOL_STAR = 30,                      /* STAR  */
  YYSYMBOL_SLASH = 31,                     /* SLASH  */
  YYSYMBOL_DOT = 32,                       /* DOT  */
  YYSYMBOL_GT = 33,                        /* GT  */
  YYSYMBOL_LT = 34,                        /* LT  */
  YYSYMBOL_EQEQ = 35,                      /* EQEQ  */
  YYSYMBOL_EQUAL = 36,                     /* EQUAL  */
  YYSYMBOL_IDENTIFIER = 37,                /* IDENTIFIER  */
  YYSYMBOL_TYPE_NAME = 38,                 /* TYPE_NAME  */
  YYSYMBOL_INT_LITERAL = 39,               /* INT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 40,            /* STRING_LITERAL  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_class_list = 43,                /* class_list  */
  YYSYMBOL_class_decl = 44,                /* class_decl  */
  YYSYMBOL_class_body = 45,                /* class_body  */
  YYSYMBOL_member_list = 46,               /* member_list  */
  YYSYMBOL_member = 47,                    /* member  */
  YYSYMBOL_type_spec = 48,                 /* type_spec  */
  YYSYMBOL_type_list = 49,                 /* type_list  */
  YYSYMBOL_var_decl = 50,                  /* var_decl  */
  YYSYMBOL_method_decl = 51,               /* method_decl  */
  YYSYMBOL_opt_params = 52,                /* opt_params  */
  YYSYMBOL_param_list = 53,                /* param_list  */
  YYSYMBOL_param = 54,                     /* param  */
  YYSYMBOL_method_body = 55,               /* method_body  */
  YYSYMBOL_stmt_list = 56,                 /* stmt_list  */
  YYSYMBOL_simple_stmt = 57,               /* simple_stmt  */
  YYSYMBOL_block_stmt = 58,                /* block_stmt  */
  YYSYMBOL_if_stmt = 59,                   /* if_stmt  */
  YYSYMBOL_elif_tail = 60,                 /* elif_tail  */
  YYSYMBOL_opt_else = 61,                  /* opt_else  */
  YYSYMBOL_while_stmt = 62,                /* while_stmt  */
  YYSYMBOL_expr = 63,                      /* expr  */
  YYSYMBOL_assign_expr = 64,               /* assign_expr  */
  YYSYMBOL_equality_expr = 65,             /* equality_expr  */
  YYSYMBOL_relational_expr = 66,           /* relational_expr  */
  YYSYMBOL_additive_expr = 67,             /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 68,       /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 69,                /* unary_expr  */
  YYSYMBOL_postfix_expr = 70,              /* postfix_expr  */
  YYSYMBOL_opt_args = 71,                  /* opt_args  */
  YYSYMBOL_arg_list = 72,                  /* arg_list  */
  YYSYMBOL_primary_expr = 73,              /* primary_expr  */
  YYSYMBOL_type_as_expr = 74,              /* type_as_expr  */
  YYSYMBOL_lvalue = 75                     /* lvalue  */
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
typedef yytype_uint8 yy_state_t;

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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   158

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    78,    78,    83,    84,    88,   102,   103,   107,   108,
     112,   113,   117,   119,   129,   131,   141,   143,   145,   150,
     163,   164,   168,   169,   173,   178,   188,   189,   190,   191,
     192,   193,   194,   195,   205,   206,   207,   208,   209,   210,
     211,   215,   225,   232,   236,   243,   244,   248,   258,   262,
     263,   267,   268,   272,   273,   274,   278,   279,   280,   284,
     285,   286,   290,   291,   295,   297,   299,   301,   306,   307,
     311,   312,   316,   317,   318,   319,   320,   321,   322,   326,
     331,   332,   333
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "VAR", "IS",
  "END", "METHOD", "RETURN", "IF", "THEN", "ELSE", "ELSEIF", "WHILE", "DO",
  "TRUE", "FALSE", "COLON", "SEMICOLON", "COMMA", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "ASSIGN", "ARROW", "PLUS",
  "MINUS", "STAR", "SLASH", "DOT", "GT", "LT", "EQEQ", "EQUAL",
  "IDENTIFIER", "TYPE_NAME", "INT_LITERAL", "STRING_LITERAL", "$accept",
  "program", "class_list", "class_decl", "class_body", "member_list",
  "member", "type_spec", "type_list", "var_decl", "method_decl",
  "opt_params", "param_list", "param", "method_body", "stmt_list",
  "simple_stmt", "block_stmt", "if_stmt", "elif_tail", "opt_else",
  "while_stmt", "expr", "assign_expr", "equality_expr", "relational_expr",
  "additive_expr", "multiplicative_expr", "unary_expr", "postfix_expr",
  "opt_args", "arg_list", "primary_expr", "type_as_expr", "lvalue", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-130)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-81)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      15,   -26,    24,    15,  -130,    44,  -130,  -130,     8,    18,
      26,    63,     8,  -130,  -130,  -130,    68,    51,  -130,  -130,
      50,    62,    57,   -10,    91,    89,   108,  -130,    50,  -130,
      80,    80,    50,   111,    62,  -130,   -13,  -130,  -130,    80,
     106,    99,  -130,  -130,  -130,   112,  -130,    94,    34,    52,
      67,  -130,    41,  -130,  -130,    40,   113,  -130,    50,  -130,
      50,  -130,   115,  -130,  -130,  -130,   106,   106,   106,   106,
     106,   106,   106,    80,    80,    95,    80,    80,    96,  -130,
     107,  -130,  -130,    34,    52,    52,    67,    67,  -130,  -130,
    -130,   116,   119,   114,  -130,   117,  -130,  -130,    74,  -130,
      80,  -130,  -130,   103,    80,    80,    80,  -130,    74,   123,
    -130,  -130,  -130,    60,  -130,   130,  -130,   138,   135,   132,
    -130,  -130,  -130,    80,    50,    74,    74,  -130,  -130,  -130,
      -7,    74,    90,    19,    80,    80,    74,    80,   145,  -130,
    -130,  -130,  -130,  -130,   142,  -130,    74,    90,  -130
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     4,     0,     1,     3,     7,     0,
       0,     0,     6,     9,    10,    11,     0,     0,     5,     8,
       0,    21,    12,     0,     0,     0,    20,    23,     0,    16,
       0,     0,     0,     0,     0,    14,     0,    74,    75,     0,
       0,    76,    72,    73,    79,     0,    48,    50,    52,    55,
      58,    61,    63,    67,    77,     0,     0,    24,     0,    22,
       0,    13,     0,    76,    62,    18,     0,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,    17,
       0,    15,    78,    51,    53,    54,    56,    57,    59,    60,
      71,     0,    68,     0,    65,     0,    49,    81,     0,    64,
       0,    66,    82,     0,    35,     0,     0,    19,    25,    33,
      31,    32,    40,     0,    70,     0,    34,     0,     0,    29,
      27,    28,    30,     0,     0,     0,     0,    26,    39,    48,
      36,    41,    46,     0,     0,     0,     0,     0,     0,    44,
      47,    38,    37,    45,     0,    42,     0,    46,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,  -130,   150,  -130,  -130,   143,   -18,  -130,  -130,
    -130,  -130,  -130,   120,  -130,   -93,   -86,  -129,   -71,     9,
    -130,   -54,   -30,   -73,  -130,    92,    48,    54,   -19,  -130,
    -130,  -130,  -130,  -130,   -95
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    11,    12,    13,    44,    36,    14,
      15,    25,    26,    27,   107,   131,   109,   132,   110,   138,
     139,   111,   112,    46,    47,    48,    49,    50,    51,    52,
      91,    92,    53,    54,    55
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    56,    23,   113,    96,   108,    60,   143,    29,    62,
      35,     5,     9,   113,    57,    10,    30,   147,     1,   134,
      61,    64,   119,   103,     6,   140,    31,   104,   105,   135,
     113,   113,   106,   133,    37,    38,   113,   120,   113,    39,
      80,   113,    81,    90,    93,   119,    95,   119,    40,     8,
     129,   113,    88,    89,   121,    16,    41,    22,    42,    43,
     120,    73,   120,    17,    76,    74,    77,    67,    68,    18,
     114,    21,    78,    75,   116,   117,   118,   121,   103,   121,
      69,    70,   104,   105,    76,    20,   123,   106,    22,    37,
      38,    28,    78,   128,    39,    37,    38,    71,    72,    24,
      39,   136,   137,    40,   141,   142,   130,   144,    32,    40,
      33,    41,    22,    42,    43,    84,    85,    41,    22,    42,
      43,    37,    38,    86,    87,   -80,    39,    34,    58,    66,
      65,    79,    94,    97,    98,    40,    82,    99,   100,   101,
     115,   122,   102,    63,    22,    42,    43,   124,   125,   126,
     127,   145,   146,     7,    59,    19,   148,     0,    83
};

static const yytype_int16 yycheck[] =
{
      30,    31,    20,    98,    77,    98,    19,   136,    18,    39,
      28,    37,     4,   108,    32,     7,    26,   146,     3,    26,
      33,    40,   108,     4,     0,     6,    36,     8,     9,    36,
     125,   126,    13,   126,    15,    16,   131,   108,   133,    20,
      58,   136,    60,    73,    74,   131,    76,   133,    29,     5,
     123,   146,    71,    72,   108,    37,    37,    38,    39,    40,
     131,    20,   133,    37,    24,    24,    26,    33,    34,     6,
     100,    20,    32,    32,   104,   105,   106,   131,     4,   133,
      28,    29,     8,     9,    24,    17,    26,    13,    38,    15,
      16,    34,    32,   123,    20,    15,    16,    30,    31,    37,
      20,    11,    12,    29,   134,   135,   124,   137,    17,    29,
      21,    37,    38,    39,    40,    67,    68,    37,    38,    39,
      40,    15,    16,    69,    70,    26,    20,    19,    17,    35,
      18,    18,    37,    37,    27,    29,    21,    21,    19,    25,
      37,    18,    25,    37,    38,    39,    40,    17,    10,    14,
      18,     6,    10,     3,    34,    12,   147,    -1,    66
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    42,    43,    44,    37,     0,    44,     5,     4,
       7,    45,    46,    47,    50,    51,    37,    37,     6,    47,
      17,    20,    38,    48,    37,    52,    53,    54,    34,    18,
      26,    36,    17,    21,    19,    48,    49,    15,    16,    20,
      29,    37,    39,    40,    48,    63,    64,    65,    66,    67,
      68,    69,    70,    73,    74,    75,    63,    48,    17,    54,
      19,    33,    63,    37,    69,    18,    35,    33,    34,    28,
      29,    30,    31,    20,    24,    32,    24,    26,    32,    18,
      48,    48,    21,    66,    67,    67,    68,    68,    69,    69,
      63,    71,    72,    63,    37,    63,    64,    37,    27,    21,
      19,    25,    25,     4,     8,     9,    13,    55,    56,    57,
      59,    62,    63,    75,    63,    37,    63,    63,    63,    57,
      59,    62,    18,    26,    17,    10,    14,    18,    63,    64,
      48,    56,    58,    56,    26,    36,    11,    12,    60,    61,
       6,    63,    63,    58,    63,     6,    10,    58,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    45,    45,    46,    46,
      47,    47,    48,    48,    49,    49,    50,    50,    50,    51,
      52,    52,    53,    53,    54,    55,    56,    56,    56,    56,
      56,    56,    56,    56,    57,    57,    57,    57,    57,    57,
      57,    58,    59,    60,    60,    61,    61,    62,    63,    64,
      64,    65,    65,    66,    66,    66,    67,    67,    67,    68,
      68,    68,    69,    69,    70,    70,    70,    70,    71,    71,
      72,    72,    73,    73,    73,    73,    73,    73,    73,    74,
      75,    75,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     5,     1,     0,     2,     1,
       1,     1,     1,     4,     1,     3,     5,     7,     7,     9,
       1,     0,     3,     1,     3,     1,     3,     2,     2,     2,
       2,     1,     1,     1,     2,     1,     4,     6,     6,     3,
       1,     1,     6,     5,     1,     2,     0,     5,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     2,     1,     4,     3,     4,     1,     1,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     3,     4
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* program: class_list  */
#line 79 "parser.y"
      { g_program = new AST::Program(); for (auto* c : *(yyvsp[0].classlist)) g_program->classes.push_back(c); delete (yyvsp[0].classlist); }
#line 1522 "parser.cpp"
    break;

  case 3: /* class_list: class_list class_decl  */
#line 83 "parser.y"
                            { (yyval.classlist) = (yyvsp[-1].classlist); (yyvsp[-1].classlist)->push_back((yyvsp[0].classdecl)); }
#line 1528 "parser.cpp"
    break;

  case 4: /* class_list: class_decl  */
#line 84 "parser.y"
                            { (yyval.classlist) = new std::vector<AST::ClassDecl*>(); (yyval.classlist)->push_back((yyvsp[0].classdecl)); }
#line 1534 "parser.cpp"
    break;

  case 5: /* class_decl: CLASS IDENTIFIER IS class_body END  */
#line 89 "parser.y"
      {
        (yyval.classdecl) = new AST::ClassDecl((yyvsp[-3].cstr));
        for (auto* n : *(yyvsp[-1].memberlist)) {
          if (auto* v = dynamic_cast<AST::VarDecl*>(n)) (yyval.classdecl)->fields.push_back(v);
          else if (auto* m = dynamic_cast<AST::MethodDecl*>(n)) (yyval.classdecl)->methods.push_back(m);
          else delete n;
        }
        free((yyvsp[-3].cstr));
        delete (yyvsp[-1].memberlist);
      }
#line 1549 "parser.cpp"
    break;

  case 6: /* class_body: member_list  */
#line 102 "parser.y"
                  { (yyval.memberlist) = (yyvsp[0].memberlist); }
#line 1555 "parser.cpp"
    break;

  case 7: /* class_body: %empty  */
#line 103 "parser.y"
                  { (yyval.memberlist) = new std::vector<AST::Node*>(); }
#line 1561 "parser.cpp"
    break;

  case 8: /* member_list: member_list member  */
#line 107 "parser.y"
                         { (yyval.memberlist) = (yyvsp[-1].memberlist); (yyvsp[-1].memberlist)->push_back((yyvsp[0].node)); }
#line 1567 "parser.cpp"
    break;

  case 9: /* member_list: member  */
#line 108 "parser.y"
                         { (yyval.memberlist) = new std::vector<AST::Node*>(); (yyval.memberlist)->push_back((yyvsp[0].node)); }
#line 1573 "parser.cpp"
    break;

  case 10: /* member: var_decl  */
#line 112 "parser.y"
                  { (yyval.node) = (yyvsp[0].vardecl); }
#line 1579 "parser.cpp"
    break;

  case 11: /* member: method_decl  */
#line 113 "parser.y"
                  { (yyval.node) = (yyvsp[0].methoddecl); }
#line 1585 "parser.cpp"
    break;

  case 12: /* type_spec: TYPE_NAME  */
#line 118 "parser.y"
      { (yyval.cstr) = (yyvsp[0].cstr); }
#line 1591 "parser.cpp"
    break;

  case 13: /* type_spec: TYPE_NAME LT type_list GT  */
#line 120 "parser.y"
      {
        std::string s = std::string((yyvsp[-3].cstr)) + "<" + std::string((yyvsp[-1].cstr)) + ">";
        (yyval.cstr) = strdup(s.c_str());
        free((yyvsp[-3].cstr));
        free((yyvsp[-1].cstr));
      }
#line 1602 "parser.cpp"
    break;

  case 14: /* type_list: type_spec  */
#line 130 "parser.y"
      { (yyval.cstr) = (yyvsp[0].cstr); }
#line 1608 "parser.cpp"
    break;

  case 15: /* type_list: type_list COMMA type_spec  */
#line 132 "parser.y"
      {
        std::string s = std::string((yyvsp[-2].cstr)) + "," + std::string((yyvsp[0].cstr));
        (yyval.cstr) = strdup(s.c_str());
        free((yyvsp[-2].cstr));
        free((yyvsp[0].cstr));
      }
#line 1619 "parser.cpp"
    break;

  case 16: /* var_decl: VAR IDENTIFIER COLON type_spec SEMICOLON  */
#line 142 "parser.y"
      { (yyval.vardecl) = new AST::VarDecl((yyvsp[-3].cstr), (yyvsp[-1].cstr), nullptr); free((yyvsp[-3].cstr)); free((yyvsp[-1].cstr)); }
#line 1625 "parser.cpp"
    break;

  case 17: /* var_decl: VAR IDENTIFIER COLON type_spec EQUAL expr SEMICOLON  */
#line 144 "parser.y"
      { (yyval.vardecl) = new AST::VarDecl((yyvsp[-5].cstr), (yyvsp[-3].cstr), (yyvsp[-1].expr)); free((yyvsp[-5].cstr)); free((yyvsp[-3].cstr)); }
#line 1631 "parser.cpp"
    break;

  case 18: /* var_decl: VAR IDENTIFIER COLON type_spec ASSIGN expr SEMICOLON  */
#line 146 "parser.y"
      { (yyval.vardecl) = new AST::VarDecl((yyvsp[-5].cstr), (yyvsp[-3].cstr), (yyvsp[-1].expr)); free((yyvsp[-5].cstr)); free((yyvsp[-3].cstr)); }
#line 1637 "parser.cpp"
    break;

  case 19: /* method_decl: METHOD IDENTIFIER LPAREN opt_params RPAREN COLON type_spec ARROW method_body  */
#line 151 "parser.y"
      {
        (yyval.methoddecl) = new AST::MethodDecl((yyvsp[-7].cstr), (yyvsp[-2].cstr), (yyvsp[0].stmt));
        if ((yyvsp[-5].paramlist)) {
          for (auto* p : *(yyvsp[-5].paramlist)) (yyval.methoddecl)->params.push_back(p);
          delete (yyvsp[-5].paramlist);
        }
        free((yyvsp[-7].cstr));
        free((yyvsp[-2].cstr));
      }
#line 1651 "parser.cpp"
    break;

  case 20: /* opt_params: param_list  */
#line 163 "parser.y"
                 { (yyval.paramlist) = (yyvsp[0].paramlist); }
#line 1657 "parser.cpp"
    break;

  case 21: /* opt_params: %empty  */
#line 164 "parser.y"
                 { (yyval.paramlist) = new std::vector<AST::Param*>(); }
#line 1663 "parser.cpp"
    break;

  case 22: /* param_list: param_list COMMA param  */
#line 168 "parser.y"
                             { (yyval.paramlist) = (yyvsp[-2].paramlist); (yyvsp[-2].paramlist)->push_back((yyvsp[0].param)); }
#line 1669 "parser.cpp"
    break;

  case 23: /* param_list: param  */
#line 169 "parser.y"
                             { (yyval.paramlist) = new std::vector<AST::Param*>(); (yyval.paramlist)->push_back((yyvsp[0].param)); }
#line 1675 "parser.cpp"
    break;

  case 24: /* param: IDENTIFIER COLON type_spec  */
#line 174 "parser.y"
      { (yyval.param) = new AST::Param((yyvsp[-2].cstr), (yyvsp[0].cstr)); free((yyvsp[-2].cstr)); free((yyvsp[0].cstr)); }
#line 1681 "parser.cpp"
    break;

  case 25: /* method_body: stmt_list  */
#line 179 "parser.y"
      {
        auto* b = new AST::Block();
        for (auto* s : *(yyvsp[0].stmtlist)) b->stmts.push_back(s);
        delete (yyvsp[0].stmtlist);
        (yyval.stmt) = b;
      }
#line 1692 "parser.cpp"
    break;

  case 26: /* stmt_list: stmt_list simple_stmt SEMICOLON  */
#line 188 "parser.y"
                                      { (yyval.stmtlist) = (yyvsp[-2].stmtlist); (yyvsp[-2].stmtlist)->push_back((yyvsp[-1].stmt)); }
#line 1698 "parser.cpp"
    break;

  case 27: /* stmt_list: stmt_list if_stmt  */
#line 189 "parser.y"
                                     { (yyval.stmtlist) = (yyvsp[-1].stmtlist); (yyvsp[-1].stmtlist)->push_back((yyvsp[0].stmt)); }
#line 1704 "parser.cpp"
    break;

  case 28: /* stmt_list: stmt_list while_stmt  */
#line 190 "parser.y"
                                     { (yyval.stmtlist) = (yyvsp[-1].stmtlist); (yyvsp[-1].stmtlist)->push_back((yyvsp[0].stmt)); }
#line 1710 "parser.cpp"
    break;

  case 29: /* stmt_list: stmt_list simple_stmt  */
#line 191 "parser.y"
                                     { (yyval.stmtlist) = (yyvsp[-1].stmtlist); (yyvsp[-1].stmtlist)->push_back((yyvsp[0].stmt)); }
#line 1716 "parser.cpp"
    break;

  case 30: /* stmt_list: simple_stmt SEMICOLON  */
#line 192 "parser.y"
                                     { (yyval.stmtlist) = new std::vector<AST::Stmt*>(); (yyval.stmtlist)->push_back((yyvsp[-1].stmt)); }
#line 1722 "parser.cpp"
    break;

  case 31: /* stmt_list: if_stmt  */
#line 193 "parser.y"
                                     { (yyval.stmtlist) = new std::vector<AST::Stmt*>(); (yyval.stmtlist)->push_back((yyvsp[0].stmt)); }
#line 1728 "parser.cpp"
    break;

  case 32: /* stmt_list: while_stmt  */
#line 194 "parser.y"
                                     { (yyval.stmtlist) = new std::vector<AST::Stmt*>(); (yyval.stmtlist)->push_back((yyvsp[0].stmt)); }
#line 1734 "parser.cpp"
    break;

  case 33: /* stmt_list: simple_stmt  */
#line 195 "parser.y"
                                     { (yyval.stmtlist) = new std::vector<AST::Stmt*>(); (yyval.stmtlist)->push_back((yyvsp[0].stmt)); }
#line 1740 "parser.cpp"
    break;

  case 34: /* simple_stmt: RETURN expr  */
#line 205 "parser.y"
                                                 { (yyval.stmt) = new AST::ReturnStmt((yyvsp[0].expr)); }
#line 1746 "parser.cpp"
    break;

  case 35: /* simple_stmt: RETURN  */
#line 206 "parser.y"
                                                 { (yyval.stmt) = new AST::ReturnStmt(nullptr); }
#line 1752 "parser.cpp"
    break;

  case 36: /* simple_stmt: VAR IDENTIFIER COLON type_spec  */
#line 207 "parser.y"
                                                 { (yyval.stmt) = new AST::VarDeclStmt(new AST::VarDecl((yyvsp[-2].cstr), (yyvsp[0].cstr), nullptr)); free((yyvsp[-2].cstr)); free((yyvsp[0].cstr)); }
#line 1758 "parser.cpp"
    break;

  case 37: /* simple_stmt: VAR IDENTIFIER COLON type_spec EQUAL expr  */
#line 208 "parser.y"
                                                 { (yyval.stmt) = new AST::VarDeclStmt(new AST::VarDecl((yyvsp[-4].cstr), (yyvsp[-2].cstr), (yyvsp[0].expr))); free((yyvsp[-4].cstr)); free((yyvsp[-2].cstr)); }
#line 1764 "parser.cpp"
    break;

  case 38: /* simple_stmt: VAR IDENTIFIER COLON type_spec ASSIGN expr  */
#line 209 "parser.y"
                                                 { (yyval.stmt) = new AST::VarDeclStmt(new AST::VarDecl((yyvsp[-4].cstr), (yyvsp[-2].cstr), (yyvsp[0].expr))); free((yyvsp[-4].cstr)); free((yyvsp[-2].cstr)); }
#line 1770 "parser.cpp"
    break;

  case 39: /* simple_stmt: lvalue ASSIGN expr  */
#line 210 "parser.y"
                                                 { (yyval.stmt) = new AST::ExprStmt(new AST::Binary(AST::BinOp::Assign, (yyvsp[-2].expr), (yyvsp[0].expr))); }
#line 1776 "parser.cpp"
    break;

  case 40: /* simple_stmt: expr  */
#line 211 "parser.y"
                                                 { (yyval.stmt) = new AST::ExprStmt((yyvsp[0].expr)); }
#line 1782 "parser.cpp"
    break;

  case 41: /* block_stmt: stmt_list  */
#line 216 "parser.y"
      {
        auto* b = new AST::Block();
        for (auto* s : *(yyvsp[0].stmtlist)) b->stmts.push_back(s);
        delete (yyvsp[0].stmtlist);
        (yyval.stmt) = b;
      }
#line 1793 "parser.cpp"
    break;

  case 42: /* if_stmt: IF expr THEN block_stmt elif_tail END  */
#line 226 "parser.y"
      {
        (yyval.stmt) = new AST::IfStmt((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[-1].stmt));
      }
#line 1801 "parser.cpp"
    break;

  case 43: /* elif_tail: ELSEIF expr THEN block_stmt elif_tail  */
#line 233 "parser.y"
      {
        (yyval.stmt) = new AST::IfStmt((yyvsp[-3].expr), (yyvsp[-1].stmt), (yyvsp[0].stmt));
      }
#line 1809 "parser.cpp"
    break;

  case 44: /* elif_tail: opt_else  */
#line 237 "parser.y"
      {
        (yyval.stmt) = (yyvsp[0].stmt) ? (yyvsp[0].stmt) : static_cast<AST::Stmt*>(new AST::Block());
      }
#line 1817 "parser.cpp"
    break;

  case 45: /* opt_else: ELSE block_stmt  */
#line 243 "parser.y"
                      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1823 "parser.cpp"
    break;

  case 46: /* opt_else: %empty  */
#line 244 "parser.y"
                      { (yyval.stmt) = nullptr; }
#line 1829 "parser.cpp"
    break;

  case 47: /* while_stmt: WHILE expr DO stmt_list END  */
#line 249 "parser.y"
      {
        auto* b = new AST::Block();
        for (auto* s : *(yyvsp[-1].stmtlist)) b->stmts.push_back(s);
        delete (yyvsp[-1].stmtlist);
        (yyval.stmt) = new AST::WhileStmt((yyvsp[-3].expr), b);
      }
#line 1840 "parser.cpp"
    break;

  case 48: /* expr: assign_expr  */
#line 258 "parser.y"
                  { (yyval.expr) = (yyvsp[0].expr); }
#line 1846 "parser.cpp"
    break;

  case 49: /* assign_expr: lvalue ASSIGN assign_expr  */
#line 262 "parser.y"
                                { (yyval.expr) = new AST::Binary(AST::BinOp::Assign, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1852 "parser.cpp"
    break;

  case 50: /* assign_expr: equality_expr  */
#line 263 "parser.y"
                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1858 "parser.cpp"
    break;

  case 51: /* equality_expr: equality_expr EQEQ relational_expr  */
#line 267 "parser.y"
                                         { (yyval.expr) = new AST::Binary(AST::BinOp::Eq, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1864 "parser.cpp"
    break;

  case 52: /* equality_expr: relational_expr  */
#line 268 "parser.y"
                                         { (yyval.expr) = (yyvsp[0].expr); }
#line 1870 "parser.cpp"
    break;

  case 53: /* relational_expr: relational_expr GT additive_expr  */
#line 272 "parser.y"
                                       { (yyval.expr) = new AST::Binary(AST::BinOp::Gt, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1876 "parser.cpp"
    break;

  case 54: /* relational_expr: relational_expr LT additive_expr  */
#line 273 "parser.y"
                                       { (yyval.expr) = new AST::Binary(AST::BinOp::Lt, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1882 "parser.cpp"
    break;

  case 55: /* relational_expr: additive_expr  */
#line 274 "parser.y"
                                       { (yyval.expr) = (yyvsp[0].expr); }
#line 1888 "parser.cpp"
    break;

  case 56: /* additive_expr: additive_expr PLUS multiplicative_expr  */
#line 278 "parser.y"
                                              { (yyval.expr) = new AST::Binary(AST::BinOp::Add, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1894 "parser.cpp"
    break;

  case 57: /* additive_expr: additive_expr MINUS multiplicative_expr  */
#line 279 "parser.y"
                                              { (yyval.expr) = new AST::Binary(AST::BinOp::Sub, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1900 "parser.cpp"
    break;

  case 58: /* additive_expr: multiplicative_expr  */
#line 280 "parser.y"
                                              { (yyval.expr) = (yyvsp[0].expr); }
#line 1906 "parser.cpp"
    break;

  case 59: /* multiplicative_expr: multiplicative_expr STAR unary_expr  */
#line 284 "parser.y"
                                           { (yyval.expr) = new AST::Binary(AST::BinOp::Mul, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1912 "parser.cpp"
    break;

  case 60: /* multiplicative_expr: multiplicative_expr SLASH unary_expr  */
#line 285 "parser.y"
                                           { (yyval.expr) = new AST::Binary(AST::BinOp::Div, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1918 "parser.cpp"
    break;

  case 61: /* multiplicative_expr: unary_expr  */
#line 286 "parser.y"
                                           { (yyval.expr) = (yyvsp[0].expr); }
#line 1924 "parser.cpp"
    break;

  case 62: /* unary_expr: MINUS unary_expr  */
#line 290 "parser.y"
                        { (yyval.expr) = new AST::Unary(AST::Unary::Op::Neg, (yyvsp[0].expr)); }
#line 1930 "parser.cpp"
    break;

  case 63: /* unary_expr: postfix_expr  */
#line 291 "parser.y"
                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1936 "parser.cpp"
    break;

  case 64: /* postfix_expr: postfix_expr LPAREN opt_args RPAREN  */
#line 296 "parser.y"
      { auto* call = new AST::Call((yyvsp[-3].expr)); for (auto* e : *(yyvsp[-1].exprlist)) call->args.push_back(e); delete (yyvsp[-1].exprlist); (yyval.expr) = call; }
#line 1942 "parser.cpp"
    break;

  case 65: /* postfix_expr: postfix_expr DOT IDENTIFIER  */
#line 298 "parser.y"
      { (yyval.expr) = new AST::MemberAccess((yyvsp[-2].expr), (yyvsp[0].cstr)); free((yyvsp[0].cstr)); }
#line 1948 "parser.cpp"
    break;

  case 66: /* postfix_expr: postfix_expr LBRACKET expr RBRACKET  */
#line 300 "parser.y"
      { (yyval.expr) = new AST::Index((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 1954 "parser.cpp"
    break;

  case 67: /* postfix_expr: primary_expr  */
#line 302 "parser.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 1960 "parser.cpp"
    break;

  case 68: /* opt_args: arg_list  */
#line 306 "parser.y"
               { (yyval.exprlist) = (yyvsp[0].exprlist); }
#line 1966 "parser.cpp"
    break;

  case 69: /* opt_args: %empty  */
#line 307 "parser.y"
               { (yyval.exprlist) = new std::vector<AST::Expr*>(); }
#line 1972 "parser.cpp"
    break;

  case 70: /* arg_list: arg_list COMMA expr  */
#line 311 "parser.y"
                          { (yyval.exprlist) = (yyvsp[-2].exprlist); (yyvsp[-2].exprlist)->push_back((yyvsp[0].expr)); }
#line 1978 "parser.cpp"
    break;

  case 71: /* arg_list: expr  */
#line 312 "parser.y"
                          { (yyval.exprlist) = new std::vector<AST::Expr*>(); (yyval.exprlist)->push_back((yyvsp[0].expr)); }
#line 1984 "parser.cpp"
    break;

  case 72: /* primary_expr: INT_LITERAL  */
#line 316 "parser.y"
                       { (yyval.expr) = new AST::IntLiteral((yyvsp[0].ival)); }
#line 1990 "parser.cpp"
    break;

  case 73: /* primary_expr: STRING_LITERAL  */
#line 317 "parser.y"
                       { (yyval.expr) = new AST::StringLiteral((yyvsp[0].cstr)); free((yyvsp[0].cstr)); }
#line 1996 "parser.cpp"
    break;

  case 74: /* primary_expr: TRUE  */
#line 318 "parser.y"
                       { (yyval.expr) = new AST::BoolLiteral(true); }
#line 2002 "parser.cpp"
    break;

  case 75: /* primary_expr: FALSE  */
#line 319 "parser.y"
                       { (yyval.expr) = new AST::BoolLiteral(false); }
#line 2008 "parser.cpp"
    break;

  case 76: /* primary_expr: IDENTIFIER  */
#line 320 "parser.y"
                       { (yyval.expr) = new AST::Identifier((yyvsp[0].cstr)); free((yyvsp[0].cstr)); }
#line 2014 "parser.cpp"
    break;

  case 77: /* primary_expr: type_as_expr  */
#line 321 "parser.y"
                       { (yyval.expr) = (yyvsp[0].expr); }
#line 2020 "parser.cpp"
    break;

  case 78: /* primary_expr: LPAREN expr RPAREN  */
#line 322 "parser.y"
                         { (yyval.expr) = (yyvsp[-1].expr); }
#line 2026 "parser.cpp"
    break;

  case 79: /* type_as_expr: type_spec  */
#line 327 "parser.y"
      { (yyval.expr) = new AST::Identifier((yyvsp[0].cstr)); free((yyvsp[0].cstr)); }
#line 2032 "parser.cpp"
    break;

  case 80: /* lvalue: IDENTIFIER  */
#line 331 "parser.y"
                                 { (yyval.expr) = new AST::Identifier((yyvsp[0].cstr)); free((yyvsp[0].cstr)); }
#line 2038 "parser.cpp"
    break;

  case 81: /* lvalue: lvalue DOT IDENTIFIER  */
#line 332 "parser.y"
                                 { (yyval.expr) = new AST::MemberAccess((yyvsp[-2].expr), (yyvsp[0].cstr)); free((yyvsp[0].cstr)); }
#line 2044 "parser.cpp"
    break;

  case 82: /* lvalue: lvalue LBRACKET expr RBRACKET  */
#line 333 "parser.y"
                                    { (yyval.expr) = new AST::Index((yyvsp[-3].expr), (yyvsp[-1].expr)); }
#line 2050 "parser.cpp"
    break;


#line 2054 "parser.cpp"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 336 "parser.y"


void yyerror(const char* s) { std::fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s); }
