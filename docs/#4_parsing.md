# Minishell - Parsing Design

This document describes the parsing phase of the Minishell project.  
It defines all steps required to transform user input into a structured, validated set of commands, ready for execution.

Parsing is the most critical stage for correctness and robustness.  
Any inconsistency, omission, or memory mishandling here will cascade into execution failures or undefined behaviour.

---

## 1. Goals of Parsing

- Convert the raw input string into structured data.
- Separate tokens accurately.
- Detect and report syntax errors before any execution attempt.
- Support expansions (variables, tildes) in a way consistent with Bash.
- Handle heredocs robustly.
- Produce a **command table** describing the entire pipeline.

---

## 2. Overview of the Parsing Pipeline

Parsing consists of the following sequential steps:

1. **Lexing**
2. **Expansion**
3. **Syntax Validation**
4. **Command Table Construction**

All steps must **fail gracefully**:  
- Free allocated memory.
- Return a clear error.
- Return control to the main REPL loop.

---

# 3. Step-by-Step Flow

---

## Step 1 - Lexing

**Objective:**  
Split input into a list of tokens while preserving context (e.g., quotes, operators).

**Actions:**

- Walk the input string **character by character**.
- Build tokens according to the following rules:
  - **Whitespace:** splits tokens when unquoted.
  - **Quotes (`'`, `"`):** preserve everything inside as a single token.
  - **Operators:** recognise as separate tokens, even unspaced:
    - `|`
    - `>`
    - `>>`
    - `<`
    - `<<`
- Store each token in a dynamically allocated list.
- Attach metadata:
  - Type (WORD, PIPE, REDIR_IN, REDIR_OUT, APPEND, HEREDOC)
  - Raw content (to be expanded later)
  - Quoting flags (to know whether expansion applies)

**Edge Cases to Handle:**

- Unclosed quotes → Syntax Error.
- Mixed quotes (`"some 'weird' text"`) → Valid, must be preserved.
- Consecutive operators without spaces (`a|b`) → must split correctly.
- Trailing operators (`echo hi |`) → must be detected later during validation.

---

## Step 2 - Expansion

**Objective:**  
Expand all special sequences in tokens:

- Environment variables (`$VAR`)
- Special variables (`$?`)
- Home directory (`~`), if unquoted and at start

**Rules:**

- **Quoted tokens:**
  - Single quotes `'...'`: No expansion.
  - Double quotes `"...$VAR..."`: Expand variables.
- **Unquoted tokens:**
  - Expand variables.
  - Expand `~`.
- After expansion, split expanded content if it contains unquoted spaces.
  - E.g.: `echo $PATH` → multiple tokens if `$PATH` contains spaces.

**Edge Cases:**

- `$` not followed by valid identifier → leave as is.
- Escaped `$` in double quotes (`"\$VAR"`) → leave `$VAR` unexpanded.
- `$?` must be replaced with last return code as string.
- Empty expansions (`VAR=""`) → may remove token or leave empty string token depending on context.

---

## Step 3 - Syntax Validation

**Objective:**  
Check the token list for invalid sequences.

**Examples of invalid syntax:**

- Operator at start: `| ls`
- Operator at end: `ls |`
- Consecutive pipes: `ls || cat`
- Misplaced redirection: `> | ls`
- Redirection without target: `ls >`
- Heredoc without delimiter: `cat <<`

**Actions:**

- Walk through the token list linearly.
- For each token:
  - If PIPE:
    - Ensure previous and next tokens are valid WORDs.
  - If REDIRECTION:
    - Ensure a WORD follows.
  - If HEREDOC:
    - Ensure a WORD delimiter follows.
- If any inconsistency is detected:
  - Print syntax error to `STDERR`.
  - Free the entire token list.
  - Abort parsing.

---

## Step 4 - Command Table Construction

**Objective:**  
Transform the validated token list into a structured Command Table.

**Structure of a Command:**

- Command Name
- Arguments Array
- Input Redirections:
  - Type (STDIN, FILE, HEREDOC)
  - Filename or heredoc delimiter
- Output Redirections:
  - Type (STDOUT, APPEND)
  - Filename
- Next pointer (for pipelines)

**Actions:**

- Iterate token list.
- For each segment between PIPE tokens:
  - Collect:
    - First WORD → command name.
    - Remaining WORDs → arguments.
    - Redirection tokens → fill redirection entries.
  - If HEREDOC:
    - Store delimiter.
    - Postpone content capture to execution preparation.
  - Allocate and populate Command struct.
- Link Commands in pipeline sequence.

**Edge Cases:**

- Multiple redirections:
  - Last occurrence takes precedence.
    - `echo hi > a > b` → `b` is used.
- Redirections interleaved with arguments:
  - `echo > file hi` → must still parse correctly.
- No command (e.g., `| cat`) → invalid.

---

# 4. Memory Management

Every allocation in parsing must be tracked carefully:

- Token list nodes
- Token content strings
- Command structs
- Argument arrays
- Redirection filenames

**Policy:**
- On any error or abort, free **all** memory before returning.
- After successful parsing, ownership of the Command Table is transferred to the Executor.

---

# 5. Error Reporting

Whenever an error is detected:

- Write clear messages to `STDERR`.
  - Examples:
    - `syntax error near unexpected token '|'`
    - `syntax error: unexpected end of input`
    - `unclosed quote`
- Do not attempt execution.
- Return control to the REPL loop.

---

# 6. Testing Recommendations

To verify robustness, test all of the following:

- Single commands:
  - `ls -l`
- Pipelines:
  - `ls | cat -e`
  - `cat | grep hi | sort`
- Redirections:
  - `ls > file`
  - `cat < input`
  - `echo hi >> file`
- Heredocs:
  - `cat << EOF`
- Quoting:
  - `echo "hi there"`
  - `echo 'single quotes'`
  - `echo "$USER"`
- Syntax errors:
  - `| ls`
  - `ls || cat`
  - `echo >`
  - `cat <<`
  - Unclosed quotes
- Variable expansion:
  - `echo $PATH`
  - `echo "$?"`
  - `echo ~`

---

# 7. Summary

Parsing is composed of these mandatory steps:

1. **Lex input** into tokens with full context (quotes, operators).
2. **Expand** variables and special sequences correctly.
3. **Validate** syntax rigorously.
4. **Build** a complete, linked Command Table.
5. **Free** all resources reliably on success or failure.
6. **Return** clear status to the REPL loop.

This design ensures our Minishell parser can handle real-world inputs, detect errors early, and prepare the Executor for correct behaviour.

---
