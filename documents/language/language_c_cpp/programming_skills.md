##清理输入缓存  
scanf("%*[^\n]");scanf("%*c");  
丢弃除'\n'之外的所有字符，然后丢弃'\n'  

## goto,尽量不要用  
1. goto破会了代码的整洁性，使代码难以阅读		
2. goto造成代码难以测试		
3. 用法不当，goto会跳过变量的初始化以及计算，对程序造成隐患		
4. goto不可绕过变长数组    

## 分支选择优化  
\#define likely(x)	__builtin_expect(!!(x), 1)  
\#define unlikely(x)	__builtin_expect(!!(x), 0)  


## extension c  
[extension c](https://gcc.gnu.org/onlinedocs/gcc-5.5.0/gcc/Function-Attributes.html#Function-Attributes)
\_\_attribute\_\_
nonnull	参数不为空	example: __attribute__((nonnull(1))), 第一个参数不为空   
format (archetype, string-index, first-to-check)  
```
	extern int  
	my_printf (void *my_object, const char *my_format, ...)  
      __attribute__ ((format (printf, 2, 3)));  
```
returns_nonnull  
noreturn  
pure  
const  
unused  
constructor  
destructor  



## 旋转无符号整数
```
/* Rotate a uint32 value left by k bits - note multiple evaluation! */
#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))
```

## 8字节对齐
```
#define MAXIMUM_ALIGNOF 8

#define TYPEALIGN(ALIGNVAL,LEN)  \
	(((uintptr_t) (LEN) + ((ALIGNVAL) - 1)) & ~((uintptr_t) ((ALIGNVAL) - 1)))

#define MAXALIGN(LEN)			TYPEALIGN(MAXIMUM_ALIGNOF, (LEN))
```

## 杂项  
__thread	Thread Local Storage	线程局部存储，是每个线程分配一个变量实例
volatile,mutable

