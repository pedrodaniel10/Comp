# Comp 2017-2018
Compilers Project - Language GR8

## Introduction
GR8 is an imperative, typed and non-structured language. The objectives of the language is to allow
an easy reading, so is highly restrictive in respect to the aspect and position of the code (indentation).

The syntax of this language is meant as a parody of the Trump's 2016 campaign and his tweets, as
we can see from it's name (GR8 = Great).

The reference manual to this language is under the folder **/docs**

## Requirements 
You must have installed the following tools:
- **gcc** and **g++** compilers
- **flex** (version 2.6.1+)
- **byacc** (version 1.9+)
- **yasm** (version 1.3.0+)
- **ld** (version 2.28+)

The versions displayed above were the ones used in the develop phase. It doesn't mean that previous
versions don't work. 

## How to compile
The compilation of the project is just running the following command in the root directory:

```
    make
```

To clean:

```
    make clean
```

The program's binary will be placed under **/target**

## How to run
The following example shows a program with two modules: one that defines the function **factorial**
and another that defines the function **covfefe** (the main function)

Definition of the function **factorial** in the file named **factorial.gr8**:
```
define public small function factorial on small n as
    if n above 1 then
        return n times use n minus 1 for factorial
    else
        return 1
```

Example the use of the function **factorial** in the file **main.gr8**:
```
!! external builtin functions
public small function argc
public news function argv uses small number
public small function atoi uses news piece
 
!! external user functions
public small function factorial uses small number
 
!! the main function
define public small function covfefe as
    small value (initially 1)
    post "Teste para a função factorial"
    if do argc equals 2 then
        news flash (initially use 1 for argv)
        assign use flash for atoi to value
    tweet value
    tweet "! is "
    post use value for factorial
    return 0
```

How to compile:
```
    gr8 --target asm factorial.gr8
    gr8 --target asm main.gr8
    yasm -felf32 factorial.asm
    yasm -felf32 main.asm
    ld -melf_i386 -o main factorial.o main.o -lrts
```

## Run the tests
There are 107 test files under the folder **/tests**, to run them (compile -> execute -> diff with expected)
just run the script **run_tests.sh** that is present in the root directory (you might need to change the 
permissions to execute it).

## Debugging
### Compilation of the project
The compilation might fail if the following files dont have the permission to execute:
- /src/libcdk13-201802181144/mk-node-decls.pl
- /src/libcdk13-201802181144/mk-visitor-decls.pl

Just change the permissions by running the command:
```
    chmod +x <file name>
```
