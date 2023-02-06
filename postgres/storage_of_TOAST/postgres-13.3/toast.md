## 相关内容

[关于heaptuple的存储](https://e.gitee.com/lotuseed/docs/834442/file/2070859?sub_id=6453748)

## 准备

插入数据
![image.png](https://foruda.gitee.com/images/1665985866663614386/132ce358_10017097.png)

## 解读

### main文件

![image.png](https://foruda.gitee.com/images/1665986037862587072/66c2e5cf_10017097.png)

![image.png](https://foruda.gitee.com/images/1665986390806461691/05576df7_10017097.png)

已经解读过的不再解读，从 0112 b94a 开始

01表示TOAST pointer

12是18，表示VARTAG_ONDISK，类型为enum vartag_external

b94a0506是 va_rawsize，表示长度101010105

11a51f00是 va_extsize，表示长度2073873

ddd70e00是 va_valueid

d9d70e00是 va_toastrelid，表示toast oid为972761

> 说明:toast pointer固定为18个字节

### TOAST文件

![image.png](https://foruda.gitee.com/images/1665987578801049091/b2ff7b89_10017097.png)

1098 e00f 2090 e00f 3088 e00f 4080 e00f 表示四行数据

> 说明:每个page含有4个extern_tuple，由EXTERN_TUPLES_PER_PAGE定义

HeapTuple头部和main没有区别，不做说明。从ddd7 0e00开始

ddd7 0eaa 是同main中的va_valueid是一样的，用来标识是哪个attribute哪行的数据

0300 0000表示chunk_seq，chunk_seq是从0开始计数

401f开始就是vardata了
