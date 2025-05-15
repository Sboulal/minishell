📋 Overview
minishell is a custom shell implementation that replicates core functionalities of bash. This project demonstrates advanced C programming concepts including process creation, signal handling, and command parsing. The shell provides an interactive command-line interface with built-in commands and external program execution capabilities.
✨ Features

Command Execution - Run both built-in commands and external programs
Input/Output Redirection - Support for <, >, >> operators
Pipes - Connect commands with the | operator
Environment Variables - Access and modify environment with $VAR
Signal Handling - Proper handling of ctrl-C, ctrl-D, and ctrl-\
Command History - Navigate through previous commands
Error Handling - Accurate error messages and return values

🛠️ Built-in Commands
 - echo : Display a line of text with option -n
 - cd : Change the current directory
 - pwd : Print working directory
 - export : Set environment variables
 - unset : Remove environment variables
 - env : Display environment variables
 - exit : Exit the shell with a status code

🚀 Installation
Prerequisites

GCC compiler
GNU Make
Readline library
# On Ubuntu/Debian
sudo apt-get install libreadline-dev

# On macOS with Homebrew
brew install readline

Compilation

# Clone the repository
git clone https://github.com/Nkhou/minishell.git
cd minishell

# Compile
make

# Run the shell
./minishell

📝 Usage Examples
# Basic command execution
$ ls -la

# Environment variables
$ echo $HOME
$ export NAME=value
$ echo $NAME

# Pipes
$ ls -l | grep .c | wc -l

# Redirections
$ echo "hello" > file.txt
$ cat < file.txt
$ ls >> file.txt

# Command sequences
$ echo hello ; ls -la

# Exit the shell
$ exit
🧠 Implementation Details
The project is structured into several key components:

Lexer & Parser: Tokenize and interpret command inputs
Executor: Handle command execution and process creation
Built-ins: Implement shell built-in commands
Redirections: Manage file descriptor operations
Signal Handler: Process Unix signals properly
Environment Manager: Handle environment variables

⚠️ Error Handling
The shell implements bash-like error handling:

Displays appropriate error messages
Sets correct exit status for commands
Handles syntax errors gracefully

🔄 Signal Behavior
 - ctrl-C :Interrupts current command (sends SIGINT)
 - ctrl-D Exits shell when line is empty (EOF)
 - ctrl-\ Does nothing in interactive mode, sends SIGQUIT to foreground process

📚 Resources

  - Bash Reference Manual : https://www.gnu.org/software/bash/manual/bash.html
  - POSIX Shell Standard : https://brennan.io/2015/01/16/write-a-shell-in-c/
  - POSIX Shell Standard : https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html

