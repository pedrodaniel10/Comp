%option c++ prefix="gr8_scanner_" outfile="gr8_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{ 
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>
#include <stack>
#include <queue>
#include "gr8_parser.tab.h"

// don't change this
#define yyerror LexerError

std::stack<int> identationStack;
std::queue<char> tokensToSend;

bool notInstruction = false;
int getIdentation(const char* yytext, int yyleng);
void calculateTokenIdentation(const char* yytext, int yyleng, bool eof);
%}
%x X_COMMENT X_STRING X_STRING_ESCAPECHAR X_STRING_IGNORE X_NEW_LINE X_SEND_TOKENS

IDENTIFIER                                  [A-Za-z][A-Za-z0-9\-]*
SPACE                                       [ \t]
SYMBOLS                                     [()?,]

SMALL_B07                                   0[0-6]+
SMALL_B10                                   [1-9]+[0-9]*|0
EXPONENT                                    [eE][-+]?[0-9]+
REAL                                        [0-9]*\.[0-9]+{EXPONENT}?|[0-9]+\.{EXPONENT}?|[0-9]+{EXPONENT}

EMPTY_LINE                                  ^{SPACE}*\n
LINE_BREAK                                  "..."\n
%%

"small"                                     return tTYPEINT;
"huge"                                      return tTYPEDOUBLE;
"news"                                      return tTYPESTRING;
"fake"                                      return tFAKE;
"initially"                                 return tINITIALLY;

"use"                                       return tUSE;
"public"                                    return tPUBLIC;
"procedure"                                 return tPROCEDURE;
"function"                                  return tFUNCTION;

"define"                                    return tDEFINE;
"on"                                        return tON;
"as"                                        notInstruction = true; return tAS;
"do"                                        notInstruction = true; return tDO;
"uses"                                      return tUSES;
"for"                                       return tFOR;
"return"                                    return tRETURN;

"plus"                                      return '+';
"minus"                                     return '-';
"times"                                     return '*';
"over"                                      return '/';
"modulus"                                   return '%';
"not"                                       return '!';
"and"                                       return tAND;
"or"                                        return tOR;

"above"                                     return '>';
"below"                                     return '<';
"equals"                                    return tEQUALS;

"assign"                                    return tASSIGN;
"to"                                        return tTO;

"cell"                                      return tCELL;
"at"                                        return tAT;

"input"                                     return tINPUT;
"post"                                      return tPRINTLN;
"tweet"                                     return tPRINT;

"objects"                                   return tOBJECTS;

"if"                                        return tIF;
"then"                                      notInstruction = true; return tTHEN;
"elsif"                                     return tELSIF;
"else"                                      notInstruction = true; return tELSE;

"stop"                                      return tSTOP;
"again"                                     return tAGAIN;

"sweeping"                                  return tSWEEPING;
"from"                                      return tFROM;
"by"                                        return tBY;

"null"                                      return tNULL;

<*>{EMPTY_LINE}                             ; /*ignore*/
<*>{LINE_BREAK}                             ; /*ignore*/

{IDENTIFIER}                                yylval.s = new std::string(yytext); return tIDENTIFIER;

{SYMBOLS}                                   return *yytext;

{SMALL_B07}                                 {
                                             yylval.i = strtol(yytext, nullptr, 7);
                                             if(errno == ERANGE) 
                                                yyerror("ERROR: Overflow! The value cannot be stored in 32bit"); 
                                             return tINT;
                                            }

{SMALL_B10}                                 {
                                             yylval.i = strtol(yytext, nullptr, 10); 
                                             if(errno == ERANGE) 
                                                yyerror("ERROR: Overflow! The value cannot be stored in 32bit");
                                             return tINT;
                                            }

{REAL}                                      {
                                             yylval.r = strtod(yytext, nullptr);
                                             if(errno == ERANGE) 
                                                yyerror("ERROR: Overflow! The value can not be represented in IEEE754.");
                                             return tDOUBLE;
                                            }

\n                                          yy_push_state(X_NEW_LINE);
<X_NEW_LINE>^{SPACE}*                       {
                                             yy_pop_state(); 
                                             calculateTokenIdentation(yytext,yyleng,false);
                                             yy_push_state(X_SEND_TOKENS);
                                            }
