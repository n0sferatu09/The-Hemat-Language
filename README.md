# The Hemat Language

> **Hemat** is a simple, statically-typed language that compiles to C

## Code Examples

### 1. Fibonacci numbers
```hm
let n = 10;
let a = 0;
let b = 1;
let i = 0;

print "Fibonacci: ";

loop
    if i == n then
        break;
    endif;
    print a;
    let temp = a + b;
    a = b;
    b = temp;
    i = i + 1;
endloop;

print "\n";
```

### 2. Sum of digits of a number
```hm
let n = 12345;
let sum = 0;

loop
    if n == 0 then
        break;
    endif;
    sum = sum + (n - (n / 10) * 10);
    n = n / 10;
endloop;

print "Sum of digits: ";
print sum;
print "\n";
```

### 3. Factorial
```hm
let n = 5;
let result = 1;

loop
    if n == 0 then
        break;
    endif;
        result = result * n;
        n = n - 1;
endloop;

print "Factorial is ";
print result;
print "\n";
```

## Installation

### Prerequisites
- C compiler (gcc, clang, or MSVC)
- CMake (version 3.20 or higher)

### Clone the repository
```bash
git clone https://github.com/n0sferatu09/The-Hemat-Language.git
cd The-Hemat-Language
```

### Build the compiler
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Add to PATH

#### Linux / macOS:
```bash
sudo cp build/hmc /usr/local/bin/
```

#### Windows (Command Prompt as Administrator):
```bash
mkdir C:\Tools
copy build\Release\hmc.exe C:\Tools\
setx PATH "%PATH%;C:\Tools" /M
```
After restarting your terminal, hmc will be available globally.

## Usage

Compile your .hm file using hmc
```bash
hmc program.hm
# Output: program.c
```

Then compile the generated C file with any C compiler:
```bash
hmc program.c -o program
./program
```
