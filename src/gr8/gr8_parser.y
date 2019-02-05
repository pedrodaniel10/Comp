%{
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE               compiler->scanner()->lineno()
#define yylex()            compiler->scanner()->scan()
#define yyerror(s)         compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
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
};

%token <i> tINT
%token <r> tDOUBLE
%token <s> tIDENTIFIER tSTRING
%token tFAKE tINITIALLY tUSE tPUBLIC tPROCEDURE tFUNCTION tDEFINE tON tAS
%token tDO tUSES tFOR tRETURN tAND
%token tOR tEQUALS tASSIGN tTO tCELL tAT tINPUT tPRINT tPRINTLN
%token tOBJECTS tTHEN tELSIF tELSE tSTOP tAGAIN tSWEEPING tFROM tBY tNULL
%token tIF tTYPEINT tTYPEDOUBLE tTYPESTRING

%nonassoc tIF 
%nonassoc tELSE tELSIF 
%left tOR
%left tAND
%nonassoc '!'
%left tEQUALS
%left '<' '>'
%left '+' '-'
%left '*' '/' '%'
%nonassoc '?' tUNARY tOBJECTS
%nonassoc tINDEXING

%type <expression> expr 
%type <node> sweeping ifs instrCond instr finalInstr
%type <sequence> exprs instrs params blockVars decls blockInstrs
%type <expression> literal expr funcCall
%type <lvalue> lval
%type <string> string
%type <integerNode> integer
%type <doubleNode> double
%type <block> block
%type <type> intPtr doublePtr stringPtr type
%type <typedNode> var blockVar param funcDecl funcDef func decl

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

file :                      { compiler->ast(new cdk::sequence_node(LINE));}
     | decls                { compiler->ast($1);}
     ;

decls : decl                { $$ = new cdk::sequence_node(LINE, $1); }
      | decls decl           { $$ = new cdk::sequence_node(LINE, $2, $1); }
      ;

decl : func                 {$$ = $1;}
     | var ';'              {$$ = $1;}
     ;

func : funcDecl ';'         {$$ = $1;}
     | funcDef              {$$ = $1;}
     ;

funcCall : tUSE exprs tFOR tIDENTIFIER          {$$ = new gr8::function_call_node(LINE, $4, $2);} 
         | tDO tIDENTIFIER                      {$$ = new gr8::function_call_node(LINE, $2, new cdk::sequence_node(LINE));} 
	 ;

funcDef : tDEFINE type tFUNCTION tIDENTIFIER tAS block                          { $$ = new gr8::function_define_node(LINE, false, false, $2, $4, new cdk::sequence_node(LINE), $6);} 
        | tDEFINE tPROCEDURE tIDENTIFIER tAS block                              { $$ = new gr8::function_define_node(LINE, false, true, new basic_type(0, basic_type::TYPE_VOID), $3, new cdk::sequence_node(LINE), $5);}
        | tDEFINE type tFUNCTION tIDENTIFIER tON params tAS block               { $$ = new gr8::function_define_node(LINE, false, false, $2, $4, $6, $8);}
        | tDEFINE tPROCEDURE tIDENTIFIER tON params tAS block                   { $$ = new gr8::function_define_node(LINE, false, true, new basic_type(0, basic_type::TYPE_VOID), $3, $5, $7);}
        | tDEFINE tPUBLIC type tFUNCTION tIDENTIFIER tAS block                  { $$ = new gr8::function_define_node(LINE, true, false, $3, $5, new cdk::sequence_node(LINE), $7);}
        | tDEFINE tPUBLIC tPROCEDURE tIDENTIFIER tAS block                      { $$ = new gr8::function_define_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), $4, new cdk::sequence_node(LINE), $6);}
        | tDEFINE tPUBLIC type tFUNCTION tIDENTIFIER tON params tAS block       { $$ = new gr8::function_define_node(LINE, true, false, $3, $5, $7, $9);}
        | tDEFINE tPUBLIC tPROCEDURE tIDENTIFIER tON params tAS block           { $$ = new gr8::function_define_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), $4, $6, $8);}
        ;

