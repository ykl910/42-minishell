# Minishell 🐚

## Overview  
Minishell is a simplified Unix shell built as part of the 42 curriculum. It supports executing commands, built-in functions, and essential shell features focusing on process management and signal handling.

## Features ✨  
- Execute standard Unix commands with arguments  
- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`  
- Support for environment variables  
- Input/output redirections (`>`, `<`, `>>`)  
- Pipes (`|`) to chain commands  
- Command chaining with `&&` and `||` including priority execution  
- Handling of quotes for strings and arguments  
- Wildcard (`*`) expansion for filenames  
- Signal handling for `Ctrl+C` and `Ctrl+D`  
- Basic syntax error detection  

## Usage 🚀  
Run the compiled `minishell` executable and enter commands as you would in a normal shell.

## Compilation 🛠️  
Use the provided Makefile with `make` to compile the project.

## Running the Shell  
Execute with `./minishell`.

## Notes ⚠️  
- Does not support advanced job control or scripting.  
- Designed as an educational project to understand shell internals.

## Author  
**ykl910** – 42 Paris student  
**A1astar** - 42 Paris student  
GitHub: [ykl910](https://github.com/ykl910) [A1astar](https://github.com/A1astar)

