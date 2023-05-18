/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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

    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    #include"lex.yy.c"

//Analyse yacc fonctions
    void yyerror(const char *s);
    int yylex();
// Table de symbole fonctions
    void ajouter(char);
    int chercher(char *);


// Affichage d'arbre syntaxique
	void afficher_arbre(struct noeud*);
	void afficher_arbre_to_file(FILE* f,struct noeud*);
	void afficher_dans_lorder(struct noeud *);
	void affichage_prifixe_de_larbre_syntaxique(FILE* f,struct noeud *,int* j);
	struct noeud* faire_noeud(struct noeud *gauche, struct noeud *droite, char *lexeme);
	void afficher_les_dependances_dot(FILE* f,struct noeud *tree,int* j);


// Analyse semantique
    void verefier_declaration(char *);
	void verefier_type_de_return(char *);
	char *retrurner_type(char *);

	struct noeud_lcrs* faire_noeud_lcrs(struct noeud_lcrs *left_child, struct noeud_lcrs *right_sibling, char *description);
   // Fonctions pour dessiner l'arbre de l'output
    void afficher_les_dependances_dot_lcrs(FILE* f,struct noeud_lcrs *tree);
	void affichage_prifixe_de_larbre_syntaxique_dot_lcrs(FILE* f,struct noeud_lcrs *tree,int* j);
	void afficher_arbre_dot_lcrs(FILE* f,struct noeud_lcrs* tree);
	void  ajouter_dernier_fils(struct noeud_lcrs* pere,struct noeud_lcrs* fils);
	struct noeud_lcrs* get_last_sibling(struct noeud_lcrs* tree);
	// Concatenation avec creation d'un nouveau chaine
	char* concatener(char*a,char*b);
	//insertion du lexeme rencontré dans la variable type
	void inserer_type();
	//Un table de symbole statique de longeur 100
	struct dataType {
        char * nom_id;
        char * type_data;
        char * type;
        int ligne_nombre;
	} table_de_symbols[100];
//une variable pour garder le nom de la fonction principale 'la premiere fonction rencontrée'
	char* main_function=NULL;
//Un nombre qui compte le nombre des symboles dans la table de symbole
    int compter_symbole=0;

    int requete;//variable temporaire
	char type[10];//variable temporaire qui garde le type d'un lexeme 
	extern int yylineno; 
	struct noeud *head;
	struct noeud_lcrs *head_dot;

	int sem_errors=0;//Nombre des erreurs sémantique
	int _3var_index=0;// nombre des instruction en 3 var code

	int temp_var=0;//Compteur pour les registres en 3 var code
	int label_count=0;//the number of labels in the 3 variable code 
	int is_for=0;// pour code 3 var pour destiguer l'utilisation d'une condition 
	char buff_3var[300];//variable temporaire pour enregistrer les chaines 3 var
	char strTmp[300];//variable temporaire pour enregistrer les chaines des description des fichier DOT
	char errors[10][100];// Un tableu des erreurs sémantiques
	char reserves[12][10] = {"extern", "int", "void", "for", "while", "if", "then","else", "switch", "case", "default", "break"};
	char code3v[500][100];//Tableu pour stocker le code 3 var

	struct noeud { 
		struct noeud *gauche; 
		struct noeud *droite; 
		char *lexeme; 
	};
	struct noeud_lcrs { 
		struct noeud_lcrs *left_child; 
		struct noeud_lcrs *right_sibling; 
		char *description;
		int inode;
	};


#line 153 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    VOID = 258,
    EXTERN = 259,
    INT = 260,
    CHAR = 261,
    FOR = 262,
    WHILE = 263,
    SWITCH = 264,
    CASE = 265,
    DEFAULT = 266,
    BREAK = 267,
    THEN = 268,
    IF = 269,
    ELSE = 270,
    TRUE = 271,
    FALSE = 272,
    CONSTANTE = 273,
    IDENTIFICATEUR = 274,
    LEQ = 275,
    GEQ = 276,
    EQ = 277,
    NOT = 278,
    GT = 279,
    BAND = 280,
    BOR = 281,
    LSHIFT = 282,
    RSHIFT = 283,
    LT = 284,
    LAND = 285,
    LOR = 286,
    NEQ = 287,
    STR = 288,
    PLUS = 289,
    MUL = 290,
    DIV = 291,
    MOINS = 292,
    UNARY = 293,
    INCLUDE = 294,
    RETURN = 295,
    OP = 296,
    REL = 297
  };
#endif
/* Tokens.  */
#define VOID 258
#define EXTERN 259
#define INT 260
#define CHAR 261
#define FOR 262
#define WHILE 263
#define SWITCH 264
#define CASE 265
#define DEFAULT 266
#define BREAK 267
#define THEN 268
#define IF 269
#define ELSE 270
#define TRUE 271
#define FALSE 272
#define CONSTANTE 273
#define IDENTIFICATEUR 274
#define LEQ 275
#define GEQ 276
#define EQ 277
#define NOT 278
#define GT 279
#define BAND 280
#define BOR 281
#define LSHIFT 282
#define RSHIFT 283
#define LT 284
#define LAND 285
#define LOR 286
#define NEQ 287
#define STR 288
#define PLUS 289
#define MUL 290
#define DIV 291
#define MOINS 292
#define UNARY 293
#define INCLUDE 294
#define RETURN 295
#define OP 296
#define REL 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 84 "parser.y"
 struct nom_variable { 
			char nom[100]; 
			struct noeud* nd;
			struct noeud_lcrs* nd_dot;
		} nd_obj;

		struct nom_variable2 { 
			char nom[100]; 
			struct noeud* nd;
			struct noeud_lcrs* nd_dot;
			char type[5];
		} nd_obj2; 

		struct nom_variable3 {
			char nom[100];
			struct noeud* nd;
			struct noeud_lcrs* nd_dot;
			char if_corps[5];
			char else_corps[5];
		} nd_obj3;
	

#line 312 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   219

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  163

