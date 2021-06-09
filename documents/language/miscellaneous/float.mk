## float比较  
float比较用以下形式  
```
typedef struct{
    union{
        int i;
        float f;
    }val;
}value;
```
赋值给f,然后用i进行比较，如果差值小于1001(二进制)，则认为两者相等
