/* fb3-1计算器的声明部分 */

/* 与词法分析器的接口 */
extern int yylineno;
extern void yyerror(char *s, ...);
extern int yylex();

/* 抽象语法树中的节点 */
struct ast{
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct numval{
    int nodetype; /* 类型K 表明常量 */
    double number;
};

/* 构造抽象语法树 */
extern struct ast *newast(int nodetype, struct ast *l, struct ast *r);
extern struct ast *newnum(double d);

/* 计算抽象语法树 */
extern double eval(struct ast *a);

/* 删除和释放抽象语法树 */
extern void treefree(struct ast *a);
