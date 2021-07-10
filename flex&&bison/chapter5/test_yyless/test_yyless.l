%{
char *cp = NULL;
int chars = 0;
%}

%%

\"[^"]*\" { /* 右边引号之前的字符是否是 \ */
            if(yytext[yyleng - 2] == '\\'){
                yyless(yyleng-1);   // 返回最后的引号
                yymore();           // 添加下一个字符串
            }else{
                cp = strdup(yytext); chars += strlen(yytext);
            }
        }

%%

int main(void){
    yylex();
    printf("%d, %s\n", chars, cp);

    return 0;
}
