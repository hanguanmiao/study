## 使用
### eval的用法
- eval command-line  
其中command－line是在终端上键入的一条普通命令行。然而当在它前面放上eval时，其结果是shell在执行命令行之前扫描它两次。如：  
pipe="|"  
eval ls $pipe wc -l  
shell第1次扫描命令行时，它替换出pipe的值｜，接着eval使它再次扫描命令行，这时shell把｜作为管道符号了。
- eval echo \$$# 取得最后一个参数  
如：cat last  
eval echo \$$#  
./last one two three four  
resule: four


### $*和$@的区别
$*和$@都表示传递给函数或脚本的所有参数，不被双引号("")包含时，都以"$1""$2"..."$n"的形式输出所有参数，  
但被双引号("")包含时，"$*"会将所有的参数作为一个整体，以"$1 $2 ... $n"的形式传输所有参数，  
"$@"会将各个参数分开，以"$1""$2"..."$n"的形式输出所有参数
``` 
#!/usr/bin/env bash
echo "\$*=" $*  
echo "\"\$*\"=" "$*"  

echo "\$@=" $@  
echo "\"\$@\"=" "$@"  

echo "print each param from \$*"  
for var in $*  
do    
    echo "$var"  
done  

echo "print each param from \$@"
for var in $@
do  
    echo "$var"
done

echo "print each param from \"\$*\""
for var in "$*"
do  
    echo "$var"
done

echo "print each param from \"\$@\""
for var in "$@"
do  
    echo "$var"
done
```

## 杂项
${PAGER:-more}	如果shell变量PAGER已经定义，且其值非空，则使用其值，否则使用字符串more

## 链接
[The Set Builtin](https://www.gnu.org/software/bash/manual/html_node/The-Set-Builtin.html)
