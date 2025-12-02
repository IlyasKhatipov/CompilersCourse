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
  YYSYMBOL_EXTENDS = 4,                    /* EXTENDS  */
  YYSYMBOL_IS = 5,                         /* IS  */
  YYSYMBOL_END = 6,                        /* END  */
  YYSYMBOL_VAR = 7,                        /* VAR  */
  YYSYMBOL_METHOD = 8,                     /* METHOD  */
  YYSYMBOL_THIS = 9,                       /* THIS  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_LOOP = 11,                      /* LOOP  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_THEN = 13,                      /* THEN  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_TRUE = 16,                      /* TRUE  */
  YYSYMBOL_FALSE = 17,                     /* FALSE  */
  YYSYMBOL_NEW = 18,                       /* NEW  */
  YYSYMBOL_IDENTIFIER = 19,                /* IDENTIFIER  */
  YYSYMBOL_INTEGER_LITERAL = 20,           /* INTEGER_LITERAL  */
  YYSYMBOL_REAL_LITERAL = 21,              /* REAL_LITERAL  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_ARROW = 23,                     /* ARROW  */
  YYSYMBOL_COLON = 24,                     /* COLON  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_DOT = 26,                       /* DOT  */
  YYSYMBOL_LPAREN = 27,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 28,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 29,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 30,                  /* RBRACKET  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_program = 32,                   /* program  */
  YYSYMBOL_class_list = 33,                /* class_list  */
  YYSYMBOL_class_decl = 34,                /* class_decl  */
  YYSYMBOL_opt_extends = 35,               /* opt_extends  */
  YYSYMBOL_class_body = 36,                /* class_body  */
  YYSYMBOL_member_list = 37,               /* member_list  */
  YYSYMBOL_member = 38,                    /* member  */
  YYSYMBOL_var_decl = 39,                  /* var_decl  */
  YYSYMBOL_method_decl = 40,               /* method_decl  */
  YYSYMBOL_opt_return_type = 41,           /* opt_return_type  */
  YYSYMBOL_method_body = 42,               /* method_body  */
  YYSYMBOL_constructor_decl = 43,          /* constructor_decl  */
  YYSYMBOL_opt_params = 44,                /* opt_params  */
  YYSYMBOL_param_list = 45,                /* param_list  */
  YYSYMBOL_param = 46,                     /* param  */
  YYSYMBOL_body = 47,                      /* body  */
  YYSYMBOL_stmt_list = 48,                 /* stmt_list  */
  YYSYMBOL_stmt = 49,                      /* stmt  */
  YYSYMBOL_simple_stmt = 50,               /* simple_stmt  */
  YYSYMBOL_if_stmt = 51,                   /* if_stmt  */
  YYSYMBOL_opt_else = 52,                  /* opt_else  */
  YYSYMBOL_while_stmt = 53,                /* while_stmt  */
  YYSYMBOL_return_stmt = 54,               /* return_stmt  */
  YYSYMBOL_opt_expr = 55,                  /* opt_expr  */
  YYSYMBOL_expr = 56,                      /* expr  */
  YYSYMBOL_primary_expr = 57,              /* primary_expr  */
  YYSYMBOL_opt_args = 58,                  /* opt_args  */
  YYSYMBOL_arg_list = 59                   /* arg_list  */
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
#define YYLAST   99

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  113

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
       0,    89,    89,    96,   100,   101,   105,   120,   121,   125,
     126,   130,   131,   135,   136,   137,   141,   146,   161,   162,
     166,   168,   176,   180,   188,   189,   193,   194,   198,   203,
     213,   214,   218,   219,   220,   221,   225,   227,   229,   234,
     239,   240,   244,   249,   254,   255,   259,   260,   262,   264,
     266,   268,   278,   279,   280,   281,   282,   283,   284,   288,
     289,   293,   294
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
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "EXTENDS",
  "IS", "END", "VAR", "METHOD", "THIS", "WHILE", "LOOP", "IF", "THEN",
  "ELSE", "RETURN", "TRUE", "FALSE", "NEW", "IDENTIFIER",
  "INTEGER_LITERAL", "REAL_LITERAL", "ASSIGN", "ARROW", "COLON", "COMMA",
  "DOT", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "$accept", "program",
  "class_list", "class_decl", "opt_extends", "class_body", "member_list",
  "member", "var_decl", "method_decl", "opt_return_type", "method_body",
  "constructor_decl", "opt_params", "param_list", "param", "body",
  "stmt_list", "stmt", "simple_stmt", "if_stmt", "opt_else", "while_stmt",
  "return_stmt", "opt_expr", "expr", "primary_expr", "opt_args",
  "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-80)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      12,     6,    36,    12,   -80,    38,   -80,   -80,    21,    39,
     -80,     1,    24,    26,    19,    41,     1,   -80,   -80,   -80,
     -80,    25,    23,    32,   -80,   -80,    14,    32,    28,    27,
      35,   -80,   -80,   -80,   -80,    43,    44,   -80,   -80,    14,
      46,   -80,    45,    55,    72,    32,   -13,    14,    -2,    59,
      56,   -80,    49,   -80,    14,    60,    46,    53,    57,   -80,
      58,    64,    -1,    14,    14,    14,   -16,   -80,    78,    49,
     -80,   -80,   -80,   -80,   -80,    46,    61,    62,   -80,    14,
      14,   -80,    49,    14,   -80,    -9,    -8,   -80,    46,    14,
     -80,   -80,   -80,    63,    46,    65,    80,    46,    49,    49,
      46,    14,   -80,   -80,    81,    74,    66,   -80,    49,    85,
     -80,   -80,   -80
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     2,     5,     8,     1,     4,     0,     0,
       7,    10,     0,     0,     0,     0,     9,    12,    13,    14,
      15,     0,     0,    25,     6,    11,     0,    25,     0,     0,
      24,    27,    57,    54,    55,     0,    56,    52,    53,     0,
      16,    46,     0,     0,     0,     0,     0,    60,     0,     0,
      19,    28,     0,    26,    60,     0,    62,     0,    59,    58,
      47,     0,    22,     0,     0,    45,    56,    36,     0,    29,
      31,    32,    33,    34,    35,    38,     0,     0,    49,     0,
      60,    18,     0,     0,    17,     0,     0,    43,    44,     0,
      23,    30,    50,     0,    61,     0,     0,    21,     0,     0,
      37,    60,    48,    20,     0,    41,     0,    42,     0,     0,
      51,    40,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -80,   -80,   -80,    92,   -80,   -80,   -80,    82,    -4,   -80,
     -80,   -80,   -80,    69,   -80,    52,   -79,   -80,    30,   -80,
     -80,   -80,   -80,   -80,   -80,   -26,   -80,   -53,   -80
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,     9,    15,    16,    17,    67,    19,
      62,    84,    20,    29,    30,    31,    68,    69,    70,    71,
      72,   109,    73,    74,    87,    75,    41,    57,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      40,    76,    98,    96,    82,    99,    89,    18,    12,    13,
      14,    47,    18,    48,    54,     1,    55,    49,    49,   104,
     105,    56,    83,    32,    49,     5,    59,    95,    56,   111,
      33,    34,    35,    36,    37,    38,     6,    85,    86,    88,
      10,    39,     8,    21,    11,    22,    23,    24,   106,    26,
      27,    28,    43,    94,    56,    44,    12,    97,    32,    63,
      45,    64,    46,   100,    65,    33,    34,    35,    66,    37,
      38,    47,    49,    50,    51,    56,    39,    52,    60,    77,
      61,    78,    79,    81,    90,    80,   103,   107,   108,    92,
     101,   112,    93,   102,   110,     7,    42,    53,    25,    91
};

