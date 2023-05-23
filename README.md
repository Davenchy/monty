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

- Check the `/bytecodes` directory for examples scripts

## ByteCodes

### push

- pushes a value into the stack

- usage: `push <int>`
    - where `<int>` is an integer

### pall

- prints all the values in the stack from top to bottom
