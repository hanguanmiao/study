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

%token <subtok> EXISTS /* NOT EXISTS or EXISTS */

%token ADD ALL ALTER ANALIZE AND ANY AS ASC AUTO_INCREMENT
    BEFORE BIGINT BINARY BIT BLOB BOTH BY
    CALL CASCADE CASE CHANGE CHAR CHECK COLLATE COLUMN COMMENT CONDITION
    CONSTRAINT CONTINUE CONVERT CREATE CROSS CURRENT_DATE CURRENT_TIME
    CURRENT_TIMESTAMP CURRENT_USER CURSOR
    DATABASE DATABASES DATE DATETIME DAY_HOUR DAY_MICROSECOND DAY_MINUTE
    DAY_SECOND DECIMAL DELCARE DEFAULT DELAYED DELETE DESC DESCRIBE
    DETERMINISTIC DISTINCT DISTINCTROW DIV DOUBLE DROP DUAL
    EACH ELSE ELSEIF ENCLOSED END ENUM ESCAPED EXIT EXPLAIN FETCH FLOAT
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
%type <intval> table_references opt_inner_cross opt_outer
%type <intval> left_or_right opt_left_or_right_outer column_list
%type <intval> index_list opt_for_join

%type <intval> delete_opts delete_list
%type <intval> insert_opts insert_vals insert_vals_list
%type <intval> insert_asgn_list opt_if_not_exists update_opts update_asgn_list
%type <intval> opt_temporary opt_length opt_binary opt_uz enum_list
%type <intval> column_atts data_type opt_ignore_replace create_col_list

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
    ;

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
    ;

expr: expr IS NULLX {emit("ISNULL");}
    | expr IS NOT NULLX {emit("ISNULL"); emit("NOT");}
    | expr IS BOOL {emit("ISBOOL %d", $3);}
    | expr IS NOT BOOL {emit("ISBOOL %d", $4); emit("NOT");}
    | USERVAR ASSIGN expr {emit("ASSIGN @%s", $1); free($1);}
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
    | expr NOT IN '(' select_stmt ')' {emit("CMPALLSELECT 3");}
    | EXISTS '(' select_stmt ')' {emit("EXISTSSELECT"); if($1) emit("NOT");}
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

trim_ltb: LEADING {emit("NUMBER 1");}
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
    | expr NOT REGEXP expr {emit("REGEXP");emit("NOT");}
    ;

expr: CURRENT_TIMESTAMP {emit("NOW");}
    | CURRENT_DATE {emit("NOW");}
    | CURRENT_TIME {emit("NOW");}
    ;

expr: BINARY expr %prec UMINUS {emit("STRTOBIN");}
    ;

 /* 语句: select语句 */
stmt: select_stmt {emit("STMT");}
    ;

select_stmt: SELECT select_opts select_expr_list /* 简单的无数据表select */{
        emit("SELECTNODATE %d %d", $2, $3);}
    | SELECT select_opts select_expr_list /* 有数据表select */
        FROM table_references
        opt_where opt_groupby opt_having opt_orderby opt_limit
        opt_info_list {emit("SELECT %d %d %d", $2, $3, $5);}
    ;

opt_where: /* empty */
    | WHERE expr {emit("WHERE");}
    ;

opt_groupby: /* empty */
    | GROUP BY groupby_list opt_with_rollup {emit("GROUPBYLIST %d %d", $3, $4);}
    ;

groupby_list: expr opt_asc_desc {emit("GROUPBY %d", $2); $$=1;}
    | groupby_list ',' expr opt_asc_desc {emit("GROUPBY %d", $4); $$= $1+1;}
    ;

opt_asc_desc: /* empty */ {$$=0;}
    | ASC {$$=0;}
    | DESC {$$=1;}
    ;

opt_with_rollup: /* empty */ {$$=0;}
    | WITH ROLLUP {$$=1;}

opt_having: /* empty */
    | HAVING expr {emit("HAVING");}
    ;

