/* 识别计算器的记号 */
%option noyywrap nodefault yylineno reentrant bison-bridge
%option header-file="purecalc.lex.h"

%{
#include "purecalc.h"
#include "purecalc.tab.h"
%}
/* 浮点数指数部分 */
EXP ([Ee][+-]?[0-9]+)

%{
struct pcdata *pp = yyextra;
%}

%%

"+" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
";" |
"(" |
")" {return yytext[0];}

 /* 比较操作符，所有返回值都是CMP记号 */
">" {yylval->fn = 1; return CMP;}
"<" {yylval->fn = 2; return CMP;}
"<>" {yylval->fn = 3; return CMP;}
"==" {yylval->fn = 4; return CMP;}
">=" {yylval->fn = 5; return CMP;}
"<=" {yylval->fn = 6; return CMP;}

 /* 关键字 */
"if"    {return IF;}
"then"  {return THEN;}
"else"  {return ELSE;}
"while" {return WHILE;}
"do"    {return DO;}
"let"   {return LET;}

 /* 内置函数 */
"sqrt"  {yylval->fn = B_sqrt; return FUNC;}
"exp"  {yylval->fn = B_exp; return FUNC;}
"log"  {yylval->fn = B_log; return FUNC;}
"print"  {yylval->fn = B_print; return FUNC;}

 /* 名字 */
[a-zA-Z][a-zA-Z]* {yylval->s = lookup(yytext); return NAME;}


[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}?    { yylval->d = atof(yytext); return NUMBER;}

"//".*
[ \t]   /* 忽略空白字符 */

\\\n {printf("c> ");} /* 忽略续行符 */

 \n {return EOL;}

.  {yyerror("Mystery character %c\n", *yytext);}

%%
