## C sample project

this project aims at understanding basic C project structure and how to use GCC on big C project

### Directory structure, took from [here](https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/)
- bin: executable files
- build: object files
- doc: document
- include: header files
- lib: libraries
- spike: random stuff
- src: project source code
- test: test files

----
### Simple compilation
with main.c in src

```
# create object file
# -c mean gcc only invokes the compiler to compile the C file into object file
gcc src/main.c -c -o build/main.o

# create bin file
# gcc knows that input file is .o, so it just invokes the linker
gcc build/main.o -o bin/main
```

### With function from other files
assume main.c use a function from lorem.c
lorem.c does not need to include lorem.h

```
# create object files
# use -Iinclude so that gcc knows where to look for the header (include)
# -I<dir> does NOT include recursively, use -I for every dir
# compilation step is done for each file separately
# because compiler can see 1 file each time
gcc src/lorem.c -c -o build/lorem.o -Iinclude
gcc src/main.c -c -o build/main.o -Iinclude

# link the object files
gcc build/main.o build/lorem.o -o bin/main
```

### Using static lib
create add lib as static library. The lib consists of src/add for source and include/add for header

```
# create lib object file
gcc src/add/add.c -c -o build/add/add.o

# create the static lib
# the lib name has to be lib<name>.a
ar rcs lib/add/libadd.a build/add/add.o

# using the lib
# like -I, -L does not search recursively
# -l<libname>
# -L<lib dir>
gcc build/main.o build/lorem.o -o bin/main -ladd -Llib/add
```

### Using dynamic library
```
# compile the lib files to object files
# -fPIC is positional independent code
gcc src/sub/sub.c -c -fPIC -o build/sub/sub.o

# create the lib file
# the lib name is lib<name>.so
gcc -shared build/sub/sub.o -o lib/sub/libsub.so
```

For dynamic linked, you need to set LD_LIBRARY_PATH env var to a dir that gcc can use to find the dynamic lib
```
LD_LIBRARY_PATH=$(pwd)/lib/sub ./bin/main
```

-----
### How linker work
There are 4 steps in GCC
- preprocessing (cpp): resolve macro
- compile C into assembly (gcc -S): turn C code into assembly
- turn assembly into binary opcode, object file (as): this and the previous step can be combined by `gcc -c`
- link the object files together (ld)

First 3 steps only have 1 input and 1 output, which mean they can process 1 file only at a time. The output object file is the same as the final executable file, except for unresolved external reference.
That is when the linker come into play. The linker find in the object file where is the placeholder value and the relocation infor in the .rela.text section, then it searches other files to find the correct address and replace the placeholder with the result

## Resources
https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
https://stackoverflow.com/a/33690144/9868917
https://cirosantilli.com/elf-hello-world