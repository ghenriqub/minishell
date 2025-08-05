/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:07:49 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/05 14:11:22 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MALLOC_ERROR "Error: failed in memory allocate\n"
# define REDIREC_ERROR "bash: syntax error near unexpected token `newline'\n"
# define INPUT_ERROR "Error: input incorrect\n"
# define MINI "\001\033[0;36m\002minishell\001\033[0m\002$ "

# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <limits.h>
#include <sys/stat.h>

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC
}	t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	**args;
	char	**env;
	char	**history;
	int		exit_status;
}		t_shell;

typedef struct s_block
{
	char			**args;
	int				redirect_in;
	int				redirect_out;
	int				append;
	int				heredoc;
	int				heredoc_fd;
	char			**limits;
	char			**input;
	char			**output;
	struct s_block	*next;
}	t_block;

// ====== Parser ======

// tokens:
t_block	*ft_tokenizer(t_shell *shell, char *line, char **env);
t_block *ft_parse_blocks(t_token *tokens, t_shell *shell);
t_token	*ft_init_token(t_shell *shell, char *line);
t_type	ft_get_type(char *value);
char	*ft_get_value(t_shell *shell, const char *s, int *i);
int		ft_is_delimiter(char c);
int		ft_heredoc(t_block *block, char *limiter);
// utils:
void	ft_free_tokens(t_token *token);
void	ft_error(t_token *token, char *message, int code);
t_shell	*ft_init_shell(t_shell *shell, char **env);
char	**ft_copy_env(char **envp);
void	ft_free_blocks(t_block *head);
int		ft_have_something(char *line);
// call_builtins:
int		ft_call_builtins(t_block *block, t_shell *shell);
void	ft_free_split(char **arr);
int		is_directory(char *path, t_shell *shell);
// environment_variable
char	*ft_get_variable(char **env, char *part, int exit_status);
char	*get_env_value(char **env, const char *var_name);
char	*ft_concat(char *start, char *part, char *var_value, int i);
char	*ft_get_brace(char **env, char *part, char *start);

// ====== Exection ======

// built in:
int		ft_echo(char **args, int exit_status);
int		ft_pwd(char **args);
char	*get_current_dir(void);
int		ft_unset(char **args, t_shell *shell);
int		ft_env(char **args, char **env);
int		env_size(char **env);
int		ft_exit(char **args, t_shell *shell, t_block *block);
int		ft_export(char **args, t_shell *shell);
void	set_var(char *variable, char ***env);
int		ft_cd(char **args, t_shell *shell);
char	*get_target_dir(char **args, t_shell *shell);
void	update_pwd_env(char *old_pwd, char *new_pwd, t_shell *shell);
// execve:
void	ft_minishell(t_block *blocks, t_shell *shell);
void	ft_pipe_command(t_block *blocks, t_shell *shell);
void	ft_simple_command(t_block *blocks, t_shell *shell);
void	ft_simple_command_2(t_block *blocks, t_shell *shell,
			int fd_in, int fd_out);
char	*ft_found_path(char *cmd, char **envp);
int		ft_redirections(t_block *block, t_shell *shell);
int		ft_heredoc(t_block *block, char *limiter);

#endif
