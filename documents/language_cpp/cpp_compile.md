## compiler gcc
```
g++ -std=c++11 -Wall -Wextra -m32 CalcSum.
```
### gcc options
-m32
-m64
>Generate code for a 32-bit or 64-bit environment.

-c  
>Compile or assemble the source files, but do not link.

-E
>Stop after the preprocessing stage; do not run the compiler proper.

-g
>Produce debugging information in the operating system's native format (stabs, COFF, XCOFF, or DWARF).

-O such as O0,O1
>Optimize.

-S  
>Stop after the stage of compilation proper

-std=
>Determine the language standard.

-Wall
>This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.

-Wextra
>This enables some extra warning flags that are not enabled by -Wall.
