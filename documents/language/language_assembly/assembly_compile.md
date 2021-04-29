##compile
### assembler as
```
as file.s -o file.o
```
#### as options
--32 | --x32 | --64
&nbsp;&nbsp;&nbsp;&nbsp;Select the word size, either 32 bits or 64 bits.
--gstabs
&nbsp;&nbsp;&nbsp;&nbsp;Generate stabs debugging information for each assembler line

### linker ld
```
ld file1.o file2.o -o file.out
ld  --dynamic-linker /usr/lib32/ld-linux.so.2 -m elf_i386  file1.o  file2.o -o file.out -lc
```
#### ld options
-m emulation
&nbsp;&nbsp;&nbsp;&nbsp;elf_i386  emulation i386
--dynamic-linker libpath
&nbsp;&nbsp;&nbsp;&nbsp;Set the name of the dynamic linker
-L searchdir
--library-path=searchdir
&nbsp;&nbsp;&nbsp;&nbsp;Add path searchdir to the list of paths that ld will search for archive libraries and ld control scripts.
-l namespec
--library=namespec
&nbsp;&nbsp;&nbsp;&nbsp;Add the archive or object file specified by namespec to the list of files to link.
