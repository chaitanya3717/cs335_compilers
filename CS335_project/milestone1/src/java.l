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

TEXTBLOCK ["]["]["][ \t][\n\x0d]([^\"]|([^\][^\"])|([^\][^\][^\"])|[\n])["]["]["]

LITERAL_INT_EXPONENT            {NONZERO_DIGIT}{DIGIT}*[eE][+-]?[0-9]+[lL]?

LIT_FLOAT_EXPONENT        ([0-9]*.[0-9]+[eE][+-]?[0-9]+[fFdD]?)|([0-9]+.[0-9]*[eE][+-]?[0-9]+[fFdD]?)

LIT_HEXINT_EXPONENT           "0"[x|X]{HEX_DIGIT}+[pP][+-]?[DIGIT]+[lL]?

LIT_HEXFLOAT_EXPONENT        ("0"[x|X][0-9A-Fa-f]*.[0-9A-Fa-f]+[pP][+-]?[0-9]+[fFdD]?)|("0"[x|X][0-9A-Fa-f]+.[0-9A-Fa-f]*[pP][+-]?[0-9]+[fFdD]?)

WHITESPACE [ \t\f]

NEWLINE [\n]

%%
{NEWLINE}                       {yylineno++;}
{WHITESPACE}+                    { }


"abstract"              {strcpy(yylval.nd_obj.name,(yytext));return abstract;}
"assert"              {strcpy(yylval.nd_obj.name,(yytext));return assert;}
"boolean"              {strcpy(yylval.nd_obj.name,(yytext));return boolean;}
"break"              {strcpy(yylval.nd_obj.name,(yytext));return break_1;}
"catch"              {strcpy(yylval.nd_obj.name,(yytext));return catch_1;}
"char"              {strcpy(yylval.nd_obj.name,(yytext));return char_1;}
"class"              {strcpy(yylval.nd_obj.name,(yytext));return class_1;}
"continue"              {strcpy(yylval.nd_obj.name,(yytext));return continue_1;}
"double"              {strcpy(yylval.nd_obj.name,(yytext));return double_1;}
"else"              {strcpy(yylval.nd_obj.name,(yytext));return else_1;}
"extends"              {strcpy(yylval.nd_obj.name,(yytext));return extends;}
"final"              {strcpy(yylval.nd_obj.name,(yytext));return final;}
"finally"              {strcpy(yylval.nd_obj.name,(yytext));return finally;}
"float"              {strcpy(yylval.nd_obj.name,(yytext));return float_1;}
"for"              {strcpy(yylval.nd_obj.name,(yytext));return for_1;}
"if"              {strcpy(yylval.nd_obj.name,(yytext));return if_1;}
"implements"              {strcpy(yylval.nd_obj.name,(yytext));return implements;}
"import"              {strcpy(yylval.nd_obj.name,(yytext));return import;}
"instanceof"              {strcpy(yylval.nd_obj.name,(yytext));return instanceof;}
"int"              {strcpy(yylval.nd_obj.name,(yytext));return int_1;}
"interface"              {strcpy(yylval.nd_obj.name,(yytext));return interface;}
"long"              {strcpy(yylval.nd_obj.name,(yytext));return long_1;}
"native"              {strcpy(yylval.nd_obj.name,(yytext));return native;}
"new"              {strcpy(yylval.nd_obj.name,(yytext));return new_1;}
"package"              {strcpy(yylval.nd_obj.name,(yytext));return package;}
"private"              {strcpy(yylval.nd_obj.name,(yytext));return private_1;}
"public"              {strcpy(yylval.nd_obj.name,(yytext));return public_1;}
"return"              {strcpy(yylval.nd_obj.name,(yytext));return return_1;}
"static"              {strcpy(yylval.nd_obj.name,(yytext));return static_1;}
"strictfp"              {strcpy(yylval.nd_obj.name,(yytext));return strictfp;}
"super"              {strcpy(yylval.nd_obj.name,(yytext));return super;}
"synchronized"              {strcpy(yylval.nd_obj.name,(yytext));return synchronized;}
"this"              {strcpy(yylval.nd_obj.name,(yytext));return this_1;}
"throw"              {strcpy(yylval.nd_obj.name,(yytext));return throw_1;}
"throws"              {strcpy(yylval.nd_obj.name,(yytext));return throws;}
"transient"              {strcpy(yylval.nd_obj.name,(yytext));return transient;}
"try"              {strcpy(yylval.nd_obj.name,(yytext));return try_1;}
"void"              {strcpy(yylval.nd_obj.name,(yytext));return void_1;}
"volatile"              {strcpy(yylval.nd_obj.name,(yytext));return volatile_1;}
"while"              {strcpy(yylval.nd_obj.name,(yytext));return while_1;}
"String"            {strcpy(yylval.nd_obj.name,(yytext));return String;}

"("              {strcpy(yylval.nd_obj.name,(yytext));return L_bracket;}
")"              {strcpy(yylval.nd_obj.name,(yytext));return R_bracket;}
"{"              {strcpy(yylval.nd_obj.name,(yytext));return LF_bracket;}
"}"              {strcpy(yylval.nd_obj.name,(yytext));return RF_bracket;}
"["              {strcpy(yylval.nd_obj.name,(yytext));return LS_bracket;}
"]"              {strcpy(yylval.nd_obj.name,(yytext));return RS_bracket;}
";"              {strcpy(yylval.nd_obj.name,(yytext));return semicolon;}
","              {strcpy(yylval.nd_obj.name,(yytext));return comma;}
"."              {strcpy(yylval.nd_obj.name,(yytext));return dot;}


