#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "fb3-1.h"

extern int yyparse (void);

struct ast *newast(int nodetype, struct ast *l, struct ast *r){
    struct ast *a = malloc(sizeof(struct ast));

    if(!a){
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *newnum(double d){
    struct numval *a = malloc(sizeof(struct numval));

    if(!a){
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->number = d;
    return (struct ast *)a;
}


double eval(struct ast *a){
    double v;   // 子树的计算结果

    switch (a->nodetype) {
    case 'K':
        v = ((struct numval *) a)->number;
        break;
    case '+':
        v = eval(a->l) + eval(a->r);
        break;
    case '-':
        v = eval(a->l) - eval(a->r);
        break;
    case '*':
        v = eval(a->l) * eval(a->r);
        break;
    case '/':
        v = eval(a->l) / eval(a->r);
        break;
    case '|':
        v = eval(a->l);
        v = fabs(v);
        break;
    case 'M':
        v = -eval(a->l);
        break;
    default:
        printf("internal error: bad node %c\n", a->nodetype);
        exit(1);
    }
    return v;
}

void treefree(struct ast *a){
    switch (a->nodetype) {
    case '+':
    case '-':
    case '*':
    case '/':
        treefree(a->r);
        /* fall through */
    case '|':
    case 'M':
        treefree(a->l);
        /* fall through */
    case 'K':
        free(a);
        break;
    default:
        printf("internal error: free bad node %c\n", a->nodetype);
        break;
    }
}

void yyerror(char *s, ...){
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main(void){
    printf("> ");
    return yyparse();
}