opt_orderby: /* empty */
    | ORDER BY groupby_list {emit("LIMIT 1");}
    ;

opt_limit: /* empty */ | LIMIT expr {emit("LIMIT 1");}
    | LIMIT expr ',' expr {emit("LIMIT 2");}
    ;

opt_info_list: /* empty */
    | INTO column_list {emit("INTO %d", $2);}
    ;

column_list: NAME {emit("COLUMN %s", $1); free($1); $$=1;}
    | column_list ',' NAME {emit("COLUMN %s", $3); free($3); $$=$1+1;}
    ;

select_opts: {$$=0;}
    | select_opts ALL {
            if($1 & 01) yyerror("duplicate ALL option");
            $$ = $1 | 01;
        }
    | select_opts DISTINCT {
            if($1 & 02) yyerror("duplicate DISTINCT option");
            $$ = $1 | 02;
        }
    | select_opts DISTINCTROW {
            if($1 & 04) yyerror("duplicate DISTINCTROW option");
            $$ = $1 | 04;
        }
    | select_opts HIGH_PRIORITY {
            if($1 & 010) yyerror("duplicate HIGH_PRIORITY option");
            $$ = $1 | 010;
        }
    | select_opts STRAIGHT_JOIN {
            if($1 & 020) yyerror("duplicate STRAIGHT_JOIN option");
            $$ = $1 | 020;
        }
    | select_opts SQL_SMALL_RESULT {
            if($1 & 040) yyerror("duplicate SQL_SMALL_RESULT option");
            $$ = $1 | 040;
        }
    | select_opts SQL_BIG_RESULT {
            if($1 & 0100) yyerror("duplicate SQL_BIG_RESULT option");
            $$ = $1 | 0100;
        }
    | select_opts SQL_CALC_FOUND_ROWS {
            if($1 & 0200) yyerror("duplicate SQL_CALC_FOUND_ROWS option");
            $$ = $1 | 0200;
        }
    ;

select_expr_list: select_expr {$$=1;}
    | select_expr_list ',' select_expr {$$=$1+1;}
    | '*' {emit("SELECTALL"); $$=1;}
    ;

select_expr: expr opt_as_alias;

opt_as_alias: AS NAME {emit("ALIAS %s", $2); free($2);}
    | NAME {emit("ALIAS %s", $1); free($1);}
    | /* nil */
    ;

table_references: table_reference {$$=1;}
    | table_references ',' table_reference {$$=$1+1;}
    ;

table_reference: table_factor
    | join_table
    ;

table_factor: NAME opt_as_alias index_hint {emit("TABLE %s", $1); free($1);}
    | NAME '.' NAME opt_as_alias index_hint {emit("TABLE %s.%s", $1, $3);
                                             free($1); free($3);}
    | table_subquery opt_as NAME {emit("SUBQUERYAS %s", $3); free($3);}
    | '(' table_references ')' {emit("TABLEREFERENCES %d", $2);}
    ;

opt_as: AS
    | /* empty */
    ;

join_table: table_reference opt_inner_cross JOIN table_factor
        opt_join_condition {emit("JOIN %d", 100+$2);}
    | table_reference  STRAIGHT_JOIN table_factor {emit("JOIN %d", 200);}
    | table_reference  STRAIGHT_JOIN table_factor ON expr {emit("JOIN %d", 200);}
    | table_reference left_or_right opt_outer JOIN table_factor
        join_condition {emit("JOIN %d", 300+$2+$3);}
    | table_reference NATURAL opt_left_or_right_outer JOIN table_factor
        {emit("JOIN %d", 400+$3);}
    ;

opt_inner_cross: /* nil */ {$$=0;}
    | INNER {$$=1;}
    | CROSS {$$=2;}
    ;

opt_outer: /* nil */ {$$ = 0;}
    | OUTER {$$=4;}
    ;

left_or_right: LEFT {$$=1;}
    | RIGHT {$$=2;}
    ;