#define YYUNDEFTOK  2
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      43,    44,     2,     2,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    52,    47,
       2,    51,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   122,   122,   133,   141,   143,   153,   156,   156,   164,
     164,   167,   168,   169,   172,   172,   178,   179,   180,   182,
     183,   183,   186,   188,   189,   191,   199,   200,   202,   203,
     203,   216,   217,   218,   220,   221,   222,   227,   228,   228,
     235,   235,   239,   239,   251,   267,   270,   271,   270,   277,
     278,   279,   277,   288,   289,   290,   296,   304,   309,   312,
     317,   325,   326,   334,   335,   335,   340,   341,   344,   345,
     351,   352,   353,   354,   355,   356,   357,   358,   361,   377,
     378,   379,   380,   384,   394,   402,   403,   404,   405,   408,
     409,   410,   411,   412,   413,   416,   425,   428,   434,   438
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VOID", "EXTERN", "INT", "CHAR", "FOR",
  "WHILE", "SWITCH", "CASE", "DEFAULT", "BREAK", "THEN", "IF", "ELSE",
  "TRUE", "FALSE", "CONSTANTE", "IDENTIFICATEUR", "LEQ", "GEQ", "EQ",
  "NOT", "GT", "BAND", "BOR", "LSHIFT", "RSHIFT", "LT", "LAND", "LOR",
  "NEQ", "STR", "PLUS", "MUL", "DIV", "MOINS", "UNARY", "INCLUDE",
  "RETURN", "OP", "REL", "'('", "')'", "'{'", "'}'", "';'", "','", "'['",
  "']'", "'='", "':'", "$accept", "programme1", "liste_fonctions",
  "fonction", "nom_fonction", "$@1", "externe", "$@2", "liste_parms",
  "parm", "$@3", "liste_declarateurs", "declarateur", "$@4", "declaration",
  "datatype", "liste_instructions", "instruction", "$@5", "instruction1",
  "$@6", "$@7", "$@8", "init", "selection", "$@9", "$@10", "$@11", "$@12",
  "$@13", "appel", "variable", "tableu", "expression", "$@14",
  "liste_expressions", "binary_op", "condition", "arithmetic",
  "binary_comp", "valeur", "returne", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    40,    41,   123,   125,    59,    44,    91,
      93,    61,    58
};
# endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-61)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      52,   -74,     6,   -74,    30,    52,   -74,    -8,   -74,    18,
      41,   -74,   -74,    22,   -74,   -74,    17,   -74,    25,    12,
      66,   -74,    34,    55,    36,    39,   -74,   -33,    62,    35,
     -74,    74,    50,    12,    58,   -74,   -74,   -74,   -74,   -40,
     -74,    67,    94,    57,    80,   -74,    71,    76,    94,    70,
     175,    79,   -74,   -74,   -36,    94,    94,   -74,   -74,    78,
     115,   -74,   -74,    82,    49,   -74,   -74,   -74,   111,    89,
      66,   -13,   119,    80,   -74,    85,    85,   166,   -32,    94,
     -74,   -74,   -74,   -74,   -74,   -74,    94,   -74,   -74,    94,
     183,   132,    94,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,    94,    94,   -74,    74,   120,    61,   -74,   -74,
     -74,   -74,    -5,    92,    80,   -74,   -74,   -74,   118,   153,
     121,   126,   117,    94,   166,   166,     1,   -74,    98,   -74,
     166,   -74,   -74,   -74,   -74,   -74,    85,   -74,    85,    94,
     -74,   -74,   -74,   166,   -74,   -74,   122,   124,   139,   166,
      80,    29,   -74,   -13,   -74,   -74,   -74,   140,   171,    80,
      80,   -74,   -74
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    24,     0,    23,     0,     2,     4,     0,     6,     0,
       0,     1,     3,     0,     7,     9,     0,     8,     0,    27,
      13,    29,     0,     0,     0,     0,    46,    40,     0,     0,
      34,     0,     0,    26,     0,    31,    33,    35,    14,     0,
      12,     0,     0,     0,    28,    36,     0,     0,     0,     0,
       0,     0,    44,    64,    57,     0,     0,    98,    66,    58,
       0,    84,    19,     0,    17,     5,    25,    32,     0,     0,
       0,    37,     0,    28,    55,    82,    82,    69,     0,     0,
      91,    92,    93,    90,    89,    94,     0,    43,    65,     0,
      63,     0,     0,    76,    77,    74,    75,    70,    72,    73,
      71,    97,     0,     0,    22,     0,     0,     0,    18,    15,
      10,    11,    40,     0,    28,    54,    80,    81,     0,     0,
       0,     0,     0,     0,    39,    41,     0,    61,     0,    62,
      83,    16,    20,    95,    96,    45,    82,    53,    82,     0,
      47,    50,    56,    68,    67,    59,     0,     0,     0,    78,
      28,    28,    21,    37,    79,    48,    51,     0,     0,    28,
      28,    30,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,   -74,   -74,   193,   -74,   -74,   -74,   -74,   -74,   135,
     -74,   101,   -74,   -74,   -74,    42,   179,   -44,   -74,   -69,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,   -28,   -74,   125,   -74,   -73,   -74,    96,
     106,   -74
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    17,     8,    18,    39,    40,
      68,    63,    64,   146,    30,    31,    32,    33,    41,    34,
      49,    50,    51,   108,    35,    46,   150,    47,   151,   158,
      36,    58,    59,   119,    88,    78,   102,   120,   103,    86,
      61,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,    60,   113,   121,    69,   -42,   112,    89,    70,     1,
      48,     3,   122,   -60,    72,     1,   123,     3,   -38,    21,
      77,    22,    23,    24,    25,    28,    26,    90,    91,   115,
      11,    27,     1,   -42,     3,    13,    21,    14,    22,    23,
      24,    25,     9,    26,    10,   144,   -38,     9,    27,   123,
      28,   124,    29,    53,    54,     1,     2,     3,   125,   -28,
      15,    77,    19,   147,   128,   148,    16,    28,    20,    29,
     137,    38,    55,    43,   129,   130,   -37,    42,    56,   133,
     134,    52,    57,     1,   157,     3,    45,    21,    44,    22,
      23,    24,    25,    62,    26,   143,    65,   105,   106,    27,
     107,   116,   117,    53,    54,    67,   155,   156,   118,    73,
      71,   149,    53,    54,    75,   161,   162,    87,    28,    76,
      29,    79,    55,    93,    94,    95,    96,    92,    56,   104,
     109,    55,    97,    98,    99,   100,   110,    56,   132,   136,
      93,    94,    95,    96,    93,    94,    95,    96,   145,    97,
      98,    99,   100,    97,    98,    99,   100,    93,    94,    95,
      96,   138,   101,   114,   142,   140,    97,    98,    99,   100,
     141,   153,   152,    80,    81,    82,   127,    83,    93,    94,
      95,    96,    84,   154,   159,    85,   160,    97,    98,    99,
     100,    93,    94,    95,    96,    80,    81,    82,    12,    83,
      97,    98,    99,   100,    84,   111,   131,    85,    93,    94,
      95,    96,    66,   135,   126,   139,     0,     0,    98,    99
};

