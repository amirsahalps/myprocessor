# mypreprocessor

A modular C preprocessor tool that processes C source files by performing comment removal, file inclusion, and macro substitution to generate an extended `.i` file.

## Features
* **Comment Removal:** Strips single-line (`//`) and multi-line (`/* ... */`) comments while preserving code structure.
* **File Inclusion:** Replaces `#include` directives with the contents of the specified file.
* **Macro Substitution:** Expands both simple object-like macros (`#define PI 3.14`) and parameterized function-like macros (`#define SQUARE(x) ((x)*(x))`).

## Build & Run

1. **Compile the project using Make:**
   ```bash
   make
   
 2.Run the preprocessor on a C source file:  
./mypreprocessor sample.c

 3.Output:
 This generates sample.i in the same directory.
