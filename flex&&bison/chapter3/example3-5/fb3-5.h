/* fb3-1计算器的声明部分 */

/* 与词法分析器的接口 */
extern int yylineno;
extern void yyerror(char *s, ...);
//extern int yylex();

/* 符号表 */
struct symbol{
    char *name; /* 变量名 */
    double value;
    struct ast *func;   /* 函数体 */
    struct symlist *syms;   /* 虚拟参数列表 */
};

/* 固定大小的简单的符号表 */
#define NHASH 9997
extern struct symbol symtab[NHASH];

extern struct symbol *lookup(char *sym);

/* 符号列表，作为参数列表 */
struct symlist{
    struct sysmbol *sym;
    struct symlist *next;
};

extern struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
extern void symlistfree(struct symlist *sl);

/* 节点类型
 * + - * / |
 * 0-7 比较操作符，位编码： 04等于， 02小于， 01大于
 * M 单目负数
 *

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