static const yytype_int8 yycheck[] =
{
      26,    54,    11,    82,     5,    13,    22,    11,     7,     8,
       9,    27,    16,    39,    27,     3,    29,    26,    26,    98,
      99,    47,    23,     9,    26,    19,    28,    80,    54,   108,
      16,    17,    18,    19,    20,    21,     0,    63,    64,    65,
      19,    27,     4,    19,     5,    19,    27,     6,   101,    24,
      27,    19,    24,    79,    80,    28,     7,    83,     9,    10,
      25,    12,    19,    89,    15,    16,    17,    18,    19,    20,
      21,    27,    26,    28,    19,   101,    27,     5,    19,    19,
      24,    28,    25,    19,     6,    27,     6,     6,    14,    28,
      27,     6,    30,    28,    28,     3,    27,    45,    16,    69
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    32,    33,    34,    19,     0,    34,     4,    35,
      19,     5,     7,     8,     9,    36,    37,    38,    39,    40,
      43,    19,    19,    27,     6,    38,    24,    27,    19,    44,
      45,    46,     9,    16,    17,    18,    19,    20,    21,    27,
      56,    57,    44,    24,    28,    25,    19,    27,    56,    26,
      28,    19,     5,    46,    27,    29,    56,    58,    59,    28,
      19,    24,    41,    10,    12,    15,    19,    39,    47,    48,
      49,    50,    51,    53,    54,    56,    58,    19,    28,    25,
      27,    19,     5,    23,    42,    56,    56,    55,    56,    22,
       6,    49,    28,    30,    56,    58,    47,    56,    11,    13,
      56,    27,    28,     6,    47,    47,    58,     6,    14,    52,
      28,    47,     6
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    32,    33,    33,    34,    35,    35,    36,
      36,    37,    37,    38,    38,    38,    39,    40,    41,    41,
      42,    42,    42,    43,    44,    44,    45,    45,    46,    47,
      48,    48,    49,    49,    49,    49,    50,    50,    50,    51,
      52,    52,    53,    54,    55,    55,    56,    56,    56,    56,
      56,    56,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    59,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     6,     2,     0,     1,
       0,     2,     1,     1,     1,     1,     4,     7,     2,     0,
       3,     2,     0,     7,     1,     0,     3,     1,     3,     1,
       2,     1,     1,     1,     1,     1,     1,     3,     1,     6,
       2,     0,     5,     2,     1,     0,     1,     3,     6,     4,
       5,     8,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     3,     1
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
#line 90 "parser.y"
      {
        g_program = new AST::Program();
        for (auto* c : *(yyvsp[0].classlist)) g_program->classes.push_back(c);
        delete (yyvsp[0].classlist);
      }
#line 1478 "parser.cpp"
    break;

  case 3: /* program: %empty  */
#line 96 "parser.y"
      { g_program = new AST::Program(); }
#line 1484 "parser.cpp"
    break;

  case 4: /* class_list: class_list class_decl  */
#line 100 "parser.y"
                            { (yyval.classlist) = (yyvsp[-1].classlist); (yyvsp[-1].classlist)->push_back((yyvsp[0].classdecl)); }
#line 1490 "parser.cpp"
    break;

  case 5: /* class_list: class_decl  */
#line 101 "parser.y"
                            { (yyval.classlist) = new std::vector<AST::ClassDecl*>(); (yyval.classlist)->push_back((yyvsp[0].classdecl)); }
#line 1496 "parser.cpp"
    break;

  case 6: /* class_decl: CLASS IDENTIFIER opt_extends IS class_body END  */
#line 106 "parser.y"
      {
        (yyval.classdecl) = new AST::ClassDecl((yyvsp[-4].cstr), (yyvsp[-3].cstr));
        for (auto* n : *(yyvsp[-1].memberlist)) {
          if (auto* v = dynamic_cast<AST::VarDecl*>(n)) (yyval.classdecl)->fields.push_back(v);
          else if (auto* m = dynamic_cast<AST::MethodDecl*>(n)) (yyval.classdecl)->methods.push_back(m);
          else if (auto* c = dynamic_cast<AST::ConstructorDecl*>(n)) (yyval.classdecl)->constructors.push_back(c);
          else delete n;
        }
        free((yyvsp[-4].cstr));
        delete (yyvsp[-1].memberlist);
      }
#line 1512 "parser.cpp"
    break;

  case 7: /* opt_extends: EXTENDS IDENTIFIER  */
#line 120 "parser.y"
                         { (yyval.cstr) = strdup((yyvsp[0].cstr)); free((yyvsp[0].cstr)); }
#line 1518 "parser.cpp"
    break;

  case 8: /* opt_extends: %empty  */
#line 121 "parser.y"
                         { (yyval.cstr) = nullptr; }
#line 1524 "parser.cpp"
    break;

  case 9: /* class_body: member_list  */
#line 125 "parser.y"
                  { (yyval.memberlist) = (yyvsp[0].memberlist); }
#line 1530 "parser.cpp"
    break;

  case 10: /* class_body: %empty  */
#line 126 "parser.y"
                  { (yyval.memberlist) = new std::vector<AST::Node*>(); }
#line 1536 "parser.cpp"
    break;

  case 11: /* member_list: member_list member  */
#line 130 "parser.y"
                         { (yyval.memberlist) = (yyvsp[-1].memberlist); (yyvsp[-1].memberlist)->push_back((yyvsp[0].node)); }
#line 1542 "parser.cpp"
    break;

  case 12: /* member_list: member  */
#line 131 "parser.y"
                         { (yyval.memberlist) = new std::vector<AST::Node*>(); (yyval.memberlist)->push_back((yyvsp[0].node)); }
#line 1548 "parser.cpp"
    break;

  case 13: /* member: var_decl  */
#line 135 "parser.y"
                       { (yyval.node) = (yyvsp[0].vardecl); }
#line 1554 "parser.cpp"
    break;

  case 14: /* member: method_decl  */
#line 136 "parser.y"
                       { (yyval.node) = (yyvsp[0].methoddecl); }
#line 1560 "parser.cpp"
    break;

  case 15: /* member: constructor_decl  */
#line 137 "parser.y"
                       { (yyval.node) = (yyvsp[0].constructor); }
#line 1566 "parser.cpp"
    break;

  case 16: /* var_decl: VAR IDENTIFIER COLON expr  */
#line 142 "parser.y"
      { (yyval.vardecl) = new AST::VarDecl((yyvsp[-2].cstr), (yyvsp[0].expr)); free((yyvsp[-2].cstr)); }
#line 1572 "parser.cpp"
    break;

  case 17: /* method_decl: METHOD IDENTIFIER LPAREN opt_params RPAREN opt_return_type method_body  */
#line 147 "parser.y"
      {
        // Создаем строку возвращаемого типа
        std::string returnType = (yyvsp[-1].cstr) ? std::string((yyvsp[-1].cstr)) : "";
        (yyval.methoddecl) = new AST::MethodDecl((yyvsp[-5].cstr), returnType, (yyvsp[0].stmt));
        if ((yyvsp[-3].paramlist)) {
          for (auto* p : *(yyvsp[-3].paramlist)) (yyval.methoddecl)->params.push_back(p);
          delete (yyvsp[-3].paramlist);
        }
        free((yyvsp[-5].cstr));
        if ((yyvsp[-1].cstr)) free((yyvsp[-1].cstr));
      }
#line 1588 "parser.cpp"
    break;

  case 18: /* opt_return_type: COLON IDENTIFIER  */
#line 161 "parser.y"
                       { (yyval.cstr) = strdup((yyvsp[0].cstr)); free((yyvsp[0].cstr)); }
#line 1594 "parser.cpp"
    break;

  case 19: /* opt_return_type: %empty  */
#line 162 "parser.y"
                       { (yyval.cstr) = nullptr; }
#line 1600 "parser.cpp"
    break;

  case 20: /* method_body: IS body END  */
#line 167 "parser.y"
      { (yyval.stmt) = (yyvsp[-1].block); }
#line 1606 "parser.cpp"
    break;

  case 21: /* method_body: ARROW expr  */
#line 169 "parser.y"
      { 
        auto* returnStmt = new AST::ReturnStmt((yyvsp[0].expr));
        auto* block = new AST::Block();
        block->stmts.push_back(returnStmt);
        (yyval.stmt) = block;
      }
#line 1617 "parser.cpp"
    break;

  case 22: /* method_body: %empty  */
#line 176 "parser.y"
      { (yyval.stmt) = nullptr; }
#line 1623 "parser.cpp"
    break;

  case 23: /* constructor_decl: THIS LPAREN opt_params RPAREN IS body END  */
#line 181 "parser.y"
      {
        (yyval.constructor) = new AST::ConstructorDecl((yyvsp[-4].paramlist));
        (yyval.constructor)->body = (yyvsp[-1].block);
      }
#line 1632 "parser.cpp"
    break;

  case 24: /* opt_params: param_list  */
#line 188 "parser.y"
                 { (yyval.paramlist) = (yyvsp[0].paramlist); }
#line 1638 "parser.cpp"
    break;

  case 25: /* opt_params: %empty  */
#line 189 "parser.y"
                  { (yyval.paramlist) = new std::vector<AST::Param*>(); }
#line 1644 "parser.cpp"
    break;

  case 26: /* param_list: param_list COMMA param  */
#line 193 "parser.y"
                             { (yyval.paramlist) = (yyvsp[-2].paramlist); (yyvsp[-2].paramlist)->push_back((yyvsp[0].param)); }
#line 1650 "parser.cpp"
    break;

  case 27: /* param_list: param  */
#line 194 "parser.y"
                             { (yyval.paramlist) = new std::vector<AST::Param*>(); (yyval.paramlist)->push_back((yyvsp[0].param)); }
#line 1656 "parser.cpp"
    break;

  case 28: /* param: IDENTIFIER COLON IDENTIFIER  */
#line 199 "parser.y"
      { (yyval.param) = new AST::Param((yyvsp[-2].cstr), (yyvsp[0].cstr)); free((yyvsp[-2].cstr)); free((yyvsp[0].cstr)); }
#line 1662 "parser.cpp"
    break;

  case 29: /* body: stmt_list  */
#line 204 "parser.y"
      {
        auto* b = new AST::Block();
        for (auto* s : *(yyvsp[0].stmtlist)) b->stmts.push_back(s);
        delete (yyvsp[0].stmtlist);
        (yyval.block) = b;
      }
#line 1673 "parser.cpp"
    break;

  case 30: /* stmt_list: stmt_list stmt  */
#line 213 "parser.y"
                     { (yyval.stmtlist) = (yyvsp[-1].stmtlist); (yyvsp[-1].stmtlist)->push_back((yyvsp[0].stmt)); }
#line 1679 "parser.cpp"
    break;

  case 31: /* stmt_list: stmt  */
#line 214 "parser.y"
                     { (yyval.stmtlist) = new std::vector<AST::Stmt*>(); (yyval.stmtlist)->push_back((yyvsp[0].stmt)); }
#line 1685 "parser.cpp"
    break;

  case 36: /* simple_stmt: var_decl  */
#line 226 "parser.y"
      { (yyval.stmt) = new AST::VarDeclStmt((yyvsp[0].vardecl)); }
#line 1691 "parser.cpp"
    break;

  case 37: /* simple_stmt: IDENTIFIER ASSIGN expr  */
#line 228 "parser.y"
      { (yyval.stmt) = new AST::AssignmentStmt((yyvsp[-2].cstr), (yyvsp[0].expr)); free((yyvsp[-2].cstr)); }
#line 1697 "parser.cpp"
    break;

  case 38: /* simple_stmt: expr  */
#line 230 "parser.y"
      { (yyval.stmt) = new AST::ExprStmt((yyvsp[0].expr)); }
#line 1703 "parser.cpp"
    break;

  case 39: /* if_stmt: IF expr THEN body opt_else END  */
#line 235 "parser.y"
      { (yyval.stmt) = new AST::IfStmt((yyvsp[-4].expr), (yyvsp[-2].block), (yyvsp[-1].block)); }
#line 1709 "parser.cpp"
    break;

  case 40: /* opt_else: ELSE body  */
#line 239 "parser.y"
                { (yyval.block) = (yyvsp[0].block); }
#line 1715 "parser.cpp"
    break;

  case 41: /* opt_else: %empty  */
#line 240 "parser.y"
                  { (yyval.block) = nullptr; }
#line 1721 "parser.cpp"
    break;

  case 42: /* while_stmt: WHILE expr LOOP body END  */
#line 245 "parser.y"
      { (yyval.stmt) = new AST::WhileStmt((yyvsp[-3].expr), (yyvsp[-1].block)); }
#line 1727 "parser.cpp"
    break;

  case 43: /* return_stmt: RETURN opt_expr  */
#line 250 "parser.y"
      { (yyval.stmt) = new AST::ReturnStmt((yyvsp[0].expr)); }
#line 1733 "parser.cpp"
    break;

  case 44: /* opt_expr: expr  */
#line 254 "parser.y"
           { (yyval.expr) = (yyvsp[0].expr); }
#line 1739 "parser.cpp"
    break;

  case 45: /* opt_expr: %empty  */
#line 255 "parser.y"
                  { (yyval.expr) = nullptr; }
#line 1745 "parser.cpp"
    break;

  case 47: /* expr: expr DOT IDENTIFIER  */
#line 261 "parser.y"
      { (yyval.expr) = new AST::MemberAccess((yyvsp[-2].expr), (yyvsp[0].cstr)); free((yyvsp[0].cstr)); }
#line 1751 "parser.cpp"
    break;

  case 48: /* expr: expr DOT IDENTIFIER LPAREN opt_args RPAREN  */
#line 263 "parser.y"
      { (yyval.expr) = new AST::MethodCall((yyvsp[-5].expr), (yyvsp[-3].cstr), (yyvsp[-1].exprlist)); free((yyvsp[-3].cstr)); }
#line 1757 "parser.cpp"
    break;

  case 49: /* expr: IDENTIFIER LPAREN opt_args RPAREN  */
#line 265 "parser.y"
      { (yyval.expr) = new AST::MethodCall(new AST::Identifier("this"), (yyvsp[-3].cstr), (yyvsp[-1].exprlist)); free((yyvsp[-3].cstr)); }
#line 1763 "parser.cpp"
    break;

  case 50: /* expr: NEW IDENTIFIER LPAREN opt_args RPAREN  */
#line 267 "parser.y"
      { (yyval.expr) = new AST::ConstructorCall((yyvsp[-3].cstr), (yyvsp[-1].exprlist)); free((yyvsp[-3].cstr)); }
#line 1769 "parser.cpp"
    break;

  case 51: /* expr: NEW IDENTIFIER LBRACKET IDENTIFIER RBRACKET LPAREN opt_args RPAREN  */
#line 269 "parser.y"
      { 
        std::string type = std::string((yyvsp[-6].cstr)) + "[" + (yyvsp[-4].cstr) + "]";
        (yyval.expr) = new AST::ConstructorCall(strdup(type.c_str()), (yyvsp[-1].exprlist)); 
        free((yyvsp[-6].cstr)); 
        free((yyvsp[-4].cstr)); 
      }
#line 1780 "parser.cpp"
    break;

  case 52: /* primary_expr: INTEGER_LITERAL  */
#line 278 "parser.y"
                           { (yyval.expr) = new AST::IntLiteral((yyvsp[0].ival)); }
#line 1786 "parser.cpp"
    break;

  case 53: /* primary_expr: REAL_LITERAL  */
#line 279 "parser.y"
                           { (yyval.expr) = new AST::RealLiteral((yyvsp[0].dval)); }
#line 1792 "parser.cpp"
    break;

  case 54: /* primary_expr: TRUE  */
#line 280 "parser.y"
                           { (yyval.expr) = new AST::BoolLiteral(true); }
#line 1798 "parser.cpp"
    break;

  case 55: /* primary_expr: FALSE  */
#line 281 "parser.y"
                           { (yyval.expr) = new AST::BoolLiteral(false); }
#line 1804 "parser.cpp"
    break;

  case 56: /* primary_expr: IDENTIFIER  */
#line 282 "parser.y"
                           { (yyval.expr) = new AST::Identifier((yyvsp[0].cstr)); free((yyvsp[0].cstr)); }
#line 1810 "parser.cpp"
    break;

  case 57: /* primary_expr: THIS  */
#line 283 "parser.y"
                           { (yyval.expr) = new AST::ThisLiteral(); }
#line 1816 "parser.cpp"
    break;

  case 58: /* primary_expr: LPAREN expr RPAREN  */
#line 284 "parser.y"
                           { (yyval.expr) = (yyvsp[-1].expr); }
#line 1822 "parser.cpp"
    break;

  case 59: /* opt_args: arg_list  */
#line 288 "parser.y"
               { (yyval.exprlist) = (yyvsp[0].exprlist); }
#line 1828 "parser.cpp"
    break;

  case 60: /* opt_args: %empty  */
#line 289 "parser.y"
                  { (yyval.exprlist) = new std::vector<AST::Expr*>(); }
#line 1834 "parser.cpp"
    break;

  case 61: /* arg_list: arg_list COMMA expr  */
#line 293 "parser.y"
                          { (yyval.exprlist) = (yyvsp[-2].exprlist); (yyvsp[-2].exprlist)->push_back((yyvsp[0].expr)); }
#line 1840 "parser.cpp"
    break;

  case 62: /* arg_list: expr  */
#line 294 "parser.y"
                          { (yyval.exprlist) = new std::vector<AST::Expr*>(); (yyval.exprlist)->push_back((yyvsp[0].expr)); }
#line 1846 "parser.cpp"
    break;


#line 1850 "parser.cpp"

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

#line 297 "parser.y"


void yyerror(const char* s) { std::fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s); }
