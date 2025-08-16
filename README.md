# Minishell

**Authors:** [lgertrud](https://github.com/Leandro-Gertrudes) && [ghenriqub](https://github.com/ghenriqub)
**Project:** Minishell - 42 School
**Objectiv:** Implement a command interpreter (*shell*) with a similar behavior of *bash*.

---

## 1. Introduction

**Minishell** is a 42 project which the main goal is to develop a command interpreter that accepts any user's entries, execute programs, and execute internal commands too (*builtins*).
Furthermore, it's necessary to deal with usual functionalities of shells, such as:

- External program executions
- Environment variables manipulation
- Pipes (`|`)
- Redirections (`>`, `<`, `>>`)
- Heredoc (`<<`)
- Command history
- Signal treatments (`CTRL+C`, `CTRL+D`, `CTRL+\`)

> This document serves as a **technical reference** and **study guide** to understand 100% of the project's internal functioning.

---

## 2. General Architecture

The **minishell**'s architecture follow a pipeline of **Entry -> Parser -> Executor -> Exit**.

### Principal Modules

1. **Entry**

   - `readline()` to capture commands.
   - History with `add_history()`.

2. **Parser**

   - `ft_tokenizer` -> Breaks the lines into *tokens* (`words`, `pipes`, `redirects`).
   - `ft_parse_blocks` -> Groups tokens into *blocks* (a command + metadata with redirects).
   - Substitution of environment variables.
   - Special treatment for *heredoc*.

3. **Executor**

   - Decides if executes **builtins** or **external programs**.
   - Implements simple executions, with pipes, and redirects.
   - Configures *file descriptors* before `execve`.

4. **Builtins**

   - Self implementions for:
     - `echo`
     - `pwd`
     - `cd`
     - `env`
     - `export`
     - `unset`
     - `exit`

5. **Memory Management**

   - Data structure:
     - `t_token` -> a *token* linked list.
     - `t_block` -> a *command block* linked list.
     - `t_shell` -> the shell's global status.
   - Auxiliar functions to free memory after each command.

---

## Execution Flow

The basic **minishell*'s cicle is:

1. **Show the prompt** -> `readline(MINI)`
2. **Read command**
   - If `NULL` (CTRL+D) -> finish shell.
3. **Tokenize command** (`ft_tokenizer`)
   - Identify *delimiters* (`|`, `<`, `>`, `<<`, `>>`)
   - Store each element in a `t_token` list.
4. **Create blocks** (`ft_parse_blocks`)
   - Groups tokens that belongs in the same command.
   - Configures redirects and heredocs.
5. **Execute command**
   - If builtin -> calls `ft_call_builtins`.
   - Otherwise -> looks for the path (`ft_found_path`) and executes with `execve`.
6. **Free memory** and goes back to the first step.

---

## 4. Parser in Details

The **parser** is responsible for interpret the string typed and transform it in internal manipulative structures.

### Key Structures

```C
typedef struct s_token
{
    char           *value;
    t_type         type;
    struct s_token *next;
}   t_token;

typedef struct s_block
{
    char            **args;
    int             redirect_in;
    int             redirect_out;
    int             append;
    int             heredoc;
    int             heredoc_fd;
    char            **limits;
    char            **input;
    char            **output;
    struct s_block  *next;
}   t_block;
```

### Parser's Main Functions

- `ft_tokenizer()`
  - Receives the whole line and returns the list of block (`t_block`).
- `ft_init_token()`
  - Creates tokens from the line using `ft_get_value` and `ft_get_type`.
- `ft_parse_blocks()`
  - Groups the tokens into commands, configuring redirects and heredocs.
- `ft_handle_heredoc()`
  - Creates a temporary file and writes the content until the *limiter* is inputed.

---

## 5. Executor in Detail

The **executor** decides how to run each command.

### Simple execution

- `ft_simple_command()` -> run a single command without pipe.
- Redirects `stdin` and/or `stdout` if necessary.
- Uses `execve` for external programs.

### Execution with pipes

- `ft_pipe_command()` -> manages multiple commands connected with `|`.
- Creates pipes with `pipe()`.
- Uses `fork()` for each command.
- Redirects input/output using `dup2()`.

### Redirects

- `ft_redirections()` -> open files for reading/writing.
- Configures `STDIN_FILENO` and `STDOUT_FILENO` before execution.

---

## 6. Builtins

The **builtins** are executed without creating a new process, if possible.

| Command | Function | Description |
| `echo` | `ft_echo` | Prints arguments |
| `pwd` | `ft_pwd` | Shows the current directory |
| `cd` | `ft_cd` | Changes the directory |
| `env` | `ft_env` | Lists the environment variables |
| `export` | `ft_export` | Defines an environment variable |
| `unset` | `ft_unset` | Removes an environment variable |
| `exit` | `ft_exit` | Closes shell |

---

## 7. Memory and Error Handling

### Cleaning Functions

- `ft_free_tokens` -> free the token list.
- `ft_free_blocks` -> free the block list.
- `ft_free_split` -> free the `char **` arrays.

### Error Handling

- `ft_error()` -> prints the error messages and defines the `exit_status`.
- Constants like `MALLOC_ERROR`, `INPUT_ERROR` centralize messages.

---

## 8. Exectution Example

### Entry

```bash
cat file.txt | grep hello > out.txt
```

### Tokenization
```bash
[T_WORD:cat] -> [T_WORD:file.txt] -> [T_PIPE] -> [T_WORD:grep] -> [T_WORD:hello] -> [T_REDIRECT_OUT] -> [T_WORD:out.txt]
```

### Blocks

Bloco 1: `args=["cat", "file.txt"], pipe_out = 1`
Bloco 2: `args=["grep", "hello"], redirect_out = out.txt`

### Execution

1. Creates a *pipe* between blocks 1 and 2.
2. `cat file.txt` write in pipe.
3. `grep hello` reads from pipe and writes in `out.txt`

---

## 9. Bonus

For an extra feature, we decided to also handle **&&** and **||** operators.

### &&

```bash
echo a && echo b
a
b
```

### ||
```bash
echo a || echo b
a
```

## 10. Compiling

```bash
make
./minishell
```

---
