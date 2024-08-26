Simple Shell Project - 0x16.c
Author: Abdelrhman Fikri
GitHub: abdelrhman2148

Overview
This project is a basic command interpreter (shell) written in C. It was developed as part of the intensive software engineering program at ALX_AFRICA School.

Synopsis
The simple_shell is a command-line program that reads user commands from the standard input and attempts to execute them using low-level system calls. It can either run built-in commands or search for executable files in the operating system.

Modes of Operation
Interactive Mode: The shell displays a prompt ($) where users can enter and execute commands. After each command is executed, the prompt reappears, ready for the next input. The shell continues running until the user exits.

Non-Interactive Mode: In this mode, commands are piped to the shell, and it executes them without displaying a prompt.

Examples
sh
Copy code
$ ./hsh
$ /bin/ls
main.c shell.c
$ exit
In Non-Interactive Mode:

sh
Copy code
$ echo "/bin/ls" | ./hsh
main.c shell.c
$ cat test_ls_2 | ./hsh
main.c shell.c
Exit Status
Upon exiting, simple_shell sets an exit status based on the last executed command:

0 - No errors encountered.
1 - General error.
2 - Misuse of shell built-ins.
126 - Command invoked cannot execute.
127 - Command not found.
130 - Script terminated by Control-D.
Command Input Format
Interactive Mode: Commands are typed when the prompt appears and executed upon pressing Enter. The program can be exited using CTRL + D. The CTRL + C signal is reserved for internal script termination and does not exit the shell.

Non-Interactive Mode: Commands need to be piped to the shell using echo or similar utilities.

Installation
To install the simple_shell, clone the repository from GitHub:

sh
Copy code
git clone https://github.com/abdelrhman2148/simple_shell.git
Authors
Abdelrhman Fikri