static const yytype_int16 yycheck[] =
{
      44,    29,    71,    76,    44,    38,    19,    43,    48,     3,
      43,     5,    44,    49,    42,     3,    48,     5,    51,     7,
      48,     9,    10,    11,    12,    38,    14,    55,    56,    73,
       0,    19,     3,    38,     5,    43,     7,    19,     9,    10,
      11,    12,     0,    14,     2,    44,    51,     5,    19,    48,
      38,    79,    40,    18,    19,     3,     4,     5,    86,    47,
      19,    89,    45,   136,    92,   138,    44,    38,    43,    40,
     114,     5,    37,    18,   102,   103,    47,    43,    43,    18,
      19,    19,    47,     3,   153,     5,    47,     7,    52,     9,
      10,    11,    12,    19,    14,   123,    46,    48,    49,    19,
      51,    16,    17,    18,    19,    47,   150,   151,    23,    52,
      43,   139,    18,    19,    43,   159,   160,    38,    38,    43,
      40,    51,    37,    25,    26,    27,    28,    49,    43,    47,
      19,    37,    34,    35,    36,    37,    47,    43,    18,    47,
      25,    26,    27,    28,    25,    26,    27,    28,    50,    34,
      35,    36,    37,    34,    35,    36,    37,    25,    26,    27,
      28,    43,    47,    44,    47,    44,    34,    35,    36,    37,
      44,    47,    50,    20,    21,    22,    44,    24,    25,    26,
      27,    28,    29,    44,    44,    32,    15,    34,    35,    36,
      37,    25,    26,    27,    28,    20,    21,    22,     5,    24,
      34,    35,    36,    37,    29,    70,   105,    32,    25,    26,
      27,    28,    33,   107,    89,   119,    -1,    -1,    35,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    54,    55,    56,    57,    59,    68,
      68,     0,    56,    43,    19,    19,    44,    58,    60,    45,
      43,     7,     9,    10,    11,    12,    14,    19,    38,    40,
      67,    68,    69,    70,    72,    77,    83,    94,     5,    61,
      62,    71,    43,    18,    52,    47,    78,    80,    43,    73,
      74,    75,    19,    18,    19,    37,    43,    47,    84,    85,
      86,    93,    19,    64,    65,    46,    69,    47,    63,    44,
      48,    43,    86,    52,    70,    43,    43,    86,    88,    51,
      20,    21,    22,    24,    29,    32,    92,    38,    87,    43,
      86,    86,    49,    25,    26,    27,    28,    34,    35,    36,
      37,    47,    89,    91,    47,    48,    49,    51,    76,    19,
      47,    62,    19,    72,    44,    70,    16,    17,    23,    86,
      90,    90,    44,    48,    86,    86,    88,    44,    86,    86,
      86,    64,    18,    18,    19,    93,    47,    70,    43,    92,
      44,    44,    47,    86,    44,    50,    66,    90,    90,    86,
      79,    81,    50,    47,    44,    70,    70,    72,    82,    44,
      15,    70,    70
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    58,    57,    60,
      59,    61,    61,    61,    63,    62,    64,    64,    64,    65,
      66,    65,    67,    68,    68,    69,    69,    69,    70,    71,
      70,    70,    70,    70,    70,    70,    70,    72,    73,    72,
      74,    72,    75,    72,    72,    76,    78,    79,    77,    80,
      81,    82,    77,    77,    77,    77,    83,    84,    84,    85,
      85,    86,    86,    86,    87,    86,    86,    86,    88,    88,
      89,    89,    89,    89,    89,    89,    89,    89,    90,    90,
      90,    90,    90,    86,    86,    91,    91,    91,    91,    92,
      92,    92,    92,    92,    92,    93,    93,    94,    94,    94
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     6,     1,     0,     3,     0,
       8,     3,     1,     0,     0,     3,     3,     1,     2,     1,
       0,     5,     3,     1,     1,     2,     1,     0,     0,     0,
      10,     1,     2,     1,     1,     1,     2,     0,     0,     4,
       0,     4,     0,     3,     2,     2,     0,     0,     7,     0,
       0,     0,    10,     5,     4,     3,     5,     1,     1,     4,
       1,     3,     3,     2,     0,     2,     1,     4,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     4,
       1,     1,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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
  case 2:
#line 123 "parser.y"
                {
		(yyval.nd_obj).nd=faire_noeud((yyvsp[0].nd_obj).nd,NULL,"programme");
		head = (yyval.nd_obj).nd; 


		(yyval.nd_obj).nd_dot=faire_noeud_lcrs((yyvsp[0].nd_obj).nd_dot,NULL,"label=programme");
		head_dot=(yyval.nd_obj).nd_dot;}
#line 1626 "y.tab.c"
    break;

  case 3:
#line 134 "parser.y"
                {
		(yyval.nd_obj).nd=faire_noeud((yyvsp[-1].nd_obj).nd,(yyvsp[0].nd_obj).nd,"fonctions");
		(yyval.nd_obj).nd_dot=(yyvsp[-1].nd_obj).nd_dot;
		
		
		if((yyvsp[-1].nd_obj).nd_dot)(yyvsp[-1].nd_obj).nd_dot->right_sibling=(yyvsp[0].nd_obj).nd_dot;
		}
#line 1638 "y.tab.c"
    break;

  case 4:
#line 141 "parser.y"
                         {(yyval.nd_obj).nd=(yyvsp[0].nd_obj).nd; (yyval.nd_obj).nd_dot=(yyvsp[0].nd_obj).nd_dot;}
#line 1644 "y.tab.c"
    break;

  case 5:
#line 143 "parser.y"
                                                           { 
(yyval.nd_obj).nd = (yyvsp[-5].nd_obj).nd;
(yyvsp[-5].nd_obj).nd->gauche=(yyvsp[-1].nd_obj).nd;



(yyval.nd_obj).nd_dot = (yyvsp[-5].nd_obj).nd_dot;
(yyvsp[-5].nd_obj).nd_dot->left_child=faire_noeud_lcrs((yyvsp[-1].nd_obj).nd_dot, NULL, "label=BLOC");

}
#line 1659 "y.tab.c"
    break;

  case 6:
#line 153 "parser.y"
          {(yyval.nd_obj).nd=NULL;(yyval.nd_obj).nd_dot=NULL;}
#line 1665 "y.tab.c"
    break;

  case 7:
#line 156 "parser.y"
                                      { ajouter('F'); if(!main_function)main_function=concatener("",yytext);}
#line 1671 "y.tab.c"
    break;

  case 8:
#line 157 "parser.y"
{
(yyval.nd_obj).nd=faire_noeud(NULL,NULL,concatener("fonction ",(yyvsp[-1].nd_obj).nom));
sprintf(strTmp,"label=\"%s, %s\" shape=invtrapezium color=blue",(yyvsp[-1].nd_obj).nom,(yyvsp[-2].nd_obj).nom);
(yyval.nd_obj).nd_dot=faire_noeud_lcrs(NULL, NULL, strTmp);

}
#line 1682 "y.tab.c"
    break;

  case 9:
#line 164 "parser.y"
                                        { ajouter('F'); }
#line 1688 "y.tab.c"
    break;

  case 14:
#line 172 "parser.y"
                    { inserer_type(); }
#line 1694 "y.tab.c"
    break;

  case 15:
#line 172 "parser.y"
                                                       { ajouter('V'); }
#line 1700 "y.tab.c"
    break;

  case 19:
#line 182 "parser.y"
                                  {ajouter('V');}
#line 1706 "y.tab.c"
    break;

  case 20:
#line 183 "parser.y"
                                          {ajouter('C');}
#line 1712 "y.tab.c"
    break;

  case 23:
#line 188 "parser.y"
               { inserer_type(); }
#line 1718 "y.tab.c"
    break;

  case 24:
#line 189 "parser.y"
       { inserer_type(); }
#line 1724 "y.tab.c"
    break;

  case 25:
#line 192 "parser.y"
{(yyval.nd_obj).nd=faire_noeud((yyvsp[-1].nd_obj).nd,(yyvsp[0].nd_obj).nd,"instructions");
if((yyvsp[-1].nd_obj).nd_dot){
(yyvsp[-1].nd_obj).nd_dot->right_sibling=(yyvsp[0].nd_obj).nd_dot;
(yyval.nd_obj).nd_dot=(yyvsp[-1].nd_obj).nd_dot;}
else (yyval.nd_obj).nd_dot=(yyvsp[0].nd_obj).nd_dot;

}
#line 1736 "y.tab.c"
    break;

  case 26:
#line 199 "parser.y"
                      {(yyval.nd_obj).nd_dot=(yyvsp[0].nd_obj).nd_dot;}
#line 1742 "y.tab.c"
    break;

  case 29:
#line 203 "parser.y"
      { ajouter('K'); is_for = 1; }
#line 1748 "y.tab.c"
    break;

  case 30:
#line 203 "parser.y"
                                                                                                     { 
	struct noeud *temp = faire_noeud((yyvsp[-4].nd_obj3).nd, (yyvsp[-2].nd_obj).nd, "CONDITION"); 
	struct noeud *temp2 = faire_noeud((yyvsp[-6].nd_obj).nd, temp, "CONDITION"); 
	(yyval.nd_obj).nd = faire_noeud(temp2, (yyvsp[0].nd_obj).nd, (yyvsp[-9].nd_obj).nom); 
	strcpy(code3v[_3var_index++], buff_3var);
	sprintf(code3v[_3var_index++], "JUMP to %s\n", (yyvsp[-4].nd_obj3).if_corps);
	sprintf(code3v[_3var_index++], "\nLABEL %s:\n", (yyvsp[-4].nd_obj3).else_corps);
	(yyval.nd_obj).nd_dot=faire_noeud_lcrs((yyvsp[-6].nd_obj).nd_dot,NULL,"label=for");
	(yyvsp[-6].nd_obj).nd_dot->right_sibling=(yyvsp[-4].nd_obj3).nd_dot;
	(yyvsp[-4].nd_obj3).nd_dot->right_sibling=(yyvsp[-2].nd_obj).nd_dot;
	(yyvsp[-2].nd_obj).nd_dot->right_sibling=(yyvsp[0].nd_obj).nd_dot;
}
#line 1765 "y.tab.c"
    break;

  case 31:
#line 216 "parser.y"
            {(yyval.nd_obj).nd=(yyvsp[0].nd_obj).nd;}
#line 1771 "y.tab.c"
    break;

  case 32:
#line 217 "parser.y"
                   { (yyval.nd_obj).nd = (yyvsp[-1].nd_obj).nd; (yyval.nd_obj).nd_dot=(yyvsp[-1].nd_obj).nd_dot;}
#line 1777 "y.tab.c"
    break;

  case 33:
#line 218 "parser.y"
        {(yyval.nd_obj).nd=(yyvsp[0].nd_obj).nd;
(yyval.nd_obj).nd_dot=(yyvsp[0].nd_obj).nd_dot;}
#line 1784 "y.tab.c"
    break;

  case 34:
#line 220 "parser.y"
             {(yyval.nd_obj).nd_dot=NULL;}
#line 1790 "y.tab.c"
    break;

  case 35:
#line 221 "parser.y"
         {(yyval.nd_obj).nd=(yyvsp[0].nd_obj).nd;(yyval.nd_obj).nd_dot=(yyvsp[0].nd_obj).nd_dot;}
#line 1796 "y.tab.c"
    break;

  case 36:
#line 222 "parser.y"
           {(yyval.nd_obj).nd=faire_noeud(NULL,NULL,"break");(yyval.nd_obj).nd_dot=faire_noeud_lcrs(NULL,NULL,"label=break");}
#line 1802 "y.tab.c"
    break;

  case 38:
#line 228 "parser.y"
                 { verefier_declaration((yyvsp[0].nd_obj).nom); }
#line 1808 "y.tab.c"
    break;

  case 39:
#line 228 "parser.y"
                                                                  {
	(yyvsp[-3].nd_obj).nd = faire_noeud(NULL, NULL, (yyvsp[-3].nd_obj).nom); 
	(yyval.nd_obj).nd = faire_noeud((yyvsp[-3].nd_obj).nd, (yyvsp[0].nd_obj2).nd, ":="); 
	sprintf(code3v[_3var_index++], "%s = %s\n", (yyvsp[-3].nd_obj).nom, (yyvsp[0].nd_obj2).nom);
	sprintf(strTmp,"label=%s",(yyvsp[-3].nd_obj).nom);
	(yyval.nd_obj).nd_dot=faire_noeud_lcrs(faire_noeud_lcrs(NULL,(yyvsp[0].nd_obj2).nd_dot,strTmp),NULL,"label=\":=\"");
}
#line 1820 "y.tab.c"
    break;

  case 40:
#line 235 "parser.y"
                 { verefier_declaration((yyvsp[0].nd_obj).nom); }
#line 1826 "y.tab.c"
    break;

  case 41:
#line 235 "parser.y"
                                                                          {
	 (yyvsp[-3].nd_obj).nd = faire_noeud(NULL, NULL, (yyvsp[-3].nd_obj).nom);
	  (yyval.nd_obj).nd = faire_noeud((yyvsp[-3].nd_obj).nd, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).nom); 
	  (yyval.nd_obj).nd_dot=faire_noeud_lcrs(NULL,NULL,"label=affectation2");}
