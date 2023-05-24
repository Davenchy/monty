# monty

- Monty is a scripting language created in C programming language

- This project is an interpreter for monty bytecodes

- The extension of the script file is `.m`

## Build

- To build from source code

```sh
gcc -Wall -Werror -Wextra -pedantic -std=c89 -o monty *.c
```

## Usage

```bash
./monty <script>
```

- example

```bash
./monty ./bytecodes/strings.m
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
- check example `00.m`

### pall

- prints all the values in the stack from top to bottom
- check example `00.m`

### pint

- prints the value at the top of the stack
- check example `06.m`

### pop

- removes the value at the top of the stack
- check example `07.m`

### swap

- swaps the top two elements of the stack
- check example `09.m`

### add

- adds the top two elements of the stack
- check example `arthm_ops.m`

### sub

- subtracts the top elements of the stack by the second top one
- check example `arthm_ops.m`

### div

- divides the second top element of the stack by the top one
- check example `arthm_ops.m`

### mul

- multiplies the second top element of the stack by the top one
- check example `arthm_ops.m`

### mod

- computes the rest of the division of the second top element of the stack by
the top one
- check example `arthm_ops.m`

### pchar

- prints the char at the top of the stack
- check example `strings.m, strings2.m`

### pstr

- prints the string starting at the top of the stack
- check example `strings.m, strings2.m`

### rotl

- rotates the stack to the __top__
- __The top__ element of the stack becomes ___the last one__,
and __the second top__ element of the stack becomes __the first one__
- check example `35.m`

### rotr

- rotates the stack to the __bottom__
- __The last__ element of the stack becomes __the top__ element of the stack
- check example `35.m`

### stack

- sets the format of the data to stack (Last In First Out).
- This is __the default behavior__ of the program.
- __On Switch__: the front of the queue becomes the top of the stack
- check example `47.m, 47_extra.m`

### queue

- sets the format of the data to queue (First In First Out).
- __On Switch__: the top of the stack becomes the front of the queue
- check example `47.m, 47_extra.m`

### nop

- No Operation - Do Nothing