<X_NEW_LINE>.                               {
                                             yyless(0); yy_pop_state();
                                             calculateTokenIdentation("",0,false);
                                             yy_push_state(X_SEND_TOKENS);
                                            }

<*><<EOF>>                                  {
                                             calculateTokenIdentation(yytext,yyleng,true);
                                             if(tokensToSend.empty()) 
                                                return 0;
                                             else{
                                                char token = tokensToSend.front();
                                                tokensToSend.pop();                                                
                                                return token;
                                             }
                                            }

<X_SEND_TOKENS>.|\n                         {
                                             yyless(0);
                                             if(tokensToSend.empty()) 
                                                yy_pop_state();
                                             else{
                                                char token = tokensToSend.front();
                                                tokensToSend.pop();
                                                return token;
                                             }
                                            }

"!!".*\n                                     ; /*ignore line comment*/

"<<"                                        yy_push_state(X_COMMENT);
<X_COMMENT>">>"                             yy_pop_state();
<X_COMMENT>">>"\n                           yy_pop_state();
<X_COMMENT>.|\n                             ; /*ignore: belongs to comment*/

\"                                          yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"                                yy_pop_state(); return tSTRING;
<X_STRING>~                                 yy_push_state(X_STRING_ESCAPECHAR);
<X_STRING>\0                                yyerror("null char in string");
<X_STRING>.                                 *yylval.s += yytext;
<X_STRING>\n                                yyerror("newline in string");

<X_STRING_ESCAPECHAR>n                      *yylval.s += "\n"; yy_pop_state();
<X_STRING_ESCAPECHAR>r                      *yylval.s += "\r"; yy_pop_state();
<X_STRING_ESCAPECHAR>t                      *yylval.s += "\t"; yy_pop_state();
<X_STRING_ESCAPECHAR>\"                     *yylval.s += "\""; yy_pop_state();
<X_STRING_ESCAPECHAR>~                      *yylval.s += "~";  yy_pop_state();
<X_STRING_ESCAPECHAR>0|"00"|"000"           {
                                             yy_pop_state(); /*pop X_STRING_ESCAPECHAR*/
                                             yy_pop_state(); /*pop X_STRING*/
                                             yy_push_state(X_STRING_IGNORE);
                                            }
<X_STRING_ESCAPECHAR>[0-6]{1,3}             {
                                             unsigned int number = strtol(yytext, NULL, 7);
                                             if(number > 255) 
                                                yyerror("ERROR: Overflow! The value is above 2^8.");
                                             else {
                                                *yylval.s += std::string(1,number); 
                                                yy_pop_state();
                                             }
                                            }
<X_STRING_ESCAPECHAR>.                     yy_pop_state(); *yylval.s +=std::string(yytext);

<X_STRING_IGNORE>"~\""                     ; /*ignore*/
<X_STRING_IGNORE>\"                        yy_pop_state(); return tSTRING;
<X_STRING_IGNORE>.|\n                      ; /*ignore*/                 

[ \t]+                                     ; /* ignore whitespace */

.                                          yyerror("LEXERROR: Unknown char");

%%
int getIdentation(const char* yytext, int yyleng){
    int identation = 0;
    for(int i = 0; i < yyleng; i++){
        if(yytext[i] == ' ')
            identation += 1;
        else if(yytext[i] == '\t')
            identation += 8 - identation % 8;
    }
    return identation;
}

void calculateTokenIdentation(const char* yytext, int yyleng, bool eof){
    int identation;

    //check if stack is empty
    if(identationStack.empty())
        identationStack.push(0);

    if(identationStack.top()==0 && eof)
        return;

    //check if is eof
    if(eof)
        identation = 0;
    else
        identation = getIdentation(yytext,yyleng);

    if(identation > identationStack.top()){
        identationStack.push(identation);
        if(notInstruction){
            notInstruction = false;
        }
        else{
            tokensToSend.push(';');
        }
        tokensToSend.push('{');
        return;
    }
    else if(identation == identationStack.top()){
        tokensToSend.push(';');
        return;
    }
    
    tokensToSend.push(';');
    while(identation != identationStack.top()){
        if(identation > identationStack.top()){
            tokensToSend.push('{');
            identationStack.push(identation);
            return;
        }
        tokensToSend.push('}');
        identationStack.pop();
    }
    return;
}