#line 1835 "y.tab.c"
    break;

  case 42:
#line 239 "parser.y"
                 { verefier_declaration((yyvsp[0].nd_obj).nom); }
#line 1841 "y.tab.c"
    break;

  case 43:
#line 239 "parser.y"
                                                         { 
	(yyvsp[-2].nd_obj).nd = faire_noeud(NULL, NULL, (yyvsp[-2].nd_obj).nom); 
	(yyvsp[0].nd_obj).nd = faire_noeud(NULL, NULL, (yyvsp[0].nd_obj).nom); 
	(yyval.nd_obj).nd = faire_noeud((yyvsp[-2].nd_obj).nd, (yyvsp[0].nd_obj).nd, "ITERATOR");  
	if(!strcmp((yyvsp[0].nd_obj).nom, "++")) {
		sprintf(buff_3var, "t%d = %s + 1\n%s = t%d\n", temp_var, (yyvsp[-2].nd_obj).nom, (yyvsp[-2].nd_obj).nom, temp_var++);
	}
	else {
		sprintf(buff_3var, "t%d = %s + 1\n%s = t%d\n", temp_var, (yyvsp[-2].nd_obj).nom, (yyvsp[-2].nd_obj).nom, temp_var++);
	}
	(yyval.nd_obj).nd_dot=faire_noeud_lcrs(NULL,NULL,"label=affectation3");
}
#line 1858 "y.tab.c"
    break;

  case 44:
