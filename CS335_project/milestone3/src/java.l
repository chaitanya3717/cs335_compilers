%option header-file="lex.yy.h"
%option noyywrap


%top{
  #include "java.tab.hpp"
  #include <iostream>
  #include <string>
  using namespace std;
  extern int yylineno;
  #define SINGLE_LINE_COMMENT 3
  #define MULTI_LINE_COMMENT 4
}

%x MULTI_LINE_COMMENT_BODY
%x SINGLE_LINE_COMMENT_BODY

IDENTIFIER  [A-Za-z_][A-Za-z0-9_]*

CHAR                  [^\']
LITERAL_CHAR     \'{CHAR}\'

STRING_CHAR                  [^\"]
STRING_CHAR_SEQUENCE         {STRING_CHAR}+
LITERAL_STR          \"({STRING_CHAR_SEQUENCE}?)\"

DIGIT                   [0-9]
NONZERO_DIGIT           [1-9]
LITERAL_INT        {NONZERO_DIGIT}{DIGIT}*[lLdDfF]?
LITERAL_FLOAT          ({DIGIT}*\.{DIGIT}+[fFdD]?)|({DIGIT}+\.{DIGIT}*[fFdD]?)


HEX_DIGIT         [0-9A-Fa-f]
HEX_INT          "0"[X|x]{HEX_DIGIT}+[lL]?

OCT_DIGIT          [0-7]
OCT_INT         "0"{OCT_DIGIT}+[lL]?|"0"[lLfFdD]?


BIN_DIGIT      [0-1]
BIN_INT        "0"[B|b]{BIN_DIGIT}+[lL]?


LITERAL_INT_EXPONENT            {NONZERO_DIGIT}{DIGIT}*[eE][+-]?[0-9]+[lL]?

LIT_FLOAT_EXPONENT        ([0-9]*.[0-9]+[eE][+-]?[0-9]+[fFdD]?)|([0-9]+.[0-9]*[eE][+-]?[0-9]+[fFdD]?)

LIT_HEXINT_EXPONENT           "0"[x|X]{HEX_DIGIT}+[pP][+-]?[DIGIT]+[lL]?

LIT_HEXFLOAT_EXPONENT        ("0"[x|X][0-9A-Fa-f]*.[0-9A-Fa-f]+[pP][+-]?[0-9]+[fFdD]?)|("0"[x|X][0-9A-Fa-f]+.[0-9A-Fa-f]*[pP][+-]?[0-9]+[fFdD]?)

WHITESPACE [ \t\f]

NEWLINE [\n]

%%
{NEWLINE}                       {yylineno++;}
{WHITESPACE}+                    { }


"abstract"              {yylval.name = strdup(yytext);return abstract;}
"boolean"              {yylval.name = strdup(yytext);return boolean;}
"break"              {yylval.name = strdup(yytext);return break_1;}
"catch"              {yylval.name = strdup(yytext);return catch_1;}
"char"              {yylval.name = strdup(yytext);return char_1;}
"class"              {yylval.name = strdup(yytext);return class_1;}
"continue"              {yylval.name = strdup(yytext);return continue_1;}
"double"              {yylval.name = strdup(yytext);return double_1;}
"else"              {yylval.name = strdup(yytext);return else_1;}
"extends"              {yylval.name = strdup(yytext);return extends;}
"final"              {yylval.name = strdup(yytext);return final;}
"finally"              {yylval.name = strdup(yytext);return finally;}
"float"              {yylval.name = strdup(yytext);return float_1;}
"for"              {yylval.name = strdup(yytext);return for_1;}
"if"              {yylval.name = strdup(yytext);return if_1;}
"implements"              {yylval.name = strdup(yytext);return implements;}
"import"              {yylval.name = strdup(yytext);return import;}
"instanceof"              {yylval.name = strdup(yytext);return instanceof;}
"int"              {yylval.name = strdup(yytext);return int_1;}
"interface"              {yylval.name = strdup(yytext);return interface;}
"long"              {yylval.name = strdup(yytext);return long_1;}
"native"              {yylval.name = strdup(yytext);return native;}
"new"              {yylval.name = strdup(yytext);return new_1;}
"package"              {yylval.name = strdup(yytext);return package;}
"private"              {yylval.name = strdup(yytext);return private_1;}
"public"              {yylval.name = strdup(yytext);return public_1;}
"return"              {yylval.name = strdup(yytext);return return_1;}
"static"              {yylval.name = strdup(yytext);return static_1;}
"strictfp"              {yylval.name = strdup(yytext);return strictfp;}
"super"              {yylval.name = strdup(yytext);return super;}
"synchronized"              {yylval.name = strdup(yytext);return synchronized;}
"this"              {yylval.name = strdup(yytext);return this_1;}
"throw"              {yylval.name = strdup(yytext);return throw_1;}
"throws"              {yylval.name = strdup(yytext);return throws;}
"transient"              {yylval.name = strdup(yytext);return transient;}
"try"              {yylval.name = strdup(yytext);return try_1;}
"void"              {yylval.name = strdup(yytext);return void_1;}
"volatile"              {yylval.name = strdup(yytext);return volatile_1;}
"while"              {yylval.name = strdup(yytext);return while_1;}
"String"            {yylval.name = strdup(yytext);return String;}

"("              {yylval.name = strdup(yytext);return L_bracket;}
")"              {yylval.name = strdup(yytext);return R_bracket;}
"{"              {yylval.name = strdup(yytext);return LF_bracket;}
"}"              {yylval.name = strdup(yytext);return RF_bracket;}
"["              {yylval.name = strdup(yytext);return LS_bracket;}
"]"              {yylval.name = strdup(yytext);return RS_bracket;}
";"              {yylval.name = strdup(yytext);return semicolon;}
","              {yylval.name = strdup(yytext);return comma;}
"."              {yylval.name = strdup(yytext);return dot;}


"true"       {yylval.name = strdup(yytext);return BooleanLiteral; }
"false"       {yylval.name = strdup(yytext);return BooleanLiteral; }
"null"               {yylval.name = strdup(yytext);return NullLiteral; }


{LITERAL_INT}               {yylval.name = strdup(yytext);return IntegerLiteral; }
{HEX_INT}           {yylval.name = strdup(yytext);return IntegerLiteral; }
{OCT_INT}            {yylval.name = strdup(yytext);return IntegerLiteral; }
{BIN_INT}          {yylval.name = strdup(yytext);return IntegerLiteral; }


{LITERAL_INT_EXPONENT}           {yylval.name = strdup(yytext);return IntegerLiteral; }
{LIT_FLOAT_EXPONENT}           {yylval.name = strdup(yytext);return FloatingPointLiteral; }


{LIT_HEXINT_EXPONENT}          {yylval.name = strdup(yytext);return IntegerLiteral; }
{LIT_HEXFLOAT_EXPONENT}            {yylval.name = strdup(yytext);return FloatingPointLiteral; }


{LITERAL_FLOAT}            {yylval.name = strdup(yytext);return FloatingPointLiteral; }


  
{LITERAL_CHAR}               {yylval.name = strdup(yytext);return CharacterLiteral;}
{LITERAL_STR}                 {yylval.name = strdup(yytext);return StringLiteral;}


"+"              {yylval.name = strdup(yytext);return addn;}
"-"              {yylval.name = strdup(yytext);return subt;}
"*"              {yylval.name = strdup(yytext);return mult;}
"/"              {yylval.name = strdup(yytext);return div_1;}
"%"              {yylval.name = strdup(yytext);return modulo;}
"++"              {yylval.name = strdup(yytext);return increment;}
"--"              {yylval.name = strdup(yytext);return decrement;}

"=="              {yylval.name = strdup(yytext);return equals;}
">"              {yylval.name = strdup(yytext);return greaterthan;}
"<"              {yylval.name = strdup(yytext);return lessthan;}
">="              {yylval.name = strdup(yytext);return greaterequal;}
"<="              {yylval.name = strdup(yytext);return lessequal;}
"!="              {yylval.name = strdup(yytext);return notequal;}


"&"              {yylval.name = strdup(yytext);return bitand_1;}
"|"              {yylval.name = strdup(yytext);return bitor_1;}
"^"              {yylval.name = strdup(yytext);return bitxor;}
"<<"              {yylval.name = strdup(yytext);return leftshift;}
">>"              {yylval.name = strdup(yytext);return rightshift;}
">>>"              {yylval.name = strdup(yytext);return urightshift;}
"~"              {yylval.name = strdup(yytext);return bitcomp;}

"&&"              {yylval.name = strdup(yytext);return and_1;}
"||"              {yylval.name = strdup(yytext);return or_1;}
"!"              {yylval.name = strdup(yytext);return not_1;}

"="              {yylval.name = strdup(yytext);return assignment;}
"+="              {yylval.name = strdup(yytext);return asnaddn;}
"-="              {yylval.name = strdup(yytext);return asnsub;}
"*="              {yylval.name = strdup(yytext);return asnmul;}
"/="              {yylval.name = strdup(yytext);return asndiv;}
"&="              {yylval.name = strdup(yytext);return asnand;}
"|="              {yylval.name = strdup(yytext);return asnor;}
"^="              {yylval.name = strdup(yytext);return asnxor;}
"%="              {yylval.name = strdup(yytext);return asnmod;}
"<<="              {yylval.name = strdup(yytext);return asnls;}
">>="              {yylval.name = strdup(yytext);return asnrs;}
">>>="              {yylval.name = strdup(yytext);return asnurs;}





"?"              {yylval.name = strdup(yytext);return questionmark;}
":"              {yylval.name = strdup(yytext);return colon;}


{IDENTIFIER}             {yylval.name = strdup(yytext);return identifier; }


"/*"                            {BEGIN(MULTI_LINE_COMMENT_BODY); }
<MULTI_LINE_COMMENT_BODY>[^*/\n]+
<MULTI_LINE_COMMENT_BODY>"\n"   {yylineno++;}
<MULTI_LINE_COMMENT_BODY><<EOF>>    cout<<"Code has ended without closing the comment";return 0;
<MULTI_LINE_COMMENT_BODY>"*/"      BEGIN(INITIAL);


"//"                            {BEGIN(SINGLE_LINE_COMMENT_BODY); }
<SINGLE_LINE_COMMENT_BODY>[^*/\n]+
<SINGLE_LINE_COMMENT_BODY>"\n"  {yylineno++; BEGIN(INITIAL); }
<SINGLE_LINE_COMMENT_BODY><<EOF>>    cout<<"Code has ended without closing the comment";return 0;


.    {;} 
%%

