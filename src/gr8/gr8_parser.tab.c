/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "gr8_parser.y"
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE               compiler->scanner()->lineno()
#define yylex()            compiler->scanner()->scan()
#define yyerror(s)         compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/
#line 13 "gr8_parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int                   i;	/* integer value */
  double                r;      /* double value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::string_node     *string;
  cdk::integer_node    *integerNode;
  cdk::double_node     *doubleNode;
  cdk::lvalue_node     *lvalue;
  cdk::typed_node      *typedNode;
  gr8::block_node      *block;
  basic_type           *type;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 63 "gr8_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 56 "gr8_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tINT 257
#define tDOUBLE 258
#define tIDENTIFIER 259
#define tSTRING 260
#define tFAKE 261
#define tINITIALLY 262
#define tUSE 263
#define tPUBLIC 264
#define tPROCEDURE 265
#define tFUNCTION 266
#define tDEFINE 267
#define tON 268
#define tAS 269
#define tDO 270
#define tUSES 271
#define tFOR 272
#define tRETURN 273
#define tAND 274
#define tOR 275
#define tEQUALS 276
#define tASSIGN 277
#define tTO 278
#define tCELL 279
#define tAT 280
#define tINPUT 281
#define tPRINT 282
#define tPRINTLN 283
#define tOBJECTS 284
#define tTHEN 285
#define tELSIF 286
#define tELSE 287
#define tSTOP 288
#define tAGAIN 289
#define tSWEEPING 290
#define tFROM 291
#define tBY 292
#define tNULL 293
#define tIF 294
#define tTYPEINT 295
#define tTYPEDOUBLE 296
#define tTYPESTRING 297
#define tUNARY 298
#define tINDEXING 299
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   11,   11,   30,   30,   29,   29,   14,   14,
   28,   28,   28,   28,   28,   28,   28,   28,   27,   27,
   27,   27,   27,   27,   27,   27,   27,   27,   27,   27,
    9,    9,   26,   10,   10,   25,   25,   24,   24,   24,
   24,   24,   23,   23,   23,   23,   23,   23,   22,   22,
   21,   21,   20,   20,   19,   19,   19,   19,   12,   12,
   12,    8,    8,    6,    6,    6,    6,    6,    6,    5,
    5,    5,    5,    5,    5,    5,    2,    2,    4,    3,
    3,    3,    7,    7,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,   15,   15,   15,   13,   13,   13,
   13,   17,   18,   16,   16,
};
static const YYINT yylen[] = {                            2,
    0,    1,    1,    2,    1,    2,    2,    1,    4,    2,
    6,    5,    8,    7,    7,    6,    9,    8,    3,    2,
    5,    4,    4,    3,    6,    5,    4,    3,    6,    5,
    1,    3,    2,    2,    3,    2,    6,    2,    6,    3,
    7,    3,    1,    2,    1,    2,    1,    2,    1,    2,
    1,    2,    1,    2,    2,    3,    3,    4,    1,    1,
    2,    1,    2,    2,    3,    2,    3,    2,    3,    2,
    3,    3,    5,    1,    1,    1,    8,   10,    2,    3,
    5,    5,    1,    3,    1,    1,    3,    2,    2,    2,
    3,    3,    3,    3,    3,    3,    3,    3,    2,    3,
    3,    1,    2,    1,    4,    6,    1,    1,    1,    1,
    1,    1,    1,    1,    2,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,   47,    0,    0,
    0,    0,    0,    0,    0,    0,    8,    5,    3,   50,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   54,
    0,   52,    4,   44,   46,   48,    0,    0,    6,    7,
    0,   42,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   31,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   33,    0,    0,    0,    0,    0,
   12,    0,    0,  112,  113,  114,  111,    0,    0,  108,
  109,    0,    0,    0,    0,   32,    0,   16,    0,    0,
    0,  107,    0,    0,    0,    0,    0,  104,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   55,    0,
   75,   74,   62,   60,    0,    0,    0,   85,   86,    0,
   76,    0,    0,    0,   11,   39,  115,   41,    0,    0,
   15,   14,    0,    0,   10,   68,    0,    0,    0,    0,
    0,   66,    0,   64,    0,    0,    0,   79,    0,   88,
   89,    0,    0,    0,    0,   90,    0,    0,    0,    0,
    0,    0,    0,   70,   63,   61,   56,    0,    0,   57,
  103,    0,   34,    0,   18,    0,    0,    0,   69,    0,
    0,   71,   72,   67,   65,    0,    0,   87,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   58,   35,
    0,   13,   17,    9,    0,    0,    0,  105,    0,    0,
    0,   73,    0,    0,    0,    0,    0,  106,    0,   82,
   81,   37,    0,    0,   77,    0,    0,   78,
};
static const YYINT yydgoto[] = {                          9,
  120,  121,  158,  122,  123,  124,  144,  125,   59,  126,
   10,  127,  128,  129,  130,   89,   90,   91,  131,   11,
   12,   13,   60,   15,  133,   61,   16,   17,   18,   19,
};
static const YYINT yysindex[] = {                      -158,
 -243, -146, -140, -235, -185, -268, -250,    0,    0, -158,
 -209, -207, -239, -195,   13,   18,    0,    0,    0,    0,
 -173, -192, -166, -177, -183, -100, -164, -150, -268,    0,
 -250,    0,    0,    0,    0,    0,   68, -139,    0,    0,
 -144,    0, -129, -131,  102, -113, -114, -111, -112, -171,
 -101, -103, -109, -114, -107, -114,  -96, -102,  129,  -88,
    0, -167,  -82, -114,   56, -155,   19, -114,  129, -114,
  129,   19, -114, -114,    0, -114,   56, -133,  -35,  -33,
    0, -114,   56,    0,    0,    0,    0,  144,  -73,    0,
    0,  129,  129,  152,  129,    0,  -31,    0, -114,   56,
   56,    0,  135,  -61,  127,  135,  135,    0,  135,  135,
  -55,  -54, -253,  135,  135,  135,  135,  135,    0,  665,
    0,    0,    0,    0,   89,    8,   74,    0,    0,  137,
    0,  -58,  145,  -30,    0,    0,    0,    0,   56,  -24,
    0,    0,  951,  -43,    0,    0,  689,  626,  734,  821,
  847,    0,  146,    0,  149,  -80,  585,    0,   23,    0,
    0,  871,  135,  135,  135,    0,  135,  135,  135,  135,
  135,  135,  135,    0,    0,    0,    0,   88,  160,    0,
    0,  182,    0,   56,    0,   56,  -17,  135,    0, -253,
  -38,    0,    0,    0,    0,  135,   56,    0,   23,  523,
  -26,  -14,  -14,  -12,  -12,  -37,  -37,  -37,    0,    0,
  -39,    0,    0,    0,  951,  184,  135,    0,  882, -142,
  135,    0,  909,  135,  135,   56,  925,    0,   81,    0,
    0,    0,   56,  135,    0,  937,   56,    0,
};
static const YYINT yyrindex[] = {                       251,
  -45,    0,    0,    0,    0, -216, -204,    0,    0,  253,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  195,    0,    0,    0,   -2,    0,
   12,    0,    0,    0,    0,    0,  215,    0,    0,    0,
  216,    0,    0,  221,   18,    0,    0,    0,    0,    0,
    0,    0,  223,    0,  224,    0,    0,  225,  227,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  229,    0,
  233,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  147,    0,
    0,  234,  235,    0,  236,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  175,    0,    0,    0,    0,  173,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -41,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  545,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  247,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  561,  570,
  400,  374,  536,  490,  513,  419,  443,  467,    0,    0,
    0,    0,    0,    0,  -36,    0,    0,    0,    0,   51,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  916,    0,   90,    0,  188,  191,    0,    0,    5,    0,
    0,  192,  -23,    0,  -91,    0,   41,    0,  820,    9,
   25,  316,   37,    0,  193,  246,    0,    0,    0,  312,
};
#define YYTABLESIZE 1235
static const YYINT yytable[] = {                        115,
  188,  217,   83,  152,  154,  102,  118,   84,   74,  116,
  173,  117,   74,   74,   30,  171,  169,    1,  170,   74,
  172,  156,  173,   25,  173,  107,   29,  171,  169,  171,
  170,   32,  172,  167,  172,  168,   14,   30,   22,   24,
  115,   28,   43,   88,   53,   31,   14,  118,   94,   43,
  116,   34,  117,   35,   45,   32,   51,   36,   69,  173,
   71,   45,   49,   37,  171,  169,   42,  170,   79,  172,
   38,   39,   92,   43,   93,    1,   40,   95,   26,   27,
   97,   45,  167,   80,  168,   41,  134,   47,   46,   80,
   80,  119,   44,   80,   50,   80,   64,   65,  216,  218,
   76,   77,    1,  140,    2,    3,    4,   52,    5,    6,
    7,    8,   82,   83,    1,   51,  132,  173,   21,   53,
    1,  115,  171,  169,   23,  170,   54,  172,  118,   55,
   80,  116,  177,  117,   99,  100,    6,    7,    8,   56,
  167,   57,  168,  225,  226,   58,    1,   62,    6,    7,
    8,  153,  155,   63,    6,    7,    8,   66,   67,  115,
    1,   68,  132,   70,   48,   72,  118,  115,   73,  116,
   75,  117,   74,   80,  118,   80,   78,  116,   80,  117,
    6,    7,    8,  110,  136,  146,  137,  110,  110,  110,
  110,  110,  138,  110,    6,    7,    8,  145,  180,  181,
  182,   84,   84,  183,  194,  110,  110,  195,  110,  102,
  196,   80,  209,  102,  102,  102,  102,  102,  210,  102,
  102,  211,  221,   84,   85,  102,   86,    1,  187,  103,
   83,  102,  102,  101,  102,   84,  104,  139,  184,  105,
  107,  214,  222,  106,  186,  107,  166,  108,  109,  110,
    1,   49,    2,   20,  111,  112,  113,  166,   53,   87,
  114,    6,    7,    8,   84,   85,  102,   86,    1,  166,
  103,  166,   51,   38,   28,   84,   85,  104,   86,   24,
  105,   19,   27,   23,  106,   22,  107,   30,  108,  109,
  110,   26,   21,   29,   25,  111,  112,  113,  165,   59,
   87,  114,    6,    7,    8,   36,  166,   80,   80,   80,
   80,   87,  175,   80,  230,  176,   20,  178,  179,   96,
   80,   33,    0,   80,    0,    0,    0,   80,    0,   80,
    0,   80,   80,   80,    0,    0,    0,    0,   80,   80,
   80,    0,    0,   80,   80,   84,   85,  102,   86,    0,
  233,  103,    0,    0,  163,  164,  165,    0,  104,    0,
    0,  105,    0,    0,  166,  106,    0,  107,    0,  108,
  109,  110,  234,    0,    0,    0,  111,  112,  113,    0,
    0,   87,  114,   84,   85,  102,   86,    0,    0,  103,
    0,   84,   85,  102,   86,    0,  104,  103,    0,    0,
    0,    0,    0,    0,  104,  107,    0,  108,    0,    0,
    0,    0,    0,  107,   96,  108,  110,   96,  110,   87,
  110,  110,  110,    0,  110,    0,  110,   87,    0,    0,
  110,  110,   96,   96,    0,   96,    0,    0,  110,    0,
   98,    0,  102,   98,  102,    0,  102,  102,  102,    0,
  102,    0,  102,    0,    0,   93,  102,  102,   98,   93,
   93,   93,   93,   93,  102,   93,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   93,   93,   94,
   93,    0,    0,   94,   94,   94,   94,   94,    0,   94,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   94,   94,   95,   94,    0,    0,   95,   95,   95,
   95,   95,    0,   95,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   95,   95,    0,   95,    0,
   91,    0,   91,   91,   91,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   91,   91,
    0,   91,    0,   92,    0,   92,   92,   92,    0,  173,
    0,    0,    0,    0,  171,  169,    0,  170,    0,  172,
    0,   92,   92,    0,   92,    0,   97,    0,    0,   97,
    0,    0,  167,    0,  168,   99,    0,    0,   99,    0,
    0,    0,    0,    0,   97,   97,    0,   97,    0,    0,
    0,  100,    0,   99,  100,    0,    0,    0,    0,    0,
  101,    0,    0,  101,    0,    0,    0,    0,    0,  100,
    0,  173,    0,    0,    0,    0,  171,  169,  101,  170,
    0,  172,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   96,  167,   96,  168,   96,   96,   96,
    0,   96,    0,   96,    0,    0,    0,    0,   96,    0,
    0,    0,  173,    0,    0,   96,    0,  171,  169,   98,
  170,   98,  172,   98,   98,   98,    0,   98,    0,   98,
    0,    0,    0,    0,   98,  167,    0,  168,   93,    0,
   93,   98,   93,   93,   93,    0,   93,    0,   93,    0,
    0,  173,    0,   93,    0,    0,  171,  169,    0,  170,
   93,  172,   94,    0,   94,    0,   94,   94,   94,    0,
   94,    0,   94,  174,  167,  173,  168,   94,    0,    0,
  171,  169,    0,  170,   94,  172,   95,    0,   95,    0,
   95,   95,   95,    0,   95,    0,   95,  189,  167,    0,
  168,   95,    0,    0,    0,    0,    0,    0,   95,   91,
    0,   91,    0,   91,   91,   91,    0,   91,    0,   91,
  173,    0,    0,    0,   91,  171,  169,    0,  170,    0,
  172,   91,   92,    0,   92,    0,   92,   92,   92,    0,
   92,    0,   92,  167,    0,  168,  163,   92,  165,    0,
    0,    0,    0,    0,   92,   97,  166,   97,    0,   97,
   97,   97,    0,   97,   99,   97,   99,    0,   99,   99,
   97,    0,   99,    0,   99,    0,    0,   97,    0,   99,
  100,    0,  100,    0,  100,  100,   99,    0,  100,  101,
  100,  101,    0,    0,  101,  100,    0,  101,    0,  101,
    0,    0,  100,    0,  101,    0,    0,  173,  163,  164,
  165,  101,  171,  169,    0,  170,    0,  172,  166,  197,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  192,
  167,    0,  168,  173,   81,    0,    0,    0,  171,  169,
    0,  170,    0,  172,    0,    0,   98,    0,    0,  163,
  164,  165,  135,  190,    0,  193,  167,  173,  168,  166,
    0,  198,  171,  169,    0,  170,    0,  172,  173,  141,
  142,    0,    0,  171,  169,    0,  170,    0,  172,    0,
  167,    0,  168,    0,    0,    0,    0,    0,  163,  164,
  165,  167,    0,  168,    0,  173,    0,    0,  166,  228,
  171,  169,    0,  170,    0,  172,    0,    0,  185,    0,
    0,  173,  163,  164,  165,  232,  171,  169,  167,  170,
  168,  172,  166,  173,    0,    0,    0,    0,  171,  169,
    0,  170,    0,  172,  167,    0,  168,  173,    0,    0,
    0,    0,  171,  169,    0,  170,  167,  172,  168,    0,
    0,    0,    0,  212,    0,  213,    0,  163,  164,  165,
  167,    0,  168,  191,    0,    0,  220,  166,  143,    0,
  147,  148,  149,    0,  150,  151,    0,    0,    0,  157,
  159,  160,  161,  162,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  231,    0,    0,    0,    0,
    0,    0,  235,    0,    0,    0,  238,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  199,  200,
  201,    0,  202,  203,  204,  205,  206,  207,  208,    0,
    0,    0,    0,    0,  163,  164,  165,    0,    0,    0,
    0,    0,    0,  215,  166,    0,    0,    0,    0,    0,
    0,  219,    0,    0,    0,    0,    0,    0,    0,    0,
  163,  164,  165,    0,    0,    0,    0,    0,    0,    0,
  166,    0,  223,    0,    0,    0,  227,    0,    0,  229,
  157,    0,    0,    0,  163,  164,  165,    0,    0,  236,
    0,    0,    0,    0,  166,  163,  164,  165,    0,  224,
    0,    0,    0,    0,    0,  166,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  163,  164,  165,    0,    0,    0,    0,    0,
    0,    0,  166,    0,    0,    0,    0,    0,  163,  164,
  165,    0,    0,    0,    0,    0,  237,    0,  166,    0,
  163,  164,  165,    0,    0,    0,    0,    0,    0,    0,
  166,    0,    0,    0,  163,  164,  165,    0,    0,    0,
    0,    0,    0,    0,  166,
};
static const YYINT yycheck[] = {                         33,
   44,   40,   44,   59,   59,  259,   40,   44,   44,   43,
   37,   45,   44,   44,    6,   42,   43,  261,   45,   44,
   47,  113,   37,  259,   37,  279,  295,   42,   43,   42,
   45,    7,   47,   60,   47,   62,    0,   29,    2,    3,
   33,    5,  259,   67,  261,  296,   10,   40,   72,  266,
   43,  261,   45,  261,  259,   31,  261,  297,   54,   37,
   56,  266,   26,  259,   42,   43,  259,   45,   64,   47,
  266,   59,   68,  266,   70,  261,   59,   73,  264,  265,
   76,  259,   60,   33,   62,  259,   82,  271,  266,  123,
   40,  125,  259,   43,  259,   45,  268,  269,  190,  191,
  268,  269,  261,   99,  263,  264,  265,   40,  267,  295,
  296,  297,  268,  269,  261,  266,   80,   37,  265,  259,
  261,   33,   42,   43,  265,   45,  271,   47,   40,  259,
  123,   43,  125,   45,  268,  269,  295,  296,  297,  271,
   60,   40,   62,  286,  287,  259,  261,  259,  295,  296,
  297,  111,  112,  266,  295,  296,  297,  259,  262,   33,
  261,  271,  126,  271,  265,  262,   40,   33,  271,   43,
  259,   45,   44,  123,   40,  125,  259,   43,  123,   45,
  295,  296,  297,   37,   41,   59,  260,   41,   42,   43,
   44,   45,   41,   47,  295,  296,  297,  259,  125,   63,
  259,  257,  257,   59,   59,   59,   60,   59,   62,   37,
  291,  123,  125,   41,   42,   43,   44,   45,   59,   47,
  259,   40,  262,  257,  258,  259,  260,  261,  272,  263,
  272,   59,   60,  269,   62,  272,  270,  269,  269,  273,
  279,  259,   59,  277,  269,  279,  284,  281,  282,  283,
    0,  297,    0,   59,  288,  289,  290,  284,  261,  293,
  294,  295,  296,  297,  257,  258,  259,  260,  261,  284,
  263,  284,  261,   59,   59,  257,  258,  270,  260,   59,
  273,   59,   59,   59,  277,   59,  279,   59,  281,  282,
  283,   59,   59,   59,   59,  288,  289,  290,  276,  125,
  293,  294,  295,  296,  297,   59,  284,  257,  258,  259,
  260,  293,  125,  263,  225,  125,    1,  126,  126,   74,
  270,   10,   -1,  273,   -1,   -1,   -1,  277,   -1,  279,
   -1,  281,  282,  283,   -1,   -1,   -1,   -1,  288,  289,
  290,   -1,   -1,  293,  294,  257,  258,  259,  260,   -1,
  270,  263,   -1,   -1,  274,  275,  276,   -1,  270,   -1,
   -1,  273,   -1,   -1,  284,  277,   -1,  279,   -1,  281,
  282,  283,  292,   -1,   -1,   -1,  288,  289,  290,   -1,
   -1,  293,  294,  257,  258,  259,  260,   -1,   -1,  263,
   -1,  257,  258,  259,  260,   -1,  270,  263,   -1,   -1,
   -1,   -1,   -1,   -1,  270,  279,   -1,  281,   -1,   -1,
   -1,   -1,   -1,  279,   41,  281,  270,   44,  272,  293,
  274,  275,  276,   -1,  278,   -1,  280,  293,   -1,   -1,
  284,  285,   59,   60,   -1,   62,   -1,   -1,  292,   -1,
   41,   -1,  270,   44,  272,   -1,  274,  275,  276,   -1,
  278,   -1,  280,   -1,   -1,   37,  284,  285,   59,   41,
   42,   43,   44,   45,  292,   47,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,   60,   37,
   62,   -1,   -1,   41,   42,   43,   44,   45,   -1,   47,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   59,   60,   37,   62,   -1,   -1,   41,   42,   43,
   44,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   59,   60,   -1,   62,   -1,
   41,   -1,   43,   44,   45,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,   60,
   -1,   62,   -1,   41,   -1,   43,   44,   45,   -1,   37,
   -1,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,
   -1,   59,   60,   -1,   62,   -1,   41,   -1,   -1,   44,
   -1,   -1,   60,   -1,   62,   41,   -1,   -1,   44,   -1,
   -1,   -1,   -1,   -1,   59,   60,   -1,   62,   -1,   -1,
   -1,   41,   -1,   59,   44,   -1,   -1,   -1,   -1,   -1,
   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,   59,
   -1,   37,   -1,   -1,   -1,   -1,   42,   43,   59,   45,
   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  270,   60,  272,   62,  274,  275,  276,
   -1,  278,   -1,  280,   -1,   -1,   -1,   -1,  285,   -1,
   -1,   -1,   37,   -1,   -1,  292,   -1,   42,   43,  270,
   45,  272,   47,  274,  275,  276,   -1,  278,   -1,  280,
   -1,   -1,   -1,   -1,  285,   60,   -1,   62,  270,   -1,
  272,  292,  274,  275,  276,   -1,  278,   -1,  280,   -1,
   -1,   37,   -1,  285,   -1,   -1,   42,   43,   -1,   45,
  292,   47,  270,   -1,  272,   -1,  274,  275,  276,   -1,
  278,   -1,  280,   59,   60,   37,   62,  285,   -1,   -1,
   42,   43,   -1,   45,  292,   47,  270,   -1,  272,   -1,
  274,  275,  276,   -1,  278,   -1,  280,   59,   60,   -1,
   62,  285,   -1,   -1,   -1,   -1,   -1,   -1,  292,  270,
   -1,  272,   -1,  274,  275,  276,   -1,  278,   -1,  280,
   37,   -1,   -1,   -1,  285,   42,   43,   -1,   45,   -1,
   47,  292,  270,   -1,  272,   -1,  274,  275,  276,   -1,
  278,   -1,  280,   60,   -1,   62,  274,  285,  276,   -1,
   -1,   -1,   -1,   -1,  292,  270,  284,  272,   -1,  274,
  275,  276,   -1,  278,  270,  280,  272,   -1,  274,  275,
  285,   -1,  278,   -1,  280,   -1,   -1,  292,   -1,  285,
  270,   -1,  272,   -1,  274,  275,  292,   -1,  278,  270,
  280,  272,   -1,   -1,  275,  285,   -1,  278,   -1,  280,
   -1,   -1,  292,   -1,  285,   -1,   -1,   37,  274,  275,
  276,  292,   42,   43,   -1,   45,   -1,   47,  284,  285,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,
   60,   -1,   62,   37,   65,   -1,   -1,   -1,   42,   43,
   -1,   45,   -1,   47,   -1,   -1,   77,   -1,   -1,  274,
  275,  276,   83,  278,   -1,   59,   60,   37,   62,  284,
   -1,   41,   42,   43,   -1,   45,   -1,   47,   37,  100,
  101,   -1,   -1,   42,   43,   -1,   45,   -1,   47,   -1,
   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,  274,  275,
  276,   60,   -1,   62,   -1,   37,   -1,   -1,  284,   41,
   42,   43,   -1,   45,   -1,   47,   -1,   -1,  139,   -1,
   -1,   37,  274,  275,  276,   41,   42,   43,   60,   45,
   62,   47,  284,   37,   -1,   -1,   -1,   -1,   42,   43,
   -1,   45,   -1,   47,   60,   -1,   62,   37,   -1,   -1,
   -1,   -1,   42,   43,   -1,   45,   60,   47,   62,   -1,
   -1,   -1,   -1,  184,   -1,  186,   -1,  274,  275,  276,
   60,   -1,   62,  280,   -1,   -1,  197,  284,  103,   -1,
  105,  106,  107,   -1,  109,  110,   -1,   -1,   -1,  114,
  115,  116,  117,  118,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  226,   -1,   -1,   -1,   -1,
   -1,   -1,  233,   -1,   -1,   -1,  237,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  163,  164,
  165,   -1,  167,  168,  169,  170,  171,  172,  173,   -1,
   -1,   -1,   -1,   -1,  274,  275,  276,   -1,   -1,   -1,
   -1,   -1,   -1,  188,  284,   -1,   -1,   -1,   -1,   -1,
   -1,  196,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  274,  275,  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  284,   -1,  217,   -1,   -1,   -1,  221,   -1,   -1,  224,
  225,   -1,   -1,   -1,  274,  275,  276,   -1,   -1,  234,
   -1,   -1,   -1,   -1,  284,  274,  275,  276,   -1,  278,
   -1,   -1,   -1,   -1,   -1,  284,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  274,  275,  276,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  284,   -1,   -1,   -1,   -1,   -1,  274,  275,
  276,   -1,   -1,   -1,   -1,   -1,  270,   -1,  284,   -1,
  274,  275,  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  284,   -1,   -1,   -1,  274,  275,  276,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  284,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 299
#define YYUNDFTOKEN 332
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,
0,0,0,0,"';'","'<'",0,"'>'","'?'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,
"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,"tINT","tDOUBLE","tIDENTIFIER","tSTRING","tFAKE",
"tINITIALLY","tUSE","tPUBLIC","tPROCEDURE","tFUNCTION","tDEFINE","tON","tAS",
"tDO","tUSES","tFOR","tRETURN","tAND","tOR","tEQUALS","tASSIGN","tTO","tCELL",
"tAT","tINPUT","tPRINT","tPRINTLN","tOBJECTS","tTHEN","tELSIF","tELSE","tSTOP",
"tAGAIN","tSWEEPING","tFROM","tBY","tNULL","tIF","tTYPEINT","tTYPEDOUBLE",
"tTYPESTRING","tUNARY","tINDEXING",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : file",
"file :",
"file : decls",
"decls : decl",
"decls : decls decl",
"decl : func",
"decl : var ';'",
"func : funcDecl ';'",
"func : funcDef",
"funcCall : tUSE exprs tFOR tIDENTIFIER",
"funcCall : tDO tIDENTIFIER",
"funcDef : tDEFINE type tFUNCTION tIDENTIFIER tAS block",
"funcDef : tDEFINE tPROCEDURE tIDENTIFIER tAS block",
"funcDef : tDEFINE type tFUNCTION tIDENTIFIER tON params tAS block",
"funcDef : tDEFINE tPROCEDURE tIDENTIFIER tON params tAS block",
"funcDef : tDEFINE tPUBLIC type tFUNCTION tIDENTIFIER tAS block",
"funcDef : tDEFINE tPUBLIC tPROCEDURE tIDENTIFIER tAS block",
"funcDef : tDEFINE tPUBLIC type tFUNCTION tIDENTIFIER tON params tAS block",
"funcDef : tDEFINE tPUBLIC tPROCEDURE tIDENTIFIER tON params tAS block",
"funcDecl : type tFUNCTION tIDENTIFIER",
"funcDecl : tPROCEDURE tIDENTIFIER",
"funcDecl : type tFUNCTION tIDENTIFIER tUSES params",
"funcDecl : tPROCEDURE tIDENTIFIER tUSES params",
"funcDecl : tPUBLIC type tFUNCTION tIDENTIFIER",
"funcDecl : tPUBLIC tPROCEDURE tIDENTIFIER",
"funcDecl : tPUBLIC type tFUNCTION tIDENTIFIER tUSES params",
"funcDecl : tPUBLIC tPROCEDURE tIDENTIFIER tUSES params",
"funcDecl : tUSE type tFUNCTION tIDENTIFIER",
"funcDecl : tUSE tPROCEDURE tIDENTIFIER",
"funcDecl : tUSE type tFUNCTION tIDENTIFIER tUSES params",
"funcDecl : tUSE tPROCEDURE tIDENTIFIER tUSES params",
"params : param",
"params : params ',' param",
"param : type tIDENTIFIER",
"blockVars : blockVar ';'",
"blockVars : blockVars blockVar ';'",
"blockVar : type tIDENTIFIER",
"blockVar : type tIDENTIFIER '(' tINITIALLY expr ')'",
"var : type tIDENTIFIER",
"var : type tIDENTIFIER '(' tINITIALLY literal ')'",
"var : tPUBLIC type tIDENTIFIER",
"var : tPUBLIC type tIDENTIFIER '(' tINITIALLY literal ')'",
"var : tUSE type tIDENTIFIER",
"type : tTYPEINT",
"type : intPtr tFAKE",
"type : tTYPEDOUBLE",
"type : doublePtr tFAKE",
"type : tTYPESTRING",
"type : stringPtr tTYPESTRING",
"stringPtr : tFAKE",
"stringPtr : tFAKE stringPtr",
"doublePtr : tTYPEDOUBLE",
"doublePtr : tTYPEDOUBLE doublePtr",
"intPtr : tTYPEINT",
"intPtr : tTYPEINT intPtr",
"block : '{' '}'",
"block : '{' blockVars '}'",
"block : '{' blockInstrs '}'",
"block : '{' blockVars blockInstrs '}'",
"blockInstrs : instrs",
"blockInstrs : finalInstr",
"blockInstrs : instrs finalInstr",
"instrs : instr",
"instrs : instrs instr",
"finalInstr : tAGAIN ';'",
"finalInstr : tAGAIN integer ';'",
"finalInstr : tSTOP ';'",
"finalInstr : tSTOP integer ';'",
"finalInstr : tRETURN ';'",
"finalInstr : tRETURN expr ';'",
"instr : expr ';'",
"instr : tPRINT expr ';'",
"instr : tPRINTLN expr ';'",
"instr : tASSIGN expr tTO lval ';'",
"instr : instrCond",
"instr : sweeping",
"instr : block",
"sweeping : tSWEEPING lval tFROM expr tTO expr tDO block",
"sweeping : tSWEEPING lval tFROM expr tTO expr tBY expr tDO block",
"instrCond : tIF ifs",
"ifs : expr tTHEN block",
"ifs : expr tTHEN block tELSE block",
"ifs : expr tTHEN block tELSIF ifs",
"exprs : expr",
"exprs : exprs ',' expr",
"expr : literal",
"expr : funcCall",
"expr : '(' expr ')'",
"expr : '+' expr",
"expr : '-' expr",
"expr : expr tOBJECTS",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr tEQUALS expr",
"expr : '!' expr",
"expr : expr tAND expr",
"expr : expr tOR expr",
"expr : lval",
"expr : lval '?'",
"expr : tINPUT",
"lval : tCELL expr tAT lval",
"lval : tCELL expr tAT '(' expr ')'",
"lval : tIDENTIFIER",
"literal : integer",
"literal : double",
"literal : string",
"literal : tNULL",
"integer : tINT",
"double : tDOUBLE",
"string : tSTRING",
"string : string tSTRING",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 67 "gr8_parser.y"
	{ compiler->ast(new cdk::sequence_node(LINE));}
break;
case 2:
#line 68 "gr8_parser.y"
	{ compiler->ast(yystack.l_mark[0].sequence);}
break;
case 3:
#line 71 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].typedNode); }
break;
case 4:
#line 72 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].typedNode, yystack.l_mark[-1].sequence); }
break;
case 5:
#line 75 "gr8_parser.y"
	{yyval.typedNode = yystack.l_mark[0].typedNode;}
break;
case 6:
#line 76 "gr8_parser.y"
	{yyval.typedNode = yystack.l_mark[-1].typedNode;}
break;
case 7:
#line 79 "gr8_parser.y"
	{yyval.typedNode = yystack.l_mark[-1].typedNode;}
break;
case 8:
#line 80 "gr8_parser.y"
	{yyval.typedNode = yystack.l_mark[0].typedNode;}
break;
case 9:
#line 83 "gr8_parser.y"
	{yyval.expression = new gr8::function_call_node(LINE, yystack.l_mark[0].s, yystack.l_mark[-2].sequence);}
break;
case 10:
#line 84 "gr8_parser.y"
	{yyval.expression = new gr8::function_call_node(LINE, yystack.l_mark[0].s, new cdk::sequence_node(LINE));}
break;
case 11:
#line 87 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_define_node(LINE, false, false, yystack.l_mark[-4].type, yystack.l_mark[-2].s, new cdk::sequence_node(LINE), yystack.l_mark[0].block);}
break;
case 12:
#line 88 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_define_node(LINE, false, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-2].s, new cdk::sequence_node(LINE), yystack.l_mark[0].block);}
break;
case 13:
#line 89 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_define_node(LINE, false, false, yystack.l_mark[-6].type, yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, yystack.l_mark[0].block);}
break;
case 14:
#line 90 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_define_node(LINE, false, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, yystack.l_mark[0].block);}
break;
case 15:
#line 91 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_define_node(LINE, true, false, yystack.l_mark[-4].type, yystack.l_mark[-2].s, new cdk::sequence_node(LINE), yystack.l_mark[0].block);}
break;
case 16:
#line 92 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_define_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-2].s, new cdk::sequence_node(LINE), yystack.l_mark[0].block);}
break;
case 17:
#line 93 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_define_node(LINE, true, false, yystack.l_mark[-6].type, yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, yystack.l_mark[0].block);}
break;
case 18:
#line 94 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_define_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-4].s, yystack.l_mark[-2].sequence, yystack.l_mark[0].block);}
break;
case 19:
#line 97 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, false, false, yystack.l_mark[-2].type, yystack.l_mark[0].s, new cdk::sequence_node(LINE));}
break;
case 20:
#line 98 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, false, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[0].s, new cdk::sequence_node(LINE));}
break;
case 21:
#line 99 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, false, false, yystack.l_mark[-4].type, yystack.l_mark[-2].s, yystack.l_mark[0].sequence);}
break;
case 22:
#line 100 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, false, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-2].s, yystack.l_mark[0].sequence);}
break;
case 23:
#line 101 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, true, false, yystack.l_mark[-2].type, yystack.l_mark[0].s, new cdk::sequence_node(LINE));}
break;
case 24:
#line 102 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[0].s, new cdk::sequence_node(LINE));}
break;
case 25:
#line 103 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, true, false, yystack.l_mark[-4].type, yystack.l_mark[-2].s, yystack.l_mark[0].sequence);}
break;
case 26:
#line 104 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-2].s, yystack.l_mark[0].sequence);}
break;
case 27:
#line 105 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, true, false, yystack.l_mark[-2].type, yystack.l_mark[0].s, new cdk::sequence_node(LINE));}
break;
case 28:
#line 106 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[0].s, new cdk::sequence_node(LINE));}
break;
case 29:
#line 107 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, true, false, yystack.l_mark[-4].type, yystack.l_mark[-2].s, yystack.l_mark[0].sequence);}
break;
case 30:
#line 108 "gr8_parser.y"
	{ yyval.typedNode = new gr8::function_declaration_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), yystack.l_mark[-2].s, yystack.l_mark[0].sequence);}
break;
case 31:
#line 111 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].typedNode); }
break;
case 32:
#line 112 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].typedNode, yystack.l_mark[-2].sequence); }
break;
case 33:
#line 115 "gr8_parser.y"
	{ yyval.typedNode = new gr8::variable_declaration_node(LINE, false, false, yystack.l_mark[-1].type, yystack.l_mark[0].s, nullptr);}
break;
case 34:
#line 118 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].typedNode); }
break;
case 35:
#line 119 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[-1].typedNode, yystack.l_mark[-2].sequence); }
break;
case 36:
#line 122 "gr8_parser.y"
	{ yyval.typedNode = new gr8::variable_declaration_node(LINE, false, false, yystack.l_mark[-1].type, yystack.l_mark[0].s, nullptr);}
break;
case 37:
#line 123 "gr8_parser.y"
	{ yyval.typedNode = new gr8::variable_declaration_node(LINE, false, false, yystack.l_mark[-5].type, yystack.l_mark[-4].s, yystack.l_mark[-1].expression);}
break;
case 38:
#line 126 "gr8_parser.y"
	{ yyval.typedNode = new gr8::variable_declaration_node(LINE, false, false, yystack.l_mark[-1].type, yystack.l_mark[0].s, nullptr);}
break;
case 39:
#line 127 "gr8_parser.y"
	{ yyval.typedNode = new gr8::variable_declaration_node(LINE, false, false, yystack.l_mark[-5].type, yystack.l_mark[-4].s, yystack.l_mark[-1].expression);}
break;
case 40:
#line 128 "gr8_parser.y"
	{ yyval.typedNode = new gr8::variable_declaration_node(LINE, true, false, yystack.l_mark[-1].type, yystack.l_mark[0].s, nullptr);}
break;
case 41:
#line 129 "gr8_parser.y"
	{ yyval.typedNode = new gr8::variable_declaration_node(LINE, true, false, yystack.l_mark[-5].type, yystack.l_mark[-4].s, yystack.l_mark[-1].expression);}
break;
case 42:
#line 130 "gr8_parser.y"
	{ yyval.typedNode = new gr8::variable_declaration_node(LINE, false, true, yystack.l_mark[-1].type, yystack.l_mark[0].s, nullptr);}
break;
case 43:
#line 133 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_INT);}
break;
case 44:
#line 134 "gr8_parser.y"
	{ yyval.type = yystack.l_mark[-1].type;}
break;
case 45:
#line 135 "gr8_parser.y"
	{ yyval.type = new basic_type(8, basic_type::TYPE_DOUBLE);}
break;
case 46:
#line 136 "gr8_parser.y"
	{ yyval.type = yystack.l_mark[-1].type;}
break;
case 47:
#line 137 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_STRING);}
break;
case 48:
#line 138 "gr8_parser.y"
	{ yyval.type = yystack.l_mark[-1].type;}
break;
case 49:
#line 141 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER);
                                              yyval.type->_subtype = new basic_type(4, basic_type::TYPE_STRING);}
break;
case 50:
#line 143 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); yyval.type->_subtype = yystack.l_mark[0].type;}
break;
case 51:
#line 146 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER);
                                              yyval.type->_subtype = new basic_type(8, basic_type::TYPE_DOUBLE);}
break;
case 52:
#line 148 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); yyval.type->_subtype = yystack.l_mark[0].type;}
break;
case 53:
#line 151 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); 
                                              yyval.type->_subtype = new basic_type(4, basic_type::TYPE_INT);}
break;
case 54:
#line 153 "gr8_parser.y"
	{ yyval.type = new basic_type(4, basic_type::TYPE_POINTER); yyval.type->_subtype = yystack.l_mark[0].type;}
break;
case 55:
#line 156 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, new cdk::sequence_node(LINE), new cdk::sequence_node(LINE));}
break;
case 56:
#line 157 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, yystack.l_mark[-1].sequence, new cdk::sequence_node(LINE)); }
break;
case 57:
#line 158 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, new cdk::sequence_node(LINE), yystack.l_mark[-1].sequence); }
break;
case 58:
#line 159 "gr8_parser.y"
	{ yyval.block = new gr8::block_node(LINE, yystack.l_mark[-2].sequence, yystack.l_mark[-1].sequence); }
break;
case 59:
#line 162 "gr8_parser.y"
	{ yyval.sequence = yystack.l_mark[0].sequence; }
break;
case 60:
#line 163 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 61:
#line 164 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 62:
#line 167 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 63:
#line 168 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 64:
#line 171 "gr8_parser.y"
	{ yyval.node = new gr8::again_node(LINE, new cdk::integer_node(LINE, 1)); }
break;
case 65:
#line 172 "gr8_parser.y"
	{ yyval.node = new gr8::again_node(LINE, yystack.l_mark[-1].integerNode); }
break;
case 66:
#line 173 "gr8_parser.y"
	{ yyval.node = new gr8::stop_node(LINE, new cdk::integer_node(LINE,1)); }
break;
case 67:
#line 174 "gr8_parser.y"
	{ yyval.node = new gr8::stop_node(LINE, yystack.l_mark[-1].integerNode); }
break;
case 68:
#line 175 "gr8_parser.y"
	{ yyval.node = new gr8::return_node(LINE, nullptr); }
break;
case 69:
#line 176 "gr8_parser.y"
	{ yyval.node = new gr8::return_node(LINE, yystack.l_mark[-1].expression); }
break;
case 70:
#line 179 "gr8_parser.y"
	{ yyval.node = new gr8::evaluation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 71:
#line 180 "gr8_parser.y"
	{ yyval.node = new gr8::print_node(LINE, yystack.l_mark[-1].expression, false); }
break;
case 72:
#line 181 "gr8_parser.y"
	{ yyval.node = new gr8::print_node(LINE, yystack.l_mark[-1].expression, true); }
break;
case 73:
#line 182 "gr8_parser.y"
	{ yyval.node = new cdk::assignment_node(LINE, yystack.l_mark[-1].lvalue, yystack.l_mark[-3].expression); }
break;
case 74:
#line 183 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 75:
#line 184 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 76:
#line 185 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[0].block; }
break;
case 77:
#line 188 "gr8_parser.y"
	{ yyval.node = new gr8::sweeping_from_to_by_do_node(LINE, yystack.l_mark[-6].lvalue, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, new cdk::integer_node(LINE, 1), yystack.l_mark[0].block);}
break;
case 78:
#line 189 "gr8_parser.y"
	{ yyval.node = new gr8::sweeping_from_to_by_do_node(LINE, yystack.l_mark[-8].lvalue, yystack.l_mark[-6].expression, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].block);}
break;
case 79:
#line 192 "gr8_parser.y"
	{ yyval.node = yystack.l_mark[0].node; }
break;
case 80:
#line 195 "gr8_parser.y"
	{ yyval.node = new gr8::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].block); }
break;
case 81:
#line 196 "gr8_parser.y"
	{ yyval.node = new gr8::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].block, yystack.l_mark[0].block);}
break;
case 82:
#line 197 "gr8_parser.y"
	{ yyval.node = new gr8::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].block, yystack.l_mark[0].node);}
break;
case 83:
#line 200 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression); }
break;
case 84:
#line 201 "gr8_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].expression, yystack.l_mark[-2].sequence); }
break;
case 85:
#line 204 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 86:
#line 205 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[0].expression; }
break;
case 87:
#line 206 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 88:
#line 207 "gr8_parser.y"
	{ yyval.expression = new gr8::identity_node(LINE, yystack.l_mark[0].expression); }
break;
case 89:
#line 208 "gr8_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 90:
#line 209 "gr8_parser.y"
	{ yyval.expression = new gr8::memory_allocation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 91:
#line 210 "gr8_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 92:
#line 211 "gr8_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 93:
#line 212 "gr8_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 94:
#line 213 "gr8_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 95:
#line 214 "gr8_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 96:
#line 215 "gr8_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 97:
#line 216 "gr8_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 98:
#line 217 "gr8_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 99:
#line 218 "gr8_parser.y"
	{ yyval.expression = new cdk::not_node(LINE, yystack.l_mark[0].expression); }
break;
case 100:
#line 219 "gr8_parser.y"
	{ yyval.expression = new cdk::and_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 101:
#line 220 "gr8_parser.y"
	{ yyval.expression = new cdk::or_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 102:
#line 221 "gr8_parser.y"
	{ yyval.expression = new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 103:
#line 222 "gr8_parser.y"
	{ yyval.expression = new gr8::address_of_node(LINE, yystack.l_mark[-1].lvalue); }
break;
case 104:
#line 223 "gr8_parser.y"
	{ yyval.expression = new gr8::read_node(LINE); }
break;
case 105:
#line 226 "gr8_parser.y"
	{ yyval.lvalue = new gr8::index_node(LINE, new cdk::rvalue_node(LINE, yystack.l_mark[0].lvalue), yystack.l_mark[-2].expression); }
break;
case 106:
#line 227 "gr8_parser.y"
	{ yyval.lvalue = new gr8::index_node(LINE, yystack.l_mark[-1].expression, yystack.l_mark[-4].expression); }
break;
case 107:
#line 228 "gr8_parser.y"
	{ yyval.lvalue = new cdk::identifier_node(LINE, yystack.l_mark[0].s); delete yystack.l_mark[0].s; }
break;
case 108:
#line 231 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[0].integerNode; }
break;
case 109:
#line 232 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[0].doubleNode; }
break;
case 110:
#line 233 "gr8_parser.y"
	{ yyval.expression = yystack.l_mark[0].string; }
break;
case 111:
#line 234 "gr8_parser.y"
	{ yyval.expression = new gr8::null_node(LINE); }
break;
case 112:
#line 237 "gr8_parser.y"
	{ yyval.integerNode = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 113:
#line 240 "gr8_parser.y"
	{ yyval.doubleNode = new cdk::double_node(LINE, yystack.l_mark[0].r); }
break;
case 114:
#line 243 "gr8_parser.y"
	{ yyval.string = new cdk::string_node(LINE, yystack.l_mark[0].s); delete yystack.l_mark[0].s;}
break;
case 115:
#line 244 "gr8_parser.y"
	{ yyval.string = new cdk::string_node(LINE, std::string(yystack.l_mark[-1].string->value() + *yystack.l_mark[0].s)); delete yystack.l_mark[-1].string; delete yystack.l_mark[0].s;}
break;
#line 1346 "gr8_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