#line 251 "parser.y"
                       { 
	verefier_declaration((yyvsp[0].nd_obj).nom); 
	(yyvsp[-1].nd_obj).nd = faire_noeud(NULL, NULL, (yyvsp[-1].nd_obj).nom); 
	(yyvsp[0].nd_obj).nd = faire_noeud(NULL, NULL, (yyvsp[0].nd_obj).nom); 
	(yyval.nd_obj).nd = faire_noeud((yyvsp[-1].nd_obj).nd, (yyvsp[0].nd_obj).nd, "ITERATOR"); 
	if(!strcmp((yyvsp[-1].nd_obj).nom, "++")) {
		sprintf(buff_3var, "t%d = %s + 1\n%s = t%d\n", temp_var, (yyvsp[0].nd_obj).nom, (yyvsp[0].nd_obj).nom, temp_var++);
	}
	else {
		sprintf(buff_3var, "t%d = %s - 1\n%s = t%d\n", temp_var, (yyvsp[0].nd_obj).nom, (yyvsp[0].nd_obj).nom, temp_var++);

	}
	(yyval.nd_obj).nd_dot=faire_noeud_lcrs(NULL,NULL,"label=affectation4");
}
#line 1877 "y.tab.c"
    break;

  case 45:
#line 267 "parser.y"
                 { (yyval.nd_obj2).nd = (yyvsp[0].nd_obj2).nd; strcpy((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type); strcpy((yyval.nd_obj2).nom, (yyvsp[0].nd_obj2).nom); }
#line 1883 "y.tab.c"
    break;

  case 46:
#line 270 "parser.y"
                                   { ajouter('K'); is_for = 0; }
#line 1889 "y.tab.c"
    break;

  case 47:
#line 271 "parser.y"
{ sprintf(code3v[_3var_index++], "\nLABEL %s:\n", (yyvsp[-1].nd_obj3).if_corps); }
#line 1895 "y.tab.c"
    break;

  case 48:
#line 272 "parser.y"
        {struct noeud *iff = faire_noeud((yyvsp[-3].nd_obj3).nd, (yyvsp[0].nd_obj).nd, (yyvsp[-6].nd_obj).nom); 
	sprintf(code3v[_3var_index++], "GOTO next\n");
	(yyval.nd_obj).nd_dot=faire_noeud_lcrs((yyvsp[-3].nd_obj3).nd_dot,NULL,"label=if shape=diamond");
	(yyvsp[-3].nd_obj3).nd_dot->right_sibling=(yyvsp[0].nd_obj).nd_dot;	
	}
#line 1905 "y.tab.c"
    break;

  case 49:
#line 277 "parser.y"
            { ajouter('K'); is_for = 0; }
#line 1911 "y.tab.c"
    break;

  case 50:
#line 278 "parser.y"
{ sprintf(code3v[_3var_index++], "\nLABEL %s:\n", (yyvsp[-1].nd_obj3).if_corps); }
#line 1917 "y.tab.c"
    break;

  case 51:
#line 279 "parser.y"
{ sprintf(code3v[_3var_index++], "\nLABEL %s:\n", (yyvsp[-3].nd_obj3).else_corps); }
#line 1923 "y.tab.c"
    break;

  case 52:
#line 281 "parser.y"
        {struct noeud *iff = faire_noeud((yyvsp[-6].nd_obj3).nd, (yyvsp[-3].nd_obj).nd, (yyvsp[-9].nd_obj).nom); 
	(yyval.nd_obj).nd = faire_noeud(iff, (yyvsp[0].nd_obj).nd, "if-else"); 
	sprintf(code3v[_3var_index++], "GOTO next\n");
	(yyval.nd_obj).nd_dot=faire_noeud_lcrs((yyvsp[-6].nd_obj3).nd_dot,NULL,"label=if shape=diamond");
	(yyvsp[-6].nd_obj3).nd_dot->right_sibling=(yyvsp[-3].nd_obj).nd_dot;
	(yyvsp[-3].nd_obj).nd_dot->right_sibling=(yyvsp[0].nd_obj).nd_dot;
	}
#line 1935 "y.tab.c"
    break;

  case 56:
#line 297 "parser.y"
                {
			(yyvsp[-4].nd_obj).nd=faire_noeud((yyvsp[-2].nd_obj).nd,NULL,(yyvsp[-4].nd_obj).nom); (yyval.nd_obj).nd=(yyvsp[-4].nd_obj).nd;
			sprintf(strTmp,"label=%s shape=septagon",(yyvsp[-4].nd_obj).nom);
				(yyval.nd_obj).nd_dot=faire_noeud_lcrs((yyvsp[-2].nd_obj).nd_dot,NULL,strTmp);
		}
#line 1945 "y.tab.c"
    break;

  case 57:
#line 305 "parser.y"
                {(yyval.nd_obj2).nd=faire_noeud(NULL,NULL,(yyvsp[0].nd_obj).nom);
		sprintf(strTmp,"label=%s",(yyvsp[0].nd_obj).nom);
		(yyval.nd_obj2).nd_dot=faire_noeud_lcrs(NULL,NULL,strTmp);
		}
#line 1954 "y.tab.c"
    break;

  case 58:
#line 309 "parser.y"
                       {(yyval.nd_obj2).nd_dot= faire_noeud_lcrs((yyvsp[0].nd_obj).nd_dot,NULL,"label=TAB");}
#line 1960 "y.tab.c"
    break;

  case 59:
#line 312 "parser.y"
                                        {
		(yyvsp[-1].nd_obj2).nd_dot->description=concatener((yyvsp[-1].nd_obj2).nd_dot->description," style=dotted shape=triangle");
		get_last_sibling((yyvsp[-3].nd_obj).nd_dot)->right_sibling=(yyvsp[-1].nd_obj2).nd_dot;
		(yyval.nd_obj).nd_dot= (yyvsp[-3].nd_obj).nd_dot;
	}
#line 1970 "y.tab.c"
    break;

  case 60:
#line 318 "parser.y"
                {(yyval.nd_obj).nd=faire_noeud(NULL,NULL,(yyvsp[0].nd_obj).nom);
		sprintf(strTmp,"label=%s",(yyvsp[0].nd_obj).nom);
		(yyval.nd_obj).nd_dot=faire_noeud_lcrs(NULL,NULL,strTmp);
		}
#line 1979 "y.tab.c"
    break;

  case 61:
#line 325 "parser.y"
                                   {(yyval.nd_obj2).nd=(yyvsp[-1].nd_obj2).nd;(yyval.nd_obj2).nd_dot=(yyvsp[-1].nd_obj2).nd_dot;}
#line 1985 "y.tab.c"
    break;

  case 62:
#line 327 "parser.y"
        {
	(yyval.nd_obj2).nd=faire_noeud((yyvsp[-2].nd_obj2).nd,(yyvsp[0].nd_obj2).nd,(yyvsp[-1].nd_obj).nom);
	
	sprintf(strTmp,"label=\"%s\"",(yyvsp[-1].nd_obj).nom);
	(yyval.nd_obj2).nd_dot=faire_noeud_lcrs((yyvsp[-2].nd_obj2).nd_dot,NULL,strTmp);
	(yyvsp[-2].nd_obj2).nd_dot->right_sibling=(yyvsp[0].nd_obj2).nd_dot;
	}
#line 1997 "y.tab.c"
    break;

  case 63:
#line 334 "parser.y"
                                 {(yyval.nd_obj2).nd=(yyvsp[0].nd_obj2).nd;(yyval.nd_obj2).nd_dot=faire_noeud_lcrs((yyvsp[0].nd_obj2).nd_dot,NULL,"label=\"-\" ");}
#line 2003 "y.tab.c"
    break;

  case 64:
#line 335 "parser.y"
                          { ajouter('C'); }
#line 2009 "y.tab.c"
    break;

  case 65:
#line 336 "parser.y"
        {struct noeud* tmp=faire_noeud(NULL,NULL,(yyvsp[-1].nd_obj).nom);
	(yyval.nd_obj2).nd=tmp;
	sprintf(strTmp,"label=%s",(yyvsp[-1].nd_obj).nom) ;
	(yyval.nd_obj2).nd_dot=faire_noeud_lcrs(NULL,NULL,strTmp);}
#line 2018 "y.tab.c"
    break;

  case 66:
#line 340 "parser.y"
                         {(yyval.nd_obj2).nd=(yyvsp[0].nd_obj2).nd; (yyval.nd_obj2).nd_dot=(yyvsp[0].nd_obj2).nd_dot;}
#line 2024 "y.tab.c"
    break;

  case 68:
#line 344 "parser.y"
                                                          {(yyval.nd_obj).nd=faire_noeud((yyvsp[-2].nd_obj).nd,(yyvsp[0].nd_obj2).nd,"expressions");}
#line 2030 "y.tab.c"
    break;

  case 69:
#line 345 "parser.y"
                     {(yyval.nd_obj).nd=(yyvsp[0].nd_obj2).nd;}
#line 2036 "y.tab.c"
    break;

  case 78:
#line 361 "parser.y"
                                             { 
	(yyval.nd_obj3).nd = faire_noeud((yyvsp[-2].nd_obj2).nd, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).nom); 
	if(is_for) {
		sprintf((yyval.nd_obj3).if_corps, "L%d", label_count++);
		sprintf(code3v[_3var_index++], "\nLABEL %s:\n", (yyval.nd_obj3).if_corps);
		sprintf(code3v[_3var_index++], "\nif NOT (%s %s %s) GOTO L%d\n", (yyvsp[-2].nd_obj2).nom, (yyvsp[-1].nd_obj).nom, (yyvsp[0].nd_obj2).nom, label_count);
		sprintf((yyval.nd_obj3).else_corps, "L%d", label_count++);
	} else {
		sprintf(code3v[_3var_index++], "\nif (%s %s %s) GOTO L%d else GOTO L%d\n", (yyvsp[-2].nd_obj2).nom, (yyvsp[-1].nd_obj).nom, (yyvsp[0].nd_obj2).nom, label_count, label_count+1);
		sprintf((yyval.nd_obj3).if_corps, "L%d", label_count++);
		sprintf((yyval.nd_obj3).else_corps, "L%d", label_count++);
	}
	sprintf(strTmp,"label=\"%s\"",(yyvsp[-1].nd_obj).nom);
	(yyval.nd_obj3).nd_dot=faire_noeud_lcrs((yyvsp[-2].nd_obj2).nd_dot,NULL,strTmp);
	(yyvsp[-2].nd_obj2).nd_dot->right_sibling=(yyvsp[0].nd_obj2).nd_dot;
}
#line 2057 "y.tab.c"
    break;

  case 79:
