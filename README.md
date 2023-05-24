# monty

- Monty is a scripting language created in C programming language

- This project is an interpreter for monty bytecodes

- The extension of the script file is `.m`

## Build

- To build from source code

```sh
gcc -Wall -Werror -Wextra -pedantic -std=c89 -o monty *.c
```

## Examples

- Check the `/bytecodes` directory for example scripts

## Comments

```
# this is a comment
push 5 # this is another comment
```

## ByteCodes

### push

- pushes a value into the stack

- usage: `push <int>`
    - where `<int>` is an integer

### pall

- prints all the values in the stack from top to bottom

### pint

- prints the value at the top of the stack

### pop

- removes the value at the top of the stack

### swap

- swaps the top two elements of the stack

### add

- adds the top two elements of the stack

### nop

- doesn't do anything

### sub

- subtracts the top elements of the stack by the second top one

### div

- divides the second top element of the stack by the top one

### mul

- multiplies the second top element of the stack by the top one

### mod

- computes the rest of the division of the second top element of the stack by
the top one

### pchar

- prints the char at the top of the stack

### pstr

- prints the string starting at the top of the stack
