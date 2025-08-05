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

![Project Banner](./images/flowchart_1.png)
![Project Banner](./images/flowchart_2.png)
![Project Banner](./images/flowchart_3.png)