#line 377 "parser.y"
                       {(yyval.nd_obj3).nd=faire_noeud((yyvsp[-3].nd_obj).nd,NULL,"not");(yyval.nd_obj3).nd_dot=faire_noeud_lcrs((yyvsp[-3].nd_obj).nd_dot,NULL,"label=not");}
#line 2063 "y.tab.c"
    break;

  case 80:
#line 378 "parser.y"
       { ajouter('K'); (yyval.nd_obj3).nd = NULL; }
#line 2069 "y.tab.c"
    break;

  case 81:
#line 379 "parser.y"
        { ajouter('K'); (yyval.nd_obj3).nd = NULL; }
#line 2075 "y.tab.c"
    break;

  case 82:
#line 380 "parser.y"
  { (yyval.nd_obj3).nd = NULL; }
#line 2081 "y.tab.c"
    break;

  case 83:
#line 384 "parser.y"
                                             { 
	strcpy((yyval.nd_obj2).type, (yyvsp[-2].nd_obj2).type);
	(yyval.nd_obj2).nd = faire_noeud((yyvsp[-2].nd_obj2).nd, (yyvsp[0].nd_obj2).nd, (yyvsp[-1].nd_obj).nom); 
	sprintf((yyval.nd_obj2).nom, "t%d", temp_var);
	temp_var++;
	sprintf(code3v[_3var_index++], "%s = %s %s %s\n",  (yyval.nd_obj2).nom, (yyvsp[-2].nd_obj2).nom, (yyvsp[-1].nd_obj).nom, (yyvsp[0].nd_obj2).nom);
	sprintf(strTmp,"label= \"%s\" ",(yyvsp[-1].nd_obj).nom);
	(yyvsp[-2].nd_obj2).nd_dot->right_sibling=(yyvsp[0].nd_obj2).nd_dot;
	(yyval.nd_obj2).nd_dot=faire_noeud_lcrs((yyvsp[-2].nd_obj2).nd_dot,NULL, strTmp); 
}
#line 2096 "y.tab.c"
    break;

  case 84:
