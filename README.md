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