opt_left_or_right_outer: LEFT opt_outer {$$ = 1 + $2;}
    | RIGHT opt_outer {$$ = 2 + $2;}
    | /* empty */ {$$=0;}
    ;

opt_join_condition: /* nil */
    | join_condition
    ;

join_condition: ON expr {emit("ONEXPR");}
    | USING '(' column_list ')' {emit("USING %d", $3);}
    ;

index_hint: USE KEY opt_for_join '(' index_list ')' {
        emit("INDEXHINT %d %d", $5, 10+$3);}
    | IGNORE KEY opt_for_join '(' index_list ')' {
        emit("INDEXHINT %d %d", $5, 20+$3);}
    | FORCE KEY opt_for_join '(' index_list ')' {
        emit("INDEXHINT %d %d", $5, 30+$3);}
    | /* emtpy */
    ;

opt_for_join: FOR JOIN {$$=1;} | /* empty */ {$$=0;}
    ;

index_list: NAME {emit("INDEX %s", $1); free($1); $$=1;}
    | index_list ',' NAME {emit("INDEX %s", $3); free($3); $$=$1+1;}
    ;

table_subquery: '(' select_stmt ')' {emit("SUBQUERY");}
    ;

/* statement: delete statememt */
stmt: delete_stmt {emit("STMT");}
   ;

/* delete simple table */
delete_stmt: DELETE delete_opts FROM NAME opt_where opt_orderby opt_limit {
            emit("DELETEONE %d %s", $2, $4); free($4);}
    ;

delete_opts: delete_opts LOW_PRIORITY {$$ = $1 + 01;}
    | delete_opts QUICK {$$ = $1 + 02;}
    | delete_opts IGNORE {$$ = $1 + 04;}
    | /* nil */ {$$ = 0;}
    ;

 /* 多表删除，第一版 */
delete_stmt: DELETE delete_opts delete_list FROM table_references opt_where {
        emit("DELETEMULTI %d %d %d", $2, $3, $5);}
    ;

delete_list: NAME opt_dot_star {emit("TABLE %s", $1); free($1); $$=1;}
    | delete_list ',' NAME opt_dot_star {emit("TABLE %s", $3); free($3);
                                          $$=$1 + 1;}
    ;

opt_dot_star: /* nil */ | '.' '*'
    ;

 /* 多表删除，第二版 */
delete_stmt: DELETE delete_opts FROM delete_list USING table_references
        opt_where { emit("DELETEMULTI %d %d %d", $2, $4, $6);}
    ;

 /* statement: insert statement */
stmt: insert_stmt {emit("STMT");}
    ;

 /* INSERT INTO a(b,c) values (1,2),(3,DEFAULT) */
insert_stmt: INSERT insert_opts opt_into NAME opt_col_names VALUES
        insert_vals_list opt_ondupupdate {
        emit("INSERTVALS %d %d %s", $2, $7, $4); free($4);}
    ;

opt_ondupupdate: /* nil */
    | ONDUPLICATE KEY UPDATE insert_asgn_list {emit("DUPLICATE %d", $4);}
    ;

insert_opts: /* nil */ {$$=0;}
    | insert_opts LOW_PRIORITY {$$ = $1 | 01;}
    | insert_opts DELAYED {$$ = $1 | 02;}
    | insert_opts HIGH_PRIORITY {$$ = $1 | 04;}
    | insert_opts IGNORE {$$ = $1 | 010;}
    ;

opt_into: INTO /* nil */
    ;

opt_col_names: /* nil */
    | '(' column_list ')' {emit("INSERTCOLS %d", $2);}
    ;

insert_vals_list: '(' insert_vals ')' {emit("VALUES %d", $2); $$ = 1;}
    | insert_vals_list ',' '(' insert_vals ')' {emit("VALUES %d", $4);
                                                $$ = $1 + 1;}
    ;