funcDecl : type tFUNCTION tIDENTIFIER                           { $$ = new gr8::function_declaration_node(LINE, false, false, $1, $3, new cdk::sequence_node(LINE));}
         | tPROCEDURE tIDENTIFIER                               { $$ = new gr8::function_declaration_node(LINE, false, true, new basic_type(0, basic_type::TYPE_VOID), $2, new cdk::sequence_node(LINE));}
         | type tFUNCTION tIDENTIFIER tUSES params              { $$ = new gr8::function_declaration_node(LINE, false, false, $1, $3, $5);}
         | tPROCEDURE tIDENTIFIER tUSES params                  { $$ = new gr8::function_declaration_node(LINE, false, true, new basic_type(0, basic_type::TYPE_VOID), $2, $4);}
         | tPUBLIC type tFUNCTION tIDENTIFIER                   { $$ = new gr8::function_declaration_node(LINE, true, false, $2, $4, new cdk::sequence_node(LINE));}
         | tPUBLIC tPROCEDURE tIDENTIFIER                       { $$ = new gr8::function_declaration_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), $3, new cdk::sequence_node(LINE));}
         | tPUBLIC type tFUNCTION tIDENTIFIER tUSES params      { $$ = new gr8::function_declaration_node(LINE, true, false, $2, $4, $6);}
         | tPUBLIC tPROCEDURE tIDENTIFIER tUSES params          { $$ = new gr8::function_declaration_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), $3, $5);}
         | tUSE type tFUNCTION tIDENTIFIER                      { $$ = new gr8::function_declaration_node(LINE, true, false, $2, $4, new cdk::sequence_node(LINE));}
         | tUSE tPROCEDURE tIDENTIFIER                          { $$ = new gr8::function_declaration_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), $3, new cdk::sequence_node(LINE));}
         | tUSE type tFUNCTION tIDENTIFIER tUSES params         { $$ = new gr8::function_declaration_node(LINE, true, false, $2, $4, $6);}
         | tUSE tPROCEDURE tIDENTIFIER tUSES params             { $$ = new gr8::function_declaration_node(LINE, true, true, new basic_type(0, basic_type::TYPE_VOID), $3, $5);}
         ;

params : param                                      { $$ = new cdk::sequence_node(LINE, $1); }
       | params ',' param                           { $$ = new cdk::sequence_node(LINE, $3, $1); }
       ;

param : type tIDENTIFIER                                      { $$ = new gr8::variable_declaration_node(LINE, false, false, $1, $2, nullptr);}
      ;

blockVars : blockVar ';'                { $$ = new cdk::sequence_node(LINE, $1); }
          | blockVars blockVar ';'      { $$ = new cdk::sequence_node(LINE, $2, $1); }
          ;

blockVar : type tIDENTIFIER                                      { $$ = new gr8::variable_declaration_node(LINE, false, false, $1, $2, nullptr);}
         | type tIDENTIFIER '(' tINITIALLY expr ')'              { $$ = new gr8::variable_declaration_node(LINE, false, false, $1, $2, $5);}
         ;

var : type tIDENTIFIER                                      { $$ = new gr8::variable_declaration_node(LINE, false, false, $1, $2, nullptr);}
    | type tIDENTIFIER '(' tINITIALLY literal ')'              { $$ = new gr8::variable_declaration_node(LINE, false, false, $1, $2, $5);}
    | tPUBLIC type tIDENTIFIER                              { $$ = new gr8::variable_declaration_node(LINE, true, false, $2, $3, nullptr);}
    | tPUBLIC type tIDENTIFIER '(' tINITIALLY literal ')'      { $$ = new gr8::variable_declaration_node(LINE, true, false, $2, $3, $6);}
    | tUSE type tIDENTIFIER                                 { $$ = new gr8::variable_declaration_node(LINE, false, true, $2, $3, nullptr);}
    ;

type : tTYPEINT                             { $$ = new basic_type(4, basic_type::TYPE_INT);}
     | intPtr tFAKE                         { $$ = $1;}
     | tTYPEDOUBLE                          { $$ = new basic_type(8, basic_type::TYPE_DOUBLE);}
     | doublePtr tFAKE                      { $$ = $1;}
     | tTYPESTRING                          { $$ = new basic_type(4, basic_type::TYPE_STRING);}
     | stringPtr tTYPESTRING                { $$ = $1;}
     ;

stringPtr : tFAKE                           { $$ = new basic_type(4, basic_type::TYPE_POINTER);
                                              $$->_subtype = new basic_type(4, basic_type::TYPE_STRING);}         
          | tFAKE stringPtr                 { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = $2;}
          ;

doublePtr : tTYPEDOUBLE                     { $$ = new basic_type(4, basic_type::TYPE_POINTER);
                                              $$->_subtype = new basic_type(8, basic_type::TYPE_DOUBLE);}
          | tTYPEDOUBLE doublePtr           { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = $2;}
          ;

intPtr : tTYPEINT                           { $$ = new basic_type(4, basic_type::TYPE_POINTER); 
                                              $$->_subtype = new basic_type(4, basic_type::TYPE_INT);}
       | tTYPEINT intPtr                    { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = $2;}
       ;

block  : '{' '}'                            { $$ = new gr8::block_node(LINE, new cdk::sequence_node(LINE), new cdk::sequence_node(LINE));}
       | '{' blockVars '}'                  { $$ = new gr8::block_node(LINE, $2, new cdk::sequence_node(LINE)); }
       | '{' blockInstrs '}'                { $$ = new gr8::block_node(LINE, new cdk::sequence_node(LINE), $2); }
       | '{' blockVars blockInstrs '}'      { $$ = new gr8::block_node(LINE, $2, $3); }
       ;

