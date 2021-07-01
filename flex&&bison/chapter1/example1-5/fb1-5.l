/* 识别出用于计算器的记号并把他们输出 */

%{
#include "fb1-5.tab.h"
%}

%%
"+"     {return ADD;}
"-"     {return SUB;}
"*"     {return MUL;}
"/"     {return DIV;}
"|"     {return ABS;}
[0-9]+  {yylval = atoi(yytext); return NUMBER;}
\n      {return EOL;}
[ \t]   {}
.       {printf("Mystery character %c\n", *yytext);}

%%
