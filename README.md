# minishell

A minimal Unix shell written in C, built as part of the 42 school curriculum.

## Overview

**minishell** is a lightweight shell that reproduces core Bash behaviours: reading user input with line-editing and history, parsing it into commands and redirections, expanding environment variables and quotes, and executing everything through pipes.

## Features

- Interactive prompt with line editing and command history (via **GNU Readline**)
- Environment variable expansion (`$VAR`, `$?`)
- Single-quote and double-quote handling
- Pipes (`|`) — unlimited chaining
- Redirections:
  - Input redirection (`<`)
  - Output redirection (`>`)
  - Append redirection (`>>`)
  - Here-document (`<<`)
- Built-in commands:
  | Command | Description |
  |---------|-------------|
  | `echo [-n]` | Print text to stdout |
  | `cd [path]` | Change the current directory |
  | `pwd` | Print the current working directory |
  | `export [name=value]` | Set or display environment variables |
  | `unset [name]` | Remove environment variables |
  | `env` | Print all environment variables |
  | `exit [n]` | Exit the shell with an optional status code |
- Signal handling: `Ctrl-C` (interrupt), `Ctrl-D` (EOF), `Ctrl-\` (ignored in interactive mode)

## Requirements

- GCC or Clang
- GNU Make
- GNU Readline library (`libreadline-dev` on Debian/Ubuntu)

## Building

```bash
make
```

This compiles the bundled **libft** and then links the `minishell` binary.

| Target  | Effect |
|---------|--------|
| `make` / `make all` | Build the binary |
| `make clean` | Remove object files |
| `make fclean` | Remove objects and the binary |
| `make re` | Full rebuild |

## Usage

```bash
./minishell
```

The shell starts an interactive loop displaying a prompt. Type commands exactly as you would in Bash:

```
<3 echo "Hello, world!"
Hello, world!
<3 ls -la | grep .c
<3 cat < file.txt >> output.txt
<3 export GREETING=hello
<3 echo $GREETING
hello
<3 exit
```

## Project Structure

```
minishell/
├── includes/
│   └── minishell.h       # Main header — structs, macros, prototypes
├── srcs/
│   ├── parse_*.c         # Tokeniser, quote/dollar/expand handling
│   └── exec_*.c          # Execution engine, pipes, builtins, redirections
├── libft/                # 42 standard C library (bundled)
├── Makefile
└── readline.supp         # Valgrind suppression file for Readline leaks
```

## Authors

- **lle-pier** — [lle-pier@student.42lyon.fr](mailto:lle-pier@student.42lyon.fr)
- **abolea**
