/* 基于抽象语法树的计算器 */
%{
#include <stdio.h>
#include <stdlib.h>
#include "fb3-1.h"
%}

%union{
    struct ast *a;
    double d;
}

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS UPOS

/* 声明记号 */
%token <d> NUMBER
%token EOL

%type <a> exp


%%
calclist: /* 空 */
    | calclist exp EOL {
            printf("= %4.4g\n", eval($2));
            treefree($2);
            printf("> ");
        }
    | calclist EOL { printf("> ");}   /* 空行或者注释 */
    ;

exp:  exp '+' exp { $$ = newast('+', $1, $3);}
    | exp '-' exp { $$ = newast('-', $1, $3);}
    | exp '*' exp { $$ = newast('*', $1, $3);}
    | exp '/' exp { $$ = newast('/', $1, $3);}
    | '|' exp '|' {$$=newast('|', $2, NULL);}
    | '(' exp ')' {$$=$2;}
    | '-' exp %prec UMINUS {$$ = newast('M', $2, NULL);}
    | '+' exp %prec UPOS {$$ = $2;}
    | NUMBER {$$ = newnum($1);}
    ;

%%

