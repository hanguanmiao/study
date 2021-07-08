/* 针对 mysql 子集的语法分析器 */
%{
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

extern int yylex();

void yyerror(char *s, ...);
void emit(char *s, ...);

%}

%union{
    int intval;
    double floatval;
    char *strval;
    int subtok;
}

 /*  名字和字面值 */
%token <strval> NAME
%token <strval> STRING
%token <intval> INTNUM
%token <intval> BOOL
%token <floatval> APPROXNUM

 /* 使用类似@abc的名字 */
%token <strval> USERVAR

 /* 操作符和优先级 */
%right ASSIGN
%left OR
%left XOR
%left ANDOP
%nonassoc IN IS LIKE REGEXP
%left NOT '!'
%left BETWEEN
%left <subtok> COMPARISON /* = <> < > <= >= <=> */
%left '|'
%left '&'
%left <subtok> SHIFT /* << >> */
%left '+' '-'
%left '*' '/' '%' MOD
%left '^'
%nonassoc UMINUS

%token ADD ALL ALTER ANALIZE AND ANY AS ASC AUTO_INCREMENT
    BEFORE BIGINT BINARY BIT BLOB BOTH BY
    CALL CASCADE CASE CHANGE CHAR CHECK COLLATE COLUMN COMMENT CONDITION
    CONSTRAINT CONTINUE CONVERT CREATE CROSS CURRENT_DATE CURRENT_TIME
    CURRENT_TIMESTAMP CURRENT_USER CURSOR
    DATABASE DATABASES DATE DATETIME DAY_HOUR DAY_MICROSECOND DAY_MINUTE
    DAY_SECOND DECIMAL DELCARE DEFAULT DELAYED DELETE DESC DESCRIBE
    DETERMINISTIC DISTINCT DISTINCTROW DIV DOUBLE DROP DUAL
    EACH ELSE ELSEIF ENCLOSED END ENUM ESCAPED EXISTS EXIT EXPLAIN FETCH FLOAT
    FOR FORCE FOREIGN FROM FULLTEXT
    GRANT GROUP
    HAVING HIGH_PRIORITY HOUR_MICROSECOND HOUR_MINUTE HOUR_SECOND
    IF IGNORE INDEX INFILE INNER INOUT INSENSITIVE INSERT INT INTEGER INTERVAL
    INTO INERATE
    JOIN
    KEY KEYS KILL
    LEADING LEAVE LEFT LIMIT LINES LOAD LOCALTIME LOCALTIMESTAMP LOCK LONG
    LONGBLOB LONGTEXT LOOP LOW_PRIORITY
    MATCH MEDIUMBLOB MEDIUMINT MEDIUMTEXT MINUTE_MICROSECOND
    MINUTE_SECOND MODIFIES
    NATURAL NO_WRITE_TO_BINLOG NULLX NUMBER
    ON ONDUPLICATE OPTIMIZE OPTION OPTIONALLY ORDER OUT OUTER OUTFILE
    PRECISION PRIMARY PROCEDURE PURGE
    QUICK
    READ READS REAL REFERENCES RELEASE RENAME REPEAT REPLACE REQUIRE RESTRICT
    RETURN REVOKE RIGHT ROLLUP
    SCHEMA SCHEMAS SECOND_MICROSECOND SELECT SENSITIVE SEPARATOR SET SHOW
    SMALLINT SOME SONAME SPATIAL SPECIFIC SQL SQLEXCEPTION SQLSTATE SQLWARNING
    SQL_BIG_RESULT SQL_CALC_FOUND_ROWS SQL_SMALL_RESULT SSL STARTING
    STRAIGHT_JOIN
    TABLE TEMPORARY TERMINATED TEXT THEN TIME TIMESTAMP TINYBLOB TINYINT
    TINYTEXT TO TRAILING TRIGGER
    UNDO UNION UNIQUE UNLOCK UNSIGNED UPDATE USAGE USE USING UTC_DATE UTC_TIME
    UTC_TIMESTAMP
    VALUES  VARBINARY VARCHAR VARYING
    WHEN WHERE WHILE WITH WRITE
    YEAR YEAR_MONTH
    ZEROFILL

%token FSUBSTRING FTRIM FDATE_ADD FDATE_SUB FCOUNT

%type <intval> select_opts select_expr_list
%type <intval> val_list opt_val_list case_list
%type <intval> groupby_list opt_with_rollup opt_asc_desc
%type <intval> table_references opt_inner_cross opt_user
%type <intval> left_or_right opt_left_or_right_outer column_list
%type <intval> index_list opt_for_join

%type <intval> delete_opts delete_list
%type <intval> insert_opts insert_vals insert_vals_list
%type <intval> insert_asgn_list opt_if_not_exists update_opts update_asgn_list

%start stmt_list

%%

stmt_list: stmt ';'
    | stmt_list stmt ';'
    ;

 /* 表达式 */
expr: NAME {emit("NAME %s", $1); free($1);}
    | NAME '.' NAME {emit("FIELDNAME %s.%s", $1, $3); free($1); free($3);}
    | USERVAR {emit("USERVAR %s", $1); free($1);}
    | STRING {emit("STRING %s", $1); free($1);}
    | INTNUM {emit("NUMBER %d", $1);}
    | APPROXNUM {emit("APPROXNUM %g", $1);}
    | BOOL {emit("BOOL %d", $1);}

