# Minishell Architecture - Big Picture

**REPL = Read - Evaluate - Execute - Loop**

---

## Overview

This document describes the architecture and flow of the Minishell project. It is designed to be the central reference for development and testing. All phases of input handling, parsing, execution, and cleanup are covered.

**What breaks the loop:**
- explicit commands (`exit`)
- interruptions (`Ctrl+C`, `Ctrl+D`)

---

# 1. Shell Initialisation

After compiling the program and launching it, the shell performs any required environment preparation:

- load environment variables (`envp`)
- configure initial signal handlers
- prepare memory structures (history, command tables, etc.)

Then, the REPL loop starts.

---

# 2. REPL Loop

The REPL loop orchestrates all phases:

1. **READ** input from the user
2. **LEX and PARSE** the input
3. **EXECUTE** the parsed commands
4. **CLEAN UP** resources
5. Return to READ unless termination conditions are met

---

# 3. READ Phase

**Responsabilities:**

- Display the default prompt
- Collect user input
- Handle signals

**Steps:**

1. Display prompt (`$ ` or custom)
2. Wait for input
   - If input ends with `|`, display continuation prompt (`>`) and read the next line
   - If heredoc is detected, capture heredoc content
3. Save input line to history
4. Pass collected input to the next phase

**Signal behaviour:**

- `Ctrl+C` clears current line and redisplays prompt
- `Ctrl+D` exits shell if input is empty
- `Ctrl+\` ignored during input collection (like other `Ctrl+(etc)`)

---

# 4. LEX and PARSE Phase

This phase transforms raw text into structured commands.

**Sub-phases:**

## 4.1 Lexing

- Split the input into tokens
- Recognise special operators (`|`, `>`, `>>`, `<`, `<<`)
- Handle quotes and escape sequences

## 4.2 Expansion

- Expand environment variables (`$VAR`)
- Expand `~` (home directory)
- Remove quotes as needed

## 4.3 Parsing

- Build the Command Table:
  - Break pipelines into separate commands
  - Capture redirections (input/output)
  - Detect heredocs and prepare temp files
- Validate syntax:
  - Ensure operators are used correctly (e.g., no `| |` sequences)
  - Return error if inconsistencies are found
- If parsing fails:
  - Display error message
  - Return to READ phase

**Notes:**

- Parsing must discard extra whitespace (`' '`, `\t`)
- If heredocs are detected, collect their content here and store it for execution

---

# 5. EXECUTION Phase

This phase executes each pipeline.

**Steps:**

1. For each command in the pipeline:
   - Set up redirections:
     - Open files as needed
     - Prepare file descriptors
   - Create pipes between commands if applicable
2. Fork a new process for each command (except in specific builtin cases)
3. In the child process:
   - Apply redirections
   - Determine whether the command is:
     - A builtin
     - An executable in `$PATH`
     - A relative/absolute path
   - Execute the command:
     - If builtin:
       - Run builtin implementation
     - If external:
       - Call `execve` with resolved path
4. In the parent process:
   - Close unused pipe ends
   - Wait for all child processes to complete
5. Capture exit status of the last command:
   - Update `$?` accordingly

**Builtin considerations:**

- Some builtins (e.g., `cd`, `exit`) must be able to modify the shell state in the parent process and are not always executed in a fork.

**Error handling:**

- All errors must be printed to `STDERR`
- Syntax errors and execution errors must have clear messages
- Error redirection (`2>`) is not required (as per project spec)

---

# 6. CLEANUP Phase

After each command or pipeline execution:

- Free all allocated memory (tokens, command structures, heredoc buffers)
- Unlink heredoc temporary files
- Restore original file descriptors (stdin/stdout)
- Reset signals if modified

---

# 7. Loop

After cleanup:

- Return to the READ phase
- Continue until `exit` is involked or EOF (`Ctrl+D`) is received

---

# 8. Additional Considerations

**Signal handling per phase:**

- READ:
  - `Ctrl+C`: clear input line
  - `Ctrl+D`: exit if line empty
  - `Ctrl+\`: ignored
- EXECUTE:
  - `Ctrl+C`: send SIGINT to child processes
  - `Ctrl+\`: send SIGQUIT to child processes

**Memory management:**

- No memory leaks are tolerated
- Every malloc must have a corresponding free
- Any error or early return must clean up allocated resources

**Testing recommendations:**

- Compare behaviour to Bash in:
  - Normal commands
  - Pipelines
  - Redirections
  - Heredocs
  - variable expansion
  - Signal handling
- Validates `$?` correctness after each execution

**Flow Diagrams:**

If desired, diagrams can be created to illustrate transitions between phases and internal logic within each phase.

---

# 9. Summary

The flow of Minishell is as follows:

1. Initialise shell environment
2. REPL Loop begins:
   - READ input
   - LEX input into tokens
   - EXPAND variables and remove quotes
   - PARSE into command structures
   - EXECUTE commands (handling forks, redirections, builtins)
   - CLEAN UP memory and descriptors
   - Return to READ
3. Exit when termination conditions are met

This document serves as the guiding reference to ensure that all steps are implemented consistently and thoroughly.

---
