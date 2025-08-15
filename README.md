<h1 align="center">
  Common Core 42 - Minishell
</h1>

<p align="center">
<img src="https://github.com/Albertoocosta/42-Minishell/releases/download/img/prompt" width="900" hidth="150">
</P>
<p align="center">
    <b><i>This project is part of third milestone of the 42 cursus</i></b>
</p>
<h3 align="center">
    <a href="#-about">About</a>
    <span> · </span>
    <a href="#-features">Features</a>
    <span> · </span>
    <a href="#-usage">Usage</a>
    <span> · </span>
    <a href="#-architecture">Architecture</a>
    <span> · </span>
    <a href="#-references">References</a
</h3>

## 📖 About

The goal of minishell is to write a simple shell that behaves like bash for a subset of features. You’ll learn process creation/termination, file descriptors, signal handling, tokenization, parsing, and building a small but robust command interpreter.

In addition, It's worth  mentioning that I was able to work in a group on this project and, as a result, i learned several git tools.

🧐 Project Highlights

A prompt that displays while waiting for a new command.

Command history and line editing (via Readline).

Environment variable handling and expansion (e.g., $USER, $?).

Builtins implemented in-process for performance.

Execution of external programs with correct PATH resolution.

Pipes and redirections with proper file descriptor management.

Signal behavior that matches bash (as required by the subject).

## ✨ Features


Prompt & Loop

Interactive prompt, EOF handling

Colored prompt, fancy modes


Parsing

Tokenization, quotes '", escapes, $-expansion

Parentheses, logical ops && `


Redirections

<, >, >>, << (here-doc)

Aggregation, advanced error messages


Pipes

`cmd1

cmd2

cmd3`

N‑ary pipelines with robust cleanup


Builtins

echo, cd, pwd, export, unset, env, exit

alias (optional), history wrapper


Env

Inherit + modify env, SHLVL, $?

Export formatting alignment


Signals

SIGINT (Ctrl‑C), SIGQUIT (Ctrl-), SIGTERM

Custom handlers per context


Exec

PATH search, execve, status codes

Hash table cache for PATH lookups


## 🧱 Usage

Works on Linux and macOS.

To pull files ↙️

git clone https://github.com/<your-user>/<your-minishell-repo>.git
cd <your-minishell-repo>

To compile ↙️

make        # builds minishell
make bonus  # (if you separate bonus sources)

Cleanup ↙️

make clean   # remove objects
make fclean  # remove binaries
make re      # rebuild from scratch

Run ↙️

./minishell

After the make command, dependencies (like readline) must be available on your system. On macOS you may need brew install readline and update include/library paths in the Makefile.

🛠️ Tools

Action

Description


Prompt

Displays a prompt and waits for input


Line Editing

Edit with arrows, history navigation (via Readline)


Signals

Ctrl-C prints a new line and redisplays prompt; Ctrl-D exits when line is empty; Ctrl-\ is ignored in interactive mode


Quotes

Single quotes keep literal value; double quotes allow $ expansion


Expansion

$VAR, $? replaced by last exit status


Redirections

< read from file, > truncate write, >> append, << here-doc with delimiter


Pipes

Combine commands: `ls -l

grep ".c"

wc -l`

Builtins

echo [-n], cd [dir], pwd, export [KEY=VAL], unset [KEY], env, exit [status]


Exit Codes

Propagates child status and builtin semantics


Examples

# Run an external command
minishell$ ls -la

# Pipe and grep
minishell$ ps aux | grep minishell | wc -l

# Redirection and here-doc
minishell$ cat <<EOF > note.txt
hello
world
EOF

# Variables and quotes
minishell$ echo "Hello $USER, last status was $?"

# Builtins
minishell$ export PATH=/usr/bin:/bin
minishell$ cd src && pwd
minishell$ exit 42

Error Handling

Print clear messages to stderr (e.g., minishell: cd: no such file or directory).

Return the correct exit status (127: command not found, 126: cannot execute, etc.).

Close all file descriptors; avoid leaks on parse/exec errors.

## 🧠 Architecture
```markdown
minishell/
├── src/
│   ├── main.c              # init, loop, cleanup
│   ├── control.c            # display prompt, read line
│   ├── parser/             # build AST / pipeline structures
|    ├── execution/         # to treat the execution part
|       ├── redirect.c           # manage temporary files / pipes
│   ├── expander/           # env, tilde(optional), quotes
│   ├── exec/               # pipelines, redirs, execve
│   ├── builtins/           # echo, cd, pwd, export, unset, env, exit
│   ├── signals.c           # handlers for interactive vs child
│   └── utils/              # strings, lists, fd helpers, errors
├── include/
│   ├── minishell.h
│   └── ...
├── Makefile
└── README.md
```

Key Design Notes

Two execution contexts: parent (runs builtins that change state) vs. child (external commands).

AST or simple pipeline list: enough to represent sequences with redirs and pipes.

Signal policy: interactive parent handles SIGINT to redraw prompt; children restore default.

Here-docs: read with proper signal handling and optional temporary files.

Memory: clear all allocations between prompts; use a global context only if necessary and guarded.


## 📚 References

bash manual (for behavior reference within subject scope)

POSIX.1-2017 — Shell & Utilities (tokenization, exit codes)

GNU Readline — history & line editing

execve(2), fork(2), pipe(2), dup2(2), waitpid(2), signal(2)

termios(3) — terminal attributes (optional advanced prompt)

🏁 Acknowledgements

Inspired by the structure and presentation of my FdF project README.

Thanks to peers and 42 community for discussions, tests and reviews.

