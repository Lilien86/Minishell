# 🖳 Minishell 

🌐[My Twitter account](https://x.com/Lilien_RIG)


The Minishell project is about building a simplified [Unix shell](https://en.wikipedia.org/wiki/Unix_shell#:~:text=A%20Unix%20shell%20is%20a,the%20system%20using%20shell%20scripts.), focusing on basic command execution, process management, and input/output handling to simulate core shell functionalities in a minimalistic style. 🚀

![Untitled](https://github.com/Lilien86/42-minishell/assets/125573483/247b1202-2b1b-4793-b0f5-031d8fd2cef7)

## How to use it :
#### (Works only on Mac or Linux) ⚠️

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
- Using all commands of the original shell.

## Sources
- [Minishell: Building a mini-bash](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
- [What is the Pipe is C](https://www.codequoi.com/en/pipe-an-inter-process-communication-method/)
- [Handling files descriptors](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
- [Understanding signals](https://medium.com/@razika28/signals-ad83f38f80b6)
## Credits
#### This project was made with [Yvann](https://x.com/yvann_mp4) in 3 months at [42 School](https://en.wikipedia.org/wiki/42_(school)).
- I was responsible for the execution, redirection, multi pipes, here doc, and handleing files descriptor.
- Yvann took care of the parsing, tokenise, signals and builtins.

#### You can find the subject publish on thsi web site
- [Subject](https://yannick.eu/content/files/2023/07/en.subject.minishell.pdf)