expr: expr '+' expr {emit("ADD");}
    | expr '-' expr {emit("SUB");}
    | expr '*' expr {emit("MUL");}
    | expr '/' expr {emit("DIV");}
    | expr '%' expr {emit("MOD");}
    | expr MOD expr {emit("MOD");}
    | '-' expr %prec UMINUS {emit("NEG");}
    | expr ANDOP expr {emit("AND");}
    | expr OR expr {emit("OR");}
    | expr XOR expr {emit("XOR");}
    | expr '|' expr {emit("BITOR");}
    | expr '&' expr {emit("BITAND");}
    | expr '^' expr {emit("BITXOR");}
    | expr SHIFT expr {emit("SHITF %s", $2==1?"left":"right");}
    | NOT expr {emit("NOT");}
    | '!' expr {emit("NOT");}
    | expr COMPARISON expr {emit("CMP %d",$2);}
        /* 递归select和比较表达式 */
    | expr COMPARISON '(' select_stmt ')' {emit("CMPSELECT %d",$2);}
    | expr COMPARISON ANY '(' select_stmt ')' {emit("CMPANYSELECT %d",$2);}
    | expr COMPARISON SOME '(' select_stmt ')' {emit("CMPSOMESELECT %d",$2);}
    | expr COMPARISON ALL '(' select_stmt ')' {emit("CMPALLSELECT %d",$2);}

expr: expr IS NULLX {emit("ISNULL");}
    | expr IS NOT NULLX {emit("ISNULL"); emit("NOT");}
    | expr IS BOOL {emit("ISBOOL %d", $3);}
    | expr IS NOT BOOL {emit("ISBOOL %d", $4); emit("NOT");}
    | USERVAR ASSIGN expr {emit("ASSIGN @%s", $1); free($1)}
    ;

expr: expr BETWEEN expr AND expr %prec BETWEEN {emit("BETWEEN");}
    ;

val_list: expr {$$=1;}
    | expr ',' val_list {$$ = 1 + $3;}
    ;

opt_val_list: /* nil */ {$$=0;}
    | val_list
    ;

expr: expr IN '(' val_list ')' {emit("ISIN %d", $4);}
    | expr NOT IN '(' val_list ')' {emit("ISIN %d", $5); emit("NOT");}
    | expr IN '(' select_stmt ')' {emit("CMPANYSELECT 4");}
    | expr NOT IN '(' select_stmt ')' {emit("CMPALLSELECT 3")}
    | EXISTS '(' select_stmt ')' {emit("EXISTSSELECT");if($1)emit("NOT");}
    ;

 /* 常规函数 */
expr: NAME '(' opt_val_list ')' {emit("CALL %d %s", $3, $1); free($1);}
    ;

 /* 具有特殊语法的函数 */
expr: FCOUNT '(' '*' ')' {emit("COUNTALL");}
    | FCOUNT '(' expr ')' {emit("CALL 1 COUNT");}
    ;

expr: FSUBSTRING '(' val_list ')' {emit("CALL %d SUBSTR", $3);}
    | FSUBSTRING '(' expr FROM expr ')' {emit("CALL 2 SUBSTR");}
    | FSUBSTRING '(' expr FROM expr FOR expr ')' {emit("CALL 3 SUBSTR");}
    | FTRIM '(' val_list ')' {emit("CALL %d TRIM", $3);}
    | FTRIM '(' trim_ltb expr FROM val_list ')' {emit("CALL 3 TRIM");}
    ;

trim_lsb: LEADING {emit("NUMBER 1");}
    | TRAILING {emit("NUMBER 2");}
    | BOTH {emit("NUMBER 3");}
    ;

expr: FDATE_ADD '(' expr ',' interval_exp ')' {emit("CALL 3 DATE_ADD");}
    | FDATE_SUB '(' expr ',' interval_exp ')' {emit("CALL 3 DATE_SUB");}
    ;

interval_exp: INTERVAL expr DAY_HOUR {emit("NUMBER 1");}
    | INTERVAL expr DAY_MICROSECOND {emit("NUMBER 2");}
    | INTERVAL expr DAY_MINUTE {emit("NUMBER 3");}
    | INTERVAL expr DAY_SECOND {emit("NUMBER 4");}
    | INTERVAL expr YEAR_MONTH {emit("NUMBER 5");}
    | INTERVAL expr YEAR {emit("NUMBER 6");}
    | INTERVAL expr HOUR_MICROSECOND {emit("NUMBER 7");}
    | INTERVAL expr HOUR_MINUTE {emit("NUMBER 8");}
    | INTERVAL expr HOUR_SECOND {emit("NUMBER 9");}
    ;


 /* others */
expr: CASE expr case_list END {emit("CASEVAL %d 0", $3);}
    | CASE expr case_list ELSE expr END {emit("CASEVAL %d 1", $3);}
    | CASE case_list END {emit("CASE %d 0", $2);}
    | CASE case_list ELSE expr END {emit("CASE %d 1", $2);}
    ;

case_list: WHEN expr THEN expr {$$=1;}
    | case_list WHEN expr THEN expr {$$=$1+1;}
    ;

expr: expr LIKE expr {emit("LIKE");}
    | expr NOT LIKE expr {emit("LIKE"); emit("NOT");}
    ;

expr: expr REGEXP expr {emit("REGEXP");}
    | expr NOT REGEXP expr {emit("REGEXP");emit("NOT")}
    ;

%%
int main(int argc, char *argv[]){
    extern FILE *yyin;

    if(argc > 1 && !strcmp(argv[1], "-d")){
        yydebug = 1;
        --argc;
        ++argv;
    }

    if(argc > 1 && (yyin = fopen(argv[1], "r")) == NULL){
        perror(argv[1]);
        exit(1);
    }

    if(!yyparse()) printf("SQL parse worked\n");
    else printf("SQL parse failed\n");

    return 0;
}


void yyerror(char *s, ...){
    extern int yylineno;

    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

void emit(char *s, ...){
    va_list ap;
    va_start(ap, s);

    printf("rpn: ");
    vfprintf(stdout, s, ap);
    printf("\n");
}
