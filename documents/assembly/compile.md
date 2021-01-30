##编译
### 编译工具as
```
as file.s -o file.o
```
#### 参数
--32 64位机上编译成32位
--gstabs 生成调式信息

### 链接工具ld
```
ld file1.o file2.o -o file.out
ld  -dynamic-linker /usr/lib32/ld-linux.so.2 -m elf_i386  file1.o  file2.o -o file.out -lc
```
#### 参数
-m elf\_i386  64位机中的32位编译选项
-dynamic-linker libpath 库的路径
-l lib 库
