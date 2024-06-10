# Minishell 🐚

[![Twitter Follow](https://x.com/Lilien_RIG)

Minishell is a simplified [Bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)) shell environment capable of parsing commands and launching executables with arguments, plus several built-in functions. 🚀

## How to use it :
#### (Works only on Mac or Linux)

```bash
# Clone the repository
git clone https://github.com/Lilien86/42-minishell.git

# Navigate to the project directory
cd minishell

# Build the project using Make
make

# Run minishell and enjoy (:
./minishell
```
## Features 🌟
- Executes commands from an absolute, relative, or environment PATH like `/bin/ls` or `ls`.
- Supports single and double quotes.
- Redirections and pipes (`>`, `>>`, `<<`, `<`, `|`).
- Handles environment variables (`$HOME`) and the return code (`$?`).
- Ctrl-C, Ctrl-\, and Ctrl-D are implemented to handle interrupts and exits.
- Built-in functions: `echo`, `pwd`, `cd`, `env`, `export`, `unset`, and `exit`.

## Credits
#### This project was made with [Yvann](https://x.com/yvann_mp4) in 3 months at [42 School](https://en.wikipedia.org/wiki/42_(school)).
- I was responsible for the parsing, environment variables, built-in functions, and signal handling.
- Lilien took care of the execution, heredoc, redirection and piping, input files.