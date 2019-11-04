# InstantCompiler
Simple compiler of Instant language to JVM bitcode and LLVM bytecode.  
First task of MRJP course at MIMUW.

# Language
Instant is a simple language based on non-negative integers, arithmetical operations and variables.  
Non-context grammar of this language is described in src/Instant.cf file (BNF format).

# Used tools
* BNFC 2.8 for compiler front-end generating.

# Dependencies  
Dependencies of parser and lexer:  
* bison  
* flex  

C++:  
* gcc 5.2  
* make  

# Compilation
Type ```make``` in main directory of repository to create two executables - `insc_jvm` and `insc_llvm`.

# Usage
* ```./insc_jvm foo/bar/in.ins # to compile in.ins file in foo/bar directory```  

generates files in.j and in.java in foo/bar directory.  
* ```./insc_llvm foo/bar/in.ins # to compile in.ins file in foo/bar directory```  

generates files in.ll and in.bc in foo/bar directory.

# Repository structure
* InstantCompiler
    * src - contains source code of project
    * lib - contains jasmin.jar - tool for translation to JVM bytecode and runtime.bc - file with definitions of helper functions for LLVM bitcode execution
    * tests - contains *.ins and *.output files with desired output of Instant input

