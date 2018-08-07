[![Codacy Badge](https://api.codacy.com/project/badge/Grade/2e8212e7eebd4db6b1cf0222be8dc477)](https://www.codacy.com?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=jllopes/uccompiler&amp;utm_campaign=Badge_Grade)

# Uc Compiler.

Compiler for a subset of the C language.

## Disclaimer

This project is not fully complete.
Code generation is not correctly implemented and semantic errors are not detected.

### Running the compiler

1. Lexical analisys
  
  ```
  $ ./uccompiler -l
  ```
  
  or
  
  ```
  $ ./uccompiler -1
  ```
  
2. Abstract Syntax Tree

  ```
  $ ./uccompiler -t
  ```

3. Syntax Analisys
  
  ```
  $ ./uccompiler -2
  ```

4. Semantic Analisys

  In this step the project will create the necessary Symbol Tables and annotate the AST.
  The project will only complete this step if there are no syntax errors in the code.

  ```
  $ ./uccompiler -s
  ```
  
5. Default
  
  If no flags are used, the project will create the symbol tables and generate the code.