#line 394 "parser.y"
         {
strcpy((yyval.nd_obj2).nom, (yyvsp[0].nd_obj2).nom);
strcpy((yyval.nd_obj2).type, (yyvsp[0].nd_obj2).type); 
(yyval.nd_obj2).nd = (yyvsp[0].nd_obj2).nd;
(yyval.nd_obj2).nd_dot=(yyvsp[0].nd_obj2).nd_dot;
}
#line 2107 "y.tab.c"
    break;

  case 95:
#line 417 "parser.y"
{ 
strcpy((yyval.nd_obj2).nom, (yyvsp[0].nd_obj).nom);
 strcpy((yyval.nd_obj2).type, "int");
 ajouter('C'); 
 (yyval.nd_obj2).nd = faire_noeud(NULL, NULL, (yyvsp[0].nd_obj).nom); 
 sprintf(strTmp,"label=%s",(yyvsp[0].nd_obj).nom);
 (yyval.nd_obj2).nd_dot=faire_noeud_lcrs(NULL,NULL,strTmp);
 }
#line 2120 "y.tab.c"
    break;

  case 96:
#line 425 "parser.y"
                 { strcpy((yyval.nd_obj2).nom, (yyvsp[0].nd_obj).nom); char *id_type = retrurner_type((yyvsp[0].nd_obj).nom); strcpy((yyval.nd_obj2).type, id_type); verefier_declaration((yyvsp[0].nd_obj).nom); (yyval.nd_obj2).nd = faire_noeud(NULL, NULL, (yyvsp[0].nd_obj).nom); }
#line 2126 "y.tab.c"
    break;

  case 97:
#line 429 "parser.y"
{ verefier_type_de_return((yyvsp[-1].nd_obj2).nom);
 (yyvsp[-2].nd_obj).nd = faire_noeud(NULL, NULL, "return");
(yyval.nd_obj).nd = faire_noeud((yyvsp[-2].nd_obj).nd, (yyvsp[-1].nd_obj2).nd, "RETURN"); 
(yyval.nd_obj).nd_dot=faire_noeud_lcrs((yyvsp[-1].nd_obj2).nd_dot,NULL,"label=RETURN shape=trapezium color=blue");
}
#line 2136 "y.tab.c"
    break;

  case 98:
#line 434 "parser.y"
            {
(yyval.nd_obj).nd = faire_noeud(NULL, NULL, "return");
(yyval.nd_obj).nd_dot=faire_noeud_lcrs(NULL,NULL,"label=RETURN shape=trapezium color=blue");
}
#line 2145 "y.tab.c"
    break;


#line 2149 "y.tab.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 441 "parser.y"


int main() {
	system("mkdir -p result");
	//system("rm -r lex.yy.c y.tab.c y.tab.h y.output");
    yyparse();
    printf("\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 1: LEXICAL ANALYSIS \n\n");
	printf("\nSYMBOL   DATATYPE   TYPE   LINE NUMBER \n");
	printf("_______________________________________\n\n");
	int i=0;
	for(i=0; i<compter_symbole; i++) {
		printf("%s\t%s\t%s\t%d\t\n", table_de_symbols[i].nom_id, table_de_symbols[i].type_data, table_de_symbols[i].type, table_de_symbols[i].ligne_nombre);
	}
	for(i=0;i<compter_symbole;i++) {
		free(table_de_symbols[i].nom_id);
		free(table_de_symbols[i].type);
	}
	printf("\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 2: l'ANALYSE SYNTAXIQUE \n\n");
	afficher_arbre(head); 
	
	FILE *fp;
	fp = fopen("result/ArbreSyntaxique.dot", "w"); // create or open the file for writing
	afficher_arbre_to_file(fp,head); 
    fclose(fp); // close the file

	printf("\n\n\n\n");

	FILE *fp_dot;
	fp_dot = fopen("result/output.dot", "w"); // create or open the file for writing
	afficher_arbre_dot_lcrs(fp_dot,head_dot); 
    fclose(fp_dot); // close the file
	printf("\n\n\n\n");

	printf("\t\t\t\t\t\t\t\t PHASE 3: L'ANALYSE SEMANTIQUE\n\n");
	if(sem_errors>0) {
		printf("L'analyse symantique est terminé avec  %d erreurs\n", sem_errors);
		for(int i=0; i<sem_errors; i++){
			printf("\t - %s", errors[i]);
		}
	} else {
		printf("L'analyse symantique est terminé avec  no erreurs");
	}
	printf("\n\n");
	printf("\t\t\t\t\t\t\t   PHASE 4: GENERATION DU CODE 3 variable\n\n");
	FILE *f3;
	f3 = fopen("result/3var.txt", "w"); // create or open the file for writing

	for(int i=0; i<_3var_index; i++){
		fprintf(f3,"%s", code3v[i]);
	}
	fclose(fp); // close the file
	printf("\n\n");
	system("dot -Tpdf result/ArbreSyntaxique.dot -o result/ArbreSyntaxique.pdf");
	system("dot -Tpdf result/output.dot -o result/output.pdf");
}

int chercher(char *type) {
	int i;
	for(i=compter_symbole-1; i>=0; i--) {
		if(strcmp(table_de_symbols[i].nom_id, type)==0) {
			return -1;
		}
	}
	return 0;
}

void verefier_declaration(char *c) {
    requete = chercher(c);
    if(!requete) {
        sprintf(errors[sem_errors], "Ligne %d: La Variable \"%s\" n'est pas declaré avant l'utilisation!\n", yylineno+1, c);
		sem_errors++;
    }
}

void verefier_type_de_return(char *valeur) {
	char *main_datatype = retrurner_type(main_function);
	char *return_datatype = retrurner_type(valeur);
	if((!strcmp(main_datatype, "int") && !strcmp(return_datatype, "CONST")) || !strcmp(main_datatype, return_datatype)){
		return ;
	}
	else {
		sprintf(errors[sem_errors], "Ligne %d: Le type de return est incorrect\n", yylineno+1);
		sem_errors++;
	}
}

char *retrurner_type(char *var){
	for(int i=0; i<compter_symbole; i++) {
		// Handle case of use before declaration
		if(!strcmp(table_de_symbols[i].nom_id, var)) {
			return table_de_symbols[i].type_data;
		}
	}
}