insert_vals: expr {$$=1;}
    | DEFAULT {emit("DEFAULT"); $$ = 1;}
    | insert_vals ',' expr {$$ = $1 + 1;}
    | insert_vals ',' DEFAULT {emit("DEFAULT"); $$ = $1 + 1;}
    ;

 /* INSERT INTO a SET b=1,c=2 */
insert_stmt: INSERT insert_opts opt_into NAME SET insert_asgn_list
        opt_ondupupdate {emit("INSETASGN %d %d %s", $2, $6, $4); free($4); }
    ;

insert_asgn_list: NAME COMPARISON expr {
            if($2 != 4){
                yyerror("bad insert assignment to %s", $1);
                YYERROR;
            }
            emit("ASSIGN %s", $1);
            free($1);
            $$ = 1;
        }
    | NAME COMPARISON DEFAULT {
            if($2 != 4){
                yyerror("bad insert assignment to %s", $1);
                YYERROR;
            }
            emit("DEFUALT");
            emit("ASSIGN %s", $1);
            free($1);
            $$ = 1;
        }
    | insert_asgn_list ',' NAME COMPARISON expr {
            if($4 != 4){
                yyerror("bad insert assignment to %s", $1);
                YYERROR;
            }
            emit("ASSIGN %s", $3);
            free($3);
            $$ = $1+1;
        }
    | insert_asgn_list ',' NAME COMPARISON DEFAULT {
            if($4 !=4){
                yyerror("bad insert assignment to %s", $1);
                YYERROR;
            }
            emit("DEFUALT");
            emit("ASSIGN %s", $3);
            free($3);
            $$ = $1 + 1;
        }
    ;

 /* INSERT into a(b,c) SELECT x,y FROM z where x < 12 */
insert_stmt: INSERT insert_opts opt_into NAME opt_col_names select_stmt
        opt_ondupupdate {emit("INSERTSELECT %d %s", $2, $4); free($4);}
    ;

 /* replace just like insert */
stmt: replace_stmt {emit("STMT");}
    ;

replace_stmt: REPLACE insert_opts opt_into NAME opt_col_names VALUES
        insert_vals_list opt_ondupupdate {
        emit("REPLACEVALS %d %d %s", $2, $7, $4); free($4);}
    | REPLACE insert_opts opt_into NAME SET insert_asgn_list opt_ondupupdate {
        emit("REPLACEASGN %d %d %s", $2, $6, $4); free($4);}
    | REPLACE insert_opts opt_into NAME opt_col_names select_stmt
        opt_ondupupdate {
        emit("REPLACESELECT %d %s", $2, $4); free($4);}
    ;

 /* update */
stmt: update_stmt {emit("STMT");}
    ;

update_stmt: UPDATE update_opts table_references SET update_asgn_list
        opt_where opt_orderby opt_limit {emit("UPDATE %d %d %d", $2, $3, $5);}
    ;

update_opts: /* nil */ {$$=0;}
    | update_opts LOW_PRIORITY {$$ = $1 | 01;}
    | update_opts IGNORE {$$ = $1 | 010;}
    ;

update_asgn_list: NAME COMPARISON expr {
            if($2 != 4) {
                yyerror("bad update assignment to %s", $1);
                YYERROR;
            }
            emit("ASSIGN %s", $1);
            free($1);
            $$ = 1;
        }
    | NAME '.' NAME COMPARISON expr {
            if($4 != 4) {
                yyerror("bad update assignment to %s.%s", $1, $3);
                YYERROR;
            }
            emit("ASSIGN %s.%s", $1, $3);
            free($1);
            free($3);
            $$ = 1;
        }
    | update_asgn_list ',' NAME COMPARISON expr {
            if($4 != 4) {
                yyerror("bad update assignment to %s", $3);
                YYERROR;
            }
            emit("ASSIGN %s", $3);
            free($3);
            $$ = $1 + 1;
        }
    | update_asgn_list ',' NAME '.' NAME COMPARISON expr {
            if($6 != 4) {
                yyerror("bad update assignment to %s.%s", $3, $5);
                YYERROR;
            }
            emit("ASSIGN %s.%s", $3, $5);
            free($3);
            free($5);
            $$ = 1;
        }
    ;

 /* create database */