blockInstrs : instrs                        { $$ = $1; }
            | finalInstr                    { $$ = new cdk::sequence_node(LINE, $1); }
            | instrs finalInstr             { $$ = new cdk::sequence_node(LINE, $2, $1); }
            ;

instrs : instr                              { $$ = new cdk::sequence_node(LINE, $1); }
       | instrs instr                       { $$ = new cdk::sequence_node(LINE, $2, $1); }
       ;

finalInstr : tAGAIN ';'                          { $$ = new gr8::again_node(LINE, new cdk::integer_node(LINE, 1)); }
           | tAGAIN integer ';'                  { $$ = new gr8::again_node(LINE, $2); }
           | tSTOP ';'                           { $$ = new gr8::stop_node(LINE, new cdk::integer_node(LINE,1)); }
           | tSTOP integer ';'                   { $$ = new gr8::stop_node(LINE, $2); }
           | tRETURN ';'                         { $$ = new gr8::return_node(LINE, nullptr); }
           | tRETURN expr ';'                    { $$ = new gr8::return_node(LINE, $2); }
           ;

instr : expr ';'                            { $$ = new gr8::evaluation_node(LINE, $1); }
      | tPRINT expr ';'                     { $$ = new gr8::print_node(LINE, $2, false); }
      | tPRINTLN expr ';'                   { $$ = new gr8::print_node(LINE, $2, true); }
      | tASSIGN expr tTO lval ';'           { $$ = new cdk::assignment_node(LINE, $4, $2); }
      | instrCond                           { $$ = $1; }
      | sweeping                            { $$ = $1; }
      | block                               { $$ = $1; }     
      ;

sweeping : tSWEEPING lval tFROM expr tTO expr tDO block             { $$ = new gr8::sweeping_from_to_by_do_node(LINE, $2, $4, $6, new cdk::integer_node(LINE, 1), $8);}
         | tSWEEPING lval tFROM expr tTO expr tBY expr tDO block    { $$ = new gr8::sweeping_from_to_by_do_node(LINE, $2, $4, $6, $8, $10);}  
         ;

instrCond : tIF ifs                     { $$ = $2; }
          ;

ifs : expr tTHEN block                      { $$ = new gr8::if_node(LINE, $1, $3); }
    | expr tTHEN block tELSE block          { $$ = new gr8::if_else_node(LINE, $1, $3, $5);}
    | expr tTHEN block tELSIF ifs           { $$ = new gr8::if_else_node(LINE, $1, $3, $5);}
    ;

exprs : expr                            { $$ = new cdk::sequence_node(LINE, $1); }
      | exprs ',' expr                  { $$ = new cdk::sequence_node(LINE, $3, $1); }
      ; 

expr : literal                          { $$ = $1; }
     | funcCall                         { $$ = $1; }
     | '(' expr ')'                     { $$ = $2; } 
     | '+' expr %prec tUNARY            { $$ = new gr8::identity_node(LINE, $2); }
     | '-' expr %prec tUNARY            { $$ = new cdk::neg_node(LINE, $2); }
     | expr tOBJECTS                    { $$ = new gr8::memory_allocation_node(LINE, $1); }     
     | expr '+' expr                    { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr                    { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr                    { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr                    { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr                    { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr                    { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr                    { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tEQUALS expr	        { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '!' expr                         { $$ = new cdk::not_node(LINE, $2); }
     | expr tAND expr                   { $$ = new cdk::and_node(LINE, $1, $3); }
     | expr tOR expr                    { $$ = new cdk::or_node(LINE, $1, $3); }
     | lval                             { $$ = new cdk::rvalue_node(LINE, $1); }
     | lval '?'                         { $$ = new gr8::address_of_node(LINE, $1); }    
     | tINPUT                           { $$ = new gr8::read_node(LINE); }
     ;

lval : tCELL expr tAT lval %prec tINDEXING          { $$ = new gr8::index_node(LINE, new cdk::rvalue_node(LINE, $4), $2); }
     | tCELL expr tAT '(' expr ')' %prec tINDEXING   { $$ = new gr8::index_node(LINE, $5, $2); }
     | tIDENTIFIER                                  { $$ = new cdk::identifier_node(LINE, $1); delete $1; }
     ;

literal : integer                       { $$ = $1; }
        | double                        { $$ = $1; }
        | string                        { $$ = $1; }
        | tNULL                         { $$ = new gr8::null_node(LINE); }
        ;

integer : tINT                          { $$ = new cdk::integer_node(LINE, $1); }
        ;

double : tDOUBLE                        { $$ = new cdk::double_node(LINE, $1); }
       ;

string : tSTRING                          { $$ = new cdk::string_node(LINE, $1); delete $1;}
       | string tSTRING                   { $$ = new cdk::string_node(LINE, std::string($1->value() + *$2)); delete $1; delete $2;} 
       ;
%%
