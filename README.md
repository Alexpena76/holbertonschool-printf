# _printf Implementation - Code Documentation

## Overview

This is a custom implementation of the C library function `printf`. The code provides a simplified version that handles basic format specifiers and produces formatted output to standard output.

## Code Structure

The implementation consists of 6 main functions organized in a modular design:

_printf()
↓
handle_format_specifier()
↓
├── print_character()
├── print_string()
├── print_percent()
└── print_integer()

## Function Documentation

### 1. `_printf(const char *format, ...)`
**Main entry point** - Parses format string and coordinates output

**Parameters**
- `format`: format string containing text and format specifiers
- `...`: Variable arguments corresponding to format specifiers

**Return:** Number of characters printed, or -1 if format is NULL

**Key Operations:**
- Validates format string
- Iterates through each character
- Identifies format specifiers (%)
- Tracks total character count

### 2. `handle_format_specifier(char specifier, va_list args)`
**Format dispatcher** - Routes format specifiers to appropriate handler functions.

**Parameters**
- `specifier`: The format character ('c', 's', '%', 'd', 'i')
- `args`: Variadic argument list

**Return** Number of characters printed by the handler

**Supported Specifiers:**
- `%c` → `print_character()`
- `%s` → `print_string()`  
- `%%` → `print_percent()`
- `%d` → `print_integer()`
- `%i` → `print_integer()`
- Unknown → Prints literally (`%z` → `%z`)

### 3. `print_character(va_list args)`
**Character handler** - Extracts and prints a single character.

**Algorithm**
1. Extract character from args (as int due to promotion)
2. Cast int back to char
3. Write character to stdout
4. Return 1 (character count)

**Key Type Conversion**
```c
char c = va_arg(args, int); // int → char conversion 
```

### 4. `print_string(va_list args)`
**String handler** - Extracts and prints a string character by character.

**Algorithm:**
1. Extract string pointer from args
2. Handle NULL case (prints "(null)")
3. Iterate through string characters
4. Write each character to stdout
5. Return character count

**Special Cases:**
- NULL pointer → prints "(null)" (6 characters)
- Empty string → prints nothing (0 characters)

### 5. `print_percent(void)`
**Percent handler** - Prints a literal percent sign.

**Simple function:**
- Writes '%' to stdout
- Returns 1

### 6. `print_integer(va_list args)`
**Integer handler** - Converts integers to string representation and prints them.

**Algorithm:**
1. Extract integer from args
2. Handle special cases (negative, zero, INT_MIN)
3. Extract digits and put them in an array in reverse order
4. Print negative sign if needed
5. Print digits in correct order
6. Return character count

**Special Cases:**
- **Zero**: Direct output "0"
- **Negative**: Print '-' then absolute value
- **INT_MIN (-2147483648)**: Special handling to avoid overflow

## Dependencies

- `<unistd.h>` - For `write()` system call
- `<stdarg.h>` - For variadic function support
- `<stdio.h>` - For testing 

## Usage Examples

```c
#include "main.h"

int main(void) {
    int count;
    
    // Basic string output
    count = _printf("Hello World\n");
    // Output: "Hello World\n", Returns: 12
    
    // Character formatting
    _printf("Grade: %c\n", 'A');
    // Output: "Grade: A\n"
    
    // String formatting
    _printf("Name: %s\n", "Alice");
    // Output: "Name: Alice\n"
    
    // Integer formatting
    _printf("Score: %d points\n", 95);
    // Output: "Score: 95 points\n"
    
    // Percent literal
    _printf("Progress: 100%%\n");
    // Output: "Progress: 100%\n"
    
    // Mixed formatting
    _printf("Student %s scored %d%% (%c grade)\n", "Bob", 87, 'B');
    // Output: "Student Bob scored 87% (B grade)\n"
    
    return 0;
}
```

# Inline code
C code

flowchart TD
    A["`**_printf(format, ...)**
    Start function`"] --> B{"`Is format 
    NULL?`"}
    
    B -->|Yes| C["`Return -1
    (Error)`"]
    
    B -->|No| D["`Initialize:
    • character_count = 0
    • i = 0
    • va_start(args, format)`"]
    
    D --> E{"`format[i] 
    != '\0'?`"}
    
    E -->|No| F["`va_end(args)
    Return character_count`"]
    
    E -->|Yes| G{"`format[i] 
    == '%'?`"}
    
    G -->|No| H["`write(1, &format[i], 1)
    character_count++
    i++`"]
    
    H --> E
    
    G -->|Yes| I["`i++`"]
    
    I --> J{"`format[i] 
    == '\0'?`"}
    
    J -->|Yes| K["`Break from loop`"]
    K --> F
    
    J -->|No| L["`**handle_format_specifier**
    (format[i], args)`"]
    
    L --> M{"`What is 
    specifier?`"}
    
    M -->|'c'| N["`**print_character(args)**
    • Extract: va_arg(args, int)
    • Cast: int → char
    • Write character
    • Return 1`"]
    
    M -->|'s'| O["`**print_string(args)**
    • Extract: va_arg(args, char*)
    • Handle NULL → '(null)'
    • Write each character
    • Return count`"]
    
    M -->|'%'| P["`**print_percent()**
    • Write '%'
    • Return 1`"]
    
    M -->|'d' or 'i'| Q["`**print_integer(args)**
    • Extract: va_arg(args, int)
    • Handle negatives & special cases
    • Convert to string
    • Write digits
    • Return count`"]
    
    M -->|Unknown| R["`Write '%' + specifier
    Return 2`"]
    
    N --> S["`Add result to 
    character_count
    i++`"]
    O --> S
    P --> S
    Q --> S
    R --> S
    
    S --> E
    
    %% Detailed print_integer subprocess
    Q --> Q1{"`num < 0?`"}
    Q1 -->|Yes| Q2{"`num == INT_MIN?`"}
    Q1 -->|No| Q4{"`num == 0?`"}
    
    Q2 -->|Yes| Q3["`Write '-2147483648'
    Return 11`"]
    Q2 -->|No| Q4A["`is_negative = 1
    num = -num`"]
    Q4A --> Q4
    
    Q4 -->|Yes| Q5["`Write '0'
    Return 1`"]
    Q4 -->|No| Q6["`Extract digits in reverse:
    digits[count] = (num % 10) + '0'
    num = num / 10`"]
    
    Q6 --> Q7{"`num > 0?`"}
    Q7 -->|Yes| Q6
    Q7 -->|No| Q8{"`is_negative?`"}
    
    Q8 -->|Yes| Q9["`Write '-'
    count++`"]
    Q8 -->|No| Q10["`Write digits in 
    reverse order`"]
    Q9 --> Q10
    
    Q10 --> Q11["`Return count`"]
    
    %% Style definitions
    classDef startEnd fill:#e1f5fe,stroke:#01579b,stroke-width:2px,color:#000
    classDef process fill:#f3e5f5,stroke:#4a148c,stroke-width:2px,color:#000
    classDef decision fill:#fff3e0,stroke:#e65100,stroke-width:2px,color:#000
    classDef function fill:#e8f5e8,stroke:#1b5e20,stroke-width:2px,color:#000
    classDef error fill:#ffebee,stroke:#c62828,stroke-width:2px,color:#000
    
    class A,F startEnd
    class D,H,I,K,S process
    class B,E,G,J,M,Q1,Q2,Q4,Q7,Q8 decision
    class L,N,O,P,Q function
    class C,R error