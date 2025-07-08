# GNU Readline

## Functions for interactive entry (command line)

### readline
### rl_clear_history
### rl_on_new_line
### rl_replace_line
### rl_redisplay
### add_history

## Library

### libreadline

## Linking

### -lreadline

***

# Standard C Library (libc)

Classic functions C/Posix

## I/O and memory

### printf
### malloc
### free
### write
### access
### open
### read
### close
### strerror
### perror
### isatty
### ttyname
### ttyslot
### exit

## Processes and Signals

### fork
### wait
### waitpid
### wait3
### wait4
### signal
### sigaction
### sigemptyset
### sigaddset
### kill
### execve

## Files and directories

### stat
### lstat
### fstat
### unlink
### dup
### dup2
### pipe
### opendir
### readdir
### closedir

## Actual directory

### getcwd
### chdir

## Environment variables

### getenv

## Terminal control

### ioctl
### tcsetattr
### tcgetattr

***

# Termcap Library (libtermcap) | Terminfo (ncurses)

## Functions for terminal capabilities

### tgetent
### tgetflag
### tgetnum
### tgetstr
### tgoto
### tputs

## Library

### If termcap => -ltermcap

### If terminfo/ncurses => -lncurses || -ltinfo

