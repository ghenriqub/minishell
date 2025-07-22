/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:31:37 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/22 15:16:40 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MALLOC_ERROR "Error: failed in memory allocate\n"
# define INPUT_ERROR "Error: input incorrect\n"

# include "libft.h"
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>

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

// ====== Parser ======

// signals:
void	ft_handle_sigint(int sig);
void	ft_setup_signals(void);
// tokens:
t_token	*ft_tokenizer(t_shell *shell, char *line, char **env);
t_token	*ft_init_token(t_shell *shell, char *line);
t_type	ft_get_type(char *value);
char	*ft_get_value(t_shell *shell, const char *s, int *i);
int		ft_is_delimiter(char c);
// utils:
void	ft_free_tokens(t_token *token);
void	ft_error(t_token *token, char *message, int code);
t_shell	*ft_init_shell(t_shell *shell, char **env);
// call_builtins:
int		call_builtins(t_token *token, t_shell *shell, char **env);
char	**ft_array_struct(t_token *token);
int		ft_lstsize(t_token *token);
void	ft_free_split(char **arr);
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
int		ft_exit(char **args, t_shell *shell, t_token *token);
int		ft_export(char **args, t_shell *shell);
void	set_var(char *variable, char ***env);
int		ft_cd(char **args, t_shell *shell);
char	*get_target_dir(char **args, t_shell *shell);
void	update_pwd_env(char *old_pwd, char *new_pwd, t_shell *shell);

#endif
