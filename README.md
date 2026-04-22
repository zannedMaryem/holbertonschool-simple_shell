# Simple SHELL

A basic Unix shell implementation in C, developed as a Holberton School project.

## Features

- Interactive command prompt (`#cisfun$`)
- PATH resolution for finding executables
- Handles Ctrl+D (EOF) gracefully
- Trim leading/trailing spaces from input

## Project Structure

| File | Description |
|------|-------------|
| `shell.h` | Header file with function declarations |
| `simple_shell.c` | Main shell loop and command execution |
| `get_path.c` | Retrieves PATH environment variable |
| `trim_spaces.c` | Removes leading/trailing whitespace |

## Build & Run

```bash
gcc -Wall -Werror -Wextra -pedantic -o hsh *.c
./hsh
```

## Current Status

- Basic shell loop implemented
- Input reading with `getline()`
- Prompt display for interactive mode
- EOF handling (Ctrl+D)
- pace trimming functionality
- PATH retrieval from environment
- Command execution (in progress)