stmt: create_database_stmt {emit("STMT");}
    ;

create_database_stmt:
    CREATE DATABASE opt_if_not_exists NAME
        {emit("CREATEDATABASE %d %s", $3, $4); free($4);}
    | CREATE SCHEMA opt_if_not_exists NAME
     {emit("CREATEDATABASE %d %s", $3, $4); free($4);}
    ;

opt_if_not_exists: /* nil */ {$$ = 0;}
    | IF EXISTS
        {
            if(!$2){
                yyerror("IF EXISTS doesn't exist");
                YYERROR;
            }
            $$ = $2;
        }
    ;

 /* create table */
stmt: create_table_stmt {emit("STMT");}
    ;

create_table_stmt:
    CREATE opt_temporary TABLE opt_if_not_exists NAME '(' create_col_list ')'
        { emit("CREATE %d %d %d %s", $2, $4, $7, $5); free($5);}
    | CREATE opt_temporary TABLE opt_if_not_exists NAME '.' NAME
        '(' create_col_list ')'
        { emit("CREATE %d %d %d %s.%s", $2, $4, $9, $5, $7); free($5);free($7);}
    | CREATE opt_temporary TABLE opt_if_not_exists NAME '(' create_col_list ')'
        create_select_statement
        { emit("CREATESELECT %d %d %d %s", $2, $4, $7, $5); free($5);}
    | CREATE opt_temporary TABLE opt_if_not_exists NAME create_select_statement
        { emit("CREATESELECT %d %d 0 %s", $2, $4, $5); free($5);}
    | CREATE opt_temporary TABLE opt_if_not_exists NAME '.' NAME
        '(' create_col_list ')' create_select_statement
        { emit("CREATESELECT %d %d %d %s.%s", $2, $4, $9, $7, $5);
          free($5); free($7);}
    | CREATE opt_temporary TABLE opt_if_not_exists NAME '.' NAME
        create_select_statement
        { emit("CREATESELECT %d %d 0 %s.%s", $2, $4, $7, $5);free($5);free($7);}
    ;

opt_temporary: /* nil */ {$$=0;}
    | TEMPORARY {$$=1;}
    ;

create_col_list: create_definition {$$ = 1;}
    | create_col_list ',' create_definition {$$ = $1 + 1;}
    ;

create_definition:
    PRIMARY KEY '(' column_list ')' {emit("PRIMARY %d", $4);}
    | KEY '(' column_list ')' {emit("KEY %d", $3);}
    | INDEX '(' column_list ')' {emit("KEY %d", $3);}
    | FULLTEXT INDEX '(' column_list ')' {emit("TEXTINDEX %d", $4);}
    | FULLTEXT KEY '(' column_list ')' {emit("TEXTINDEX %d", $4);}
    ;

create_definition: {emit("STARTCOL");} NAME data_type column_atts
        {emit("COLUMNDEF %d %s", $3, $2); free($2);}
    ;

column_atts: /* nil */ {$$ = 0;}
    | column_atts NOT NULLX {emit("ATTR NOTNULL"); $$=$1+1;}
    | column_atts NULLX
    | column_atts DEFAULT STRING {emit("ATTR DEFAULT STRING %s", $3); free($3);
                                  $$=$1+1;}
    | column_atts DEFAULT INTNUM {emit("ATTR DEFAULT NUMBER %d", $3); $$=$1+1;}
    | column_atts DEFAULT APPROXNUM {emit("ATTR DEFAULT FLOAT %g", $3);$$=$1+1;}
    | column_atts DEFAULT BOOL {emit("ATTR DEFAULT BOOL", $3); $$=$1+1;}
    | column_atts AUTO_INCREMENT {emit("ATTR AUTOINC"); $$=$1+1;}
    | column_atts UNIQUE '(' column_list ')' {emit("ATTR UNIQUEKEY %d", $4);
                                              $$=$1+1;}
    | column_atts UNIQUE KEY {emit("ATTR UNIQUE KEY"); $$=$1+1;}
    | column_atts PRIMARY KEY {emit("ATTR PRIMARY"); $$=$1+1;}
    | column_atts KEY {emit("ATTR PRIMARY"); $$=$1+1;}
    | column_atts COMMENT STRING {emit("ATTR COMMENT %s"); free($3); $$=$1+1;}
    ;