"true"       {strcpy(yylval.nd_obj.name,(yytext));return BooleanLiteral; }
"false"       {strcpy(yylval.nd_obj.name,(yytext));return BooleanLiteral; }
"null"               {strcpy(yylval.nd_obj.name,(yytext));return NullLiteral; }


{TEXTBLOCK}         {strcpy(yylval.nd_obj.name,(yytext));return TextBlock;}

{LITERAL_INT}               {strcpy(yylval.nd_obj.name,(yytext));return IntegerLiteral; }
{HEX_INT}           {strcpy(yylval.nd_obj.name,(yytext));return IntegerLiteral; }
{OCT_INT}            {strcpy(yylval.nd_obj.name,(yytext));return IntegerLiteral; }
{BIN_INT}          {strcpy(yylval.nd_obj.name,(yytext));return IntegerLiteral; }


{LITERAL_INT_EXPONENT}           {strcpy(yylval.nd_obj.name,(yytext));return IntegerLiteral; }
{LIT_FLOAT_EXPONENT}           {strcpy(yylval.nd_obj.name,(yytext));return FloatingPointLiteral; }


{LIT_HEXINT_EXPONENT}          {strcpy(yylval.nd_obj.name,(yytext));return IntegerLiteral; }
{LIT_HEXFLOAT_EXPONENT}            {strcpy(yylval.nd_obj.name,(yytext));return FloatingPointLiteral; }


{LITERAL_FLOAT}            {strcpy(yylval.nd_obj.name,(yytext));return FloatingPointLiteral; }


  
{LITERAL_CHAR}               {strcpy(yylval.nd_obj.name,(yytext));return CharacterLiteral;}
{LITERAL_STR}                 {strcpy(yylval.nd_obj.name,(yytext));return StringLiteral;}


"+"              {strcpy(yylval.nd_obj.name,(yytext));return addn;}
"-"              {strcpy(yylval.nd_obj.name,(yytext));return subt;}
"*"              {strcpy(yylval.nd_obj.name,(yytext));return mult;}
"/"              {strcpy(yylval.nd_obj.name,(yytext));return div_1;}
"%"              {strcpy(yylval.nd_obj.name,(yytext));return modulo;}
"++"              {strcpy(yylval.nd_obj.name,(yytext));return increment;}
"--"              {strcpy(yylval.nd_obj.name,(yytext));return decrement;}

"=="              {strcpy(yylval.nd_obj.name,(yytext));return equals;}
">"              {strcpy(yylval.nd_obj.name,(yytext));return greaterthan;}
"<"              {strcpy(yylval.nd_obj.name,(yytext));return lessthan;}
">="              {strcpy(yylval.nd_obj.name,(yytext));return greaterequal;}
"<="              {strcpy(yylval.nd_obj.name,(yytext));return lessequal;}
"!="              {strcpy(yylval.nd_obj.name,(yytext));return notequal;}


"&"              {strcpy(yylval.nd_obj.name,(yytext));return bitand_1;}
"|"              {strcpy(yylval.nd_obj.name,(yytext));return bitor_1;}
"^"              {strcpy(yylval.nd_obj.name,(yytext));return bitxor;}
"<<"              {strcpy(yylval.nd_obj.name,(yytext));return leftshift;}
">>"              {strcpy(yylval.nd_obj.name,(yytext));return rightshift;}
">>>"              {strcpy(yylval.nd_obj.name,(yytext));return urightshift;}
"~"              {strcpy(yylval.nd_obj.name,(yytext));return bitcomp;}

"&&"              {strcpy(yylval.nd_obj.name,(yytext));return and_1;}
"||"              {strcpy(yylval.nd_obj.name,(yytext));return or_1;}
"!"              {strcpy(yylval.nd_obj.name,(yytext));return not_1;}

"="              {strcpy(yylval.nd_obj.name,(yytext));return assignment;}
"+="              {strcpy(yylval.nd_obj.name,(yytext));return asnaddn;}
"-="              {strcpy(yylval.nd_obj.name,(yytext));return asnsub;}
"*="              {strcpy(yylval.nd_obj.name,(yytext));return asnmul;}
"/="              {strcpy(yylval.nd_obj.name,(yytext));return asndiv;}
"&="              {strcpy(yylval.nd_obj.name,(yytext));return asnand;}
"|="              {strcpy(yylval.nd_obj.name,(yytext));return asnor;}
"^="              {strcpy(yylval.nd_obj.name,(yytext));return asnxor;}
"%="              {strcpy(yylval.nd_obj.name,(yytext));return asnmod;}
"<<="              {strcpy(yylval.nd_obj.name,(yytext));return asnls;}
">>="              {strcpy(yylval.nd_obj.name,(yytext));return asnrs;}
">>>="              {strcpy(yylval.nd_obj.name,(yytext));return asnurs;}





"?"              {strcpy(yylval.nd_obj.name,(yytext));return questionmark;}
":"              {strcpy(yylval.nd_obj.name,(yytext));return colon;}


{IDENTIFIER}             {strcpy(yylval.nd_obj.name,(yytext));return identifier; }


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