void ajouter(char c) {
	if(c == 'V'){
		for(int i=0; i<10; i++){
			if(!strcmp(reserves[i], strdup(yytext))){
        		sprintf(errors[sem_errors], "Line %d: Variable nom \"%s\" est un mot clé reservé!\n", yylineno+1, yytext);
				sem_errors++;
				return;
			}
		}
	}
    requete=chercher(yytext);
	if(!requete) {
		if(c == 'K') {
			table_de_symbols[compter_symbole].nom_id=strdup(yytext);
			table_de_symbols[compter_symbole].type_data=strdup("N/A");
			table_de_symbols[compter_symbole].ligne_nombre=yylineno;
			table_de_symbols[compter_symbole].type=strdup("Keyword\t");
			compter_symbole++;
		}
		else if(c == 'V') {
			table_de_symbols[compter_symbole].nom_id=strdup(yytext);
			table_de_symbols[compter_symbole].type_data=strdup(type);
			table_de_symbols[compter_symbole].ligne_nombre=yylineno;
			table_de_symbols[compter_symbole].type=strdup("Variable");
			compter_symbole++;
		}
		else if(c == 'C') {
			table_de_symbols[compter_symbole].nom_id=strdup(yytext);
			table_de_symbols[compter_symbole].type_data=strdup("CONST");
			table_de_symbols[compter_symbole].ligne_nombre=yylineno;
			table_de_symbols[compter_symbole].type=strdup("Constant");
			compter_symbole++;
		}
		else if(c == 'F') {
			table_de_symbols[compter_symbole].nom_id=strdup(yytext);
			table_de_symbols[compter_symbole].type_data=strdup(type);
			table_de_symbols[compter_symbole].ligne_nombre=yylineno;
			table_de_symbols[compter_symbole].type=strdup("Function");
			compter_symbole++;
		}
    }
    else if(c == 'V' && requete) {
        sprintf(errors[sem_errors], "Line %d: Plusiers declaration de  \"%s\" n'est pas autorisé!\n", yylineno+1, yytext);
		sem_errors++;
    }
}

struct noeud* faire_noeud(struct noeud *gauche, struct noeud *droite, char *lexeme) {	
	struct noeud *newnode = (struct noeud *)malloc(sizeof(struct noeud));
	char *newstr = (char *)malloc(strlen(lexeme)+1);
	strcpy(newstr, lexeme);
	newnode->gauche = gauche;
	newnode->droite = droite;
	newnode->lexeme = newstr;
	return(newnode);
}
struct noeud_lcrs* faire_noeud_lcrs(struct noeud_lcrs *left_child, struct noeud_lcrs *right_sibling,char* description){
	struct noeud_lcrs *newnode = (struct noeud_lcrs *)malloc(sizeof(struct noeud_lcrs));
	char *newdescription = (char *)malloc(strlen(description)+1);
	strcpy(newdescription, description);
	newnode->left_child = left_child;
	newnode->right_sibling = right_sibling;
	newnode->description =newdescription;
	return(newnode);
}

void ajouter_dernier_fils(struct noeud_lcrs* pere,struct noeud_lcrs* fils){
	if(pere->left_child==NULL)pere->left_child=fils;
	else{
		struct noeud_lcrs* child=pere->left_child;
		while(child->right_sibling)child=child->right_sibling;
		child->right_sibling=fils;
	}
	}
void afficher_arbre(struct noeud* tree) {
	printf("\n\nLe parcour INFIXE DE l'arbre syntaxique est : \n\n");
	afficher_dans_lorder(tree);
}
void afficher_arbre_to_file(FILE* f,struct noeud* tree) {
	fprintf(f,"digraph mon_programme {\n");
	int j=1;
	affichage_prifixe_de_larbre_syntaxique(f,tree,&j);
	j=1;
	afficher_les_dependances_dot(f,tree,&j);
	fprintf(f,"\n}");

}
void afficher_arbre_dot_lcrs(FILE* f,struct noeud_lcrs* tree) {
	fprintf(f,"digraph mon_programme {\n");
	int j=1;
	affichage_prifixe_de_larbre_syntaxique_dot_lcrs(f,tree,&j);
	j=1;
	afficher_les_dependances_dot_lcrs(f,tree);
	fprintf(f,"\n}");

}
void afficher_dans_lorder(struct noeud *tree) {
	int i;
	if (tree->gauche) {
		afficher_dans_lorder(tree->gauche);
	}
	printf("%s, ", tree->lexeme);
	if (tree->droite) {
		afficher_dans_lorder(tree->droite);
	}
}
void affichage_prifixe_de_larbre_syntaxique(FILE* f,struct noeud *tree,int* j) {
	fprintf(f,"\nnode%d [label=\"%s\" shape=ellipse ];",*j, tree->lexeme);
	*j=*j+1;
	if (tree->gauche) {
		affichage_prifixe_de_larbre_syntaxique(f,tree->gauche,j);
	}
	if (tree->droite) {
		affichage_prifixe_de_larbre_syntaxique(f,tree->droite,j);
	}



}
void affichage_prifixe_de_larbre_syntaxique_dot_lcrs(FILE* f,struct noeud_lcrs *tree,int* j) {
	fprintf(f,"\nnode%d [%s]",*j, tree->description);
	tree->inode=*j;
	*j=*j+1;
	if (tree->left_child) {
		affichage_prifixe_de_larbre_syntaxique_dot_lcrs(f,tree->left_child,j);
}
	if (tree->right_sibling) {
		affichage_prifixe_de_larbre_syntaxique_dot_lcrs(f,tree->right_sibling,j);
}


}
void afficher_les_dependances_dot(FILE* f,struct noeud *tree,int* j) {
	int p=*j;
	*j=*(j)+1;
	int g=*j;
	if (tree->gauche) {
		afficher_les_dependances_dot(f,tree->gauche,j);
	}
	int d=*j;
	if (tree->droite) {
		afficher_les_dependances_dot(f,tree->droite,j);
	}
		if (tree->gauche) fprintf(f,"\nnode%d->node%d;",p,g);
		if (tree->droite) fprintf(f,"\nnode%d->node%d;",p,d);
		}

void afficher_les_dependances_dot_lcrs(FILE* f,struct noeud_lcrs *tree) {
		if (tree->left_child){
			struct noeud_lcrs* current_chilid=tree->left_child;
			while(current_chilid){
				fprintf(f,"\nnode%d->node%d;",tree->inode,current_chilid->inode);
				afficher_les_dependances_dot_lcrs(f,current_chilid);
				current_chilid=current_chilid->right_sibling;
			}
			}
		}

void inserer_type() {
	strcpy(type, yytext);
}

char* concatener(char*a,char*b){
		char*cat=(char*)malloc(sizeof(char)*(1+strlen(a)+strlen(b)));
		strcat(cat,a);
		strcat(cat,b);
		return cat;
	}
	
struct noeud_lcrs* get_last_sibling(struct noeud_lcrs* tree){
	if(tree->right_sibling)return get_last_sibling(tree->right_sibling);
	return tree;
}

void yyerror(const char *msg) {
    fprintf(stderr, "Erreur de Syntax: %s\n", msg);
    fprintf(stderr, "Le dernier lexème lue est '%s'\n", yytext);
    fprintf(stderr, "L'erreur est apparue dans la ligne %d, column \n", yylineno+1 );
}