opt_length: /* nil */ {$$ = 0;}
    | '(' INTNUM ')' {$$ = $2;}
    | '(' INTNUM ',' INTNUM ')' {$$ = $2 + 1000*$4;}
    ;

opt_binary: /* nil */ {$$ = 0;}
    | BINARY {$$ = 4000;}
    ;

opt_uz: /* nil */ {$$ = 0;}
    | opt_uz UNSIGNED {$$ = $1 | 1000;}
    | opt_uz ZEROFILL {$$ = $1 | 2000;}
    ;

opt_csc: /* nil */
    | opt_csc CHAR SET STRING {emit("COLCHARSET %s", $4); free($4);}
    | opt_csc COLLATE STRING {emit("COLCOLLATE %s", $3); free($3);}
    ;

data_type:
    BIT opt_length {$$ = 10000 + $2;}
    | TINYINT opt_length opt_uz {$$ = 10000 + $2;}
    | SMALLINT opt_length opt_uz {$$ = 20000 + $2 + $3;}
    | MEDIUMINT opt_length opt_uz {$$ = 30000 + $2 + $3;}
    | INT opt_length opt_uz {$$ = 40000 + $2 + $3;}
    | INTEGER opt_length opt_uz {$$ = 50000 + $2 + $3;}
    | BIGINT opt_length opt_uz {$$ = 60000 + $2 + $3;}
    | REAL opt_length opt_uz {$$ = 70000 + $2 + $3;}
    | DOUBLE opt_length opt_uz {$$ = 80000 + $2 + $3;}
    | FLOAT opt_length opt_uz {$$ = 90000 + $2 + $3;}
    | DECIMAL opt_length opt_uz {$$ = 110000 + $2 + $3;}
    | DATE {$$ = 100001;}
    | TIME {$$ = 100002;}
    | TIMESTAMP {$$ = 100003;}
    | DATETIME {$$ = 100004;}
    | YEAR {$$ = 100005;}
    | CHAR opt_length opt_csc {$$ = 120000 + $2;}
    | VARCHAR '(' INTNUM ')' opt_csc {$$ = 130000 + $3;}
    | BINARY opt_length {$$ = 140000 + $2;}
    | VARBINARY '(' INTNUM ')' {$$ = 150000 + $3;}
    | TINYBLOB {$$ = 160001;}
    | BLOB {$$ = 160002;}
    | MEDIUMBLOB {$$ = 160003;}
    | LONGBLOB {$$ = 160004;}
    | TINYTEXT opt_binary opt_csc {$$ = 170000 + $2;}
    | TEXT opt_binary opt_csc {$$ = 171000 + $2;}
    | MEDIUMTEXT opt_binary opt_csc {$$ = 172000 + $2;}
    | LONGTEXT opt_binary opt_csc {$$ = 173000 + $2;}
    | ENUM '(' enum_list ')' opt_csc {$$ = 200000 + $3;}
    | SET '(' enum_list ')' opt_csc {$$ = 210000 + $3;}
    ;

enum_list:
    STRING {emit("ENUMVAL %s", $1); free($1); $$ = 1;}
    | enum_list ',' STRING {emit("ENUMVAL %s", $3); free($3); $$ =$1 + 1;}
    ;


create_select_statement: opt_ignore_replace opt_as select_stmt
        {emit("CREATESELECT %d", $1);}
    ;

opt_ignore_replace: /* nil */ {$$ = 0;}
    | IGNORE {$$ = 1;}
    | REPLACE {$$ = 2;}
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
