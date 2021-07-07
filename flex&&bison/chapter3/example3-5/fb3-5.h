/* fb3-1计算器的声明部分 */

/* 与词法分析器的接口 */
extern int yylineno;
extern void yyerror(char *s, ...);

/* 符号表 */
struct symbol{
    char *name; /* 变量名 */
    double value;
    struct ast *func;   /* 函数体 */
    struct symlist *syms;   /* 虚拟参数列表 */
};

/* 固定大小的简单的符号表 */
#define NHASH 9997
struct symbol symtab[NHASH];

extern struct symbol *lookup(char *sym);

/* 符号列表，作为参数列表 */
struct symlist{
    struct symbol *sym;
    struct symlist *next;
};

extern struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
extern void symlistfree(struct symlist *sl);

/* 节点类型
 * + - * / |
 * 0-7 比较操作符，位编码： 04等于， 02小于， 01大于
 * M 单目负数
 * L 表达式或者语句列表
 * I IF 语句
 * W WHILE 语句
 * N 符号引用
 * = 赋值
 * S 符号列表
 * F 内置函数调用
 * C 用户函数调用
 */
enum bifs{ /* 内置函数 */
    B_sqrt = 1,
    B_exp,
    B_log,
    B_print
};

/* 抽象语法树中的节点 */
/* 所有节点都有公共的初始nodetype */
struct ast{
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct fncall{ /* 内置函数 */
    int nodetype; /* 类型F */
    struct ast *l;
    enum bifs functype;
};

struct ufncall{ /* 用户自定义函数*/
    int nodetype; /* 类型C */
    struct ast *l; /* 参数列表 */
    struct symbol *s;
};

struct flow{
    int nodetype; /* 类型I或者W */
    struct ast *cond; /* 条件 */
    struct ast *tl; /* then分支或者do语句 */
    struct ast *el; /* 可选的 else 分支 */
};


struct numval{
    int nodetype; /* 类型K 表明常量 */
    double number;
};

struct symref{
    int nodetype; /* 类型 N */
    struct symbol *s;
};

struct symasgn{
    int nodetype; /* 类型 = */
    struct symbol *s;
    struct ast *v; /* 值 */
};

/* 构造抽象语法树 */
extern struct ast *newast(int nodetype, struct ast *l, struct ast *r);
extern struct ast *newcmp(int cmptype, struct ast *l, struct ast *r);
extern struct ast *newfunc(int functype, struct ast *l);
extern struct ast *newcall(struct symbol *s, struct ast *l);
extern struct ast *newref(struct symbol *s);
extern struct ast *newasgn(struct symbol *s, struct ast *v);
extern struct ast *newnum(double d);
extern struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl,
                           struct ast *el);

/* 定义函数 */
void dodef(struct symbol *name, struct symlist *syms, struct ast *func);

/* 计算抽象语法树 */
extern double eval(struct ast *a);

/* 删除和释放抽象语法树 */
extern void treefree(struct ast *a);
