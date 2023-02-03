## Heaptulple  
以postgres-13.3为例  

### 准备  
建表  
![image.png](https://github.com/hanguanmiao/study/blob/main/postgres/storage_structure_of_heaptuple/postgres-13.3/pictures/761dd704_10017097.png)

插入数据  
![image.png](https://github.com/hanguanmiao/study/blob/main/postgres/storage_structure_of_heaptuple/postgres-13.3/pictures/9b5e815a_10017097.png)

### 从文件中解读  

#### 头部  
![image.png](https://github.com/hanguanmiao/study/blob/main/postgres/storage_structure_of_heaptuple/postgres-13.3/pictures/538a34f3_10017097.png)
![image.png](https://github.com/hanguanmiao/study/blob/main/postgres/storage_structure_of_heaptuple/postgres-13.3/pictures/b81d961f_10017097.png)

到PageHeaderData->pd_linp 总共24个字节，  
24字节之后的a89f a200, 509f a800 分别指向第一行，第二行数据  
a89f a200 转换后为  00000000 10100010 10011111 10101000  -> 000000001010001 01 001111110101000  
000000001010001 表示长度 81， 01表示used,  001111110101000表示偏移量8104  

#### 数据  
![image.png](https://github.com/hanguanmiao/study/blob/main/postgres/storage_structure_of_heaptuple/postgres-13.3/pictures/26dd9ecc_10017097.png)
![image.png](https://github.com/hanguanmiao/study/blob/main/postgres/storage_structure_of_heaptuple/postgres-13.3/pictures/1c601743_10017097.png)

前23个字节为头部, 以bbbb这行数据为例  
bf2c 0000 0000 0000 0000 0000 分别是  t_xmin， t_xmax，t_cid  
0000 0000 0200 是  t_ctid，02指第二行数据  
0a00是t_infomask2，0a表示含有10个字段  
0308是t_infomask，08表示HEAP_XMAX_INVALID，03表示 HEAP_HASNULL | HEAP_HASVARWIDTH  
20是t_hoff，表示数据起始偏移量为32  
ff01是t_bits，表示第10个字段为空  
00 0000 0000 0000为padding  
0200 0000表示数值2  
0d62 6262 6262： 0d -> 00001101 表示长度占1个字节，总共长度为6  
0000为padding  

### 修改  
可以通过编辑文件修改数据内容  
![image.png](https://github.com/hanguanmiao/study/blob/main/postgres/storage_structure_of_heaptuple/postgres-13.3/pictures/357cbe2d_10017097.png)
