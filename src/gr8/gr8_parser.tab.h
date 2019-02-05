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
extern YYSTYPE yylval;
