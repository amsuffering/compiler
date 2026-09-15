# Compiler Project
who knows if i actually work on this

## Goal
Ok, technically this is an interpreter cause I don't wanna deal with writing real CPU instructions LOL. See [Back End](#back-end)

## Phases
Compilers are written in a front end, middle end, and back end.

### Front End
Roughly, this is going to contain a Lexical Analyzer, Syntax Analyzer, and Semantic Analyzer

#### Lexical Analysis
Also known as *scanning*. Convert a stream of input characters to Tokens.

#### Syntax Analysis
Also known as *parsing*. Uses tokens to create a syntax tree. Each node represents an operation and the children of a node represent the arguments of the parent operation.

#### Semantic Analyzer

### Middle End
IR Code generator and machine independent code optimization

### Back End
This is mainly where the difference in interpretor vs compiler are. Compilers will take the IR, do machine dependent optimizations, and then write CPU instructions. Interpretors, however, will simply compile to some platform independent code — like Java Bytecodes — and not do many of the optimizations.