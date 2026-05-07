# Hemat Programming Language Documentation

> A simple statically-typed language that compiles to C

### 1. Language Syntax
**Variables (let)**

```hm
let x = 5;
let name = "John";
```

Variables are immutable by default. Reassignment is allowed without let:

```hm
x = 10;
```

**Print**
```hm
print x;
print "Hello";
```

**If Statement**
```hm
if x > 5 then
    print "Greater";
endif;
```

**Loop**
```hm
loop
    if x == 0 then
        break;
    endif;
    x = x - 1;
endloop;
```

### Expressions
| Operator | Meaning                  |
|:---------|:-------------------------|
| +	       | Addition / Concatenation |
| -	       | Subtraction              |
| *	       | Multiplication           |
| / 	      | Division                 |
| ==	      | Equal                    |
| !=	      | Not equal                |
| >	       | Greater                  |
| <	       | Less                     |

**Example:**

```hm
let result = (5 + 3) * 2;
```

### 2. Building & Installation
**Prerequisites**

- C compiler (gcc, clang, or MSVC)

- make (optional)

**Build from source**
```bash
git clone https://github.com/n0sferatu09/The-Hemat-Language.git
cd hemat
make
```

**Install**

```bash
sudo make install   # Linux/macOS
```

**Windows**

Download hmc.exe and add to PATH.

### 3. Usage
**Transpile to C only**
```bash
hmc program.hm
# Output: program.c
```

**Compile to executable**
```bash
hmc program.hm --compile
# Uses default C compiler (gcc/clang/cl)
```

**Specify compiler**
```bash
hmc program.hm --compile --cc=clang -o myapp
```

**Options**

| Flag	      | Description           |
|:-----------|:----------------------|
| -o <file>	 | Output file name      |
| --compile	 | Compile to executable |
| --cc=<cc>	 | Specify C compiler    |
| -v	        | Verbose output        |

### 4. Example
**factorial.hm**
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

print "Factorial is: ";
print result;
```

**Compile and run**
```
hmc factorial.hm --compile
./factorial
```

**Output:**
```text
Factorial is: 120
```

### 5. Type System
| Type	    | C equivalent  |
|:---------|:--------------|
| integer	 | long long int |
| string	  | const char*   |

Types are inferred automatically:
```hm
let x = 5;      // integer
let y = "hello"; // string
```

Type mismatch is a semantic error:
```hm
let x = 5;
x = "world";  // Error!
```
