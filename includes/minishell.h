/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:31:37 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/11 16:48:13 by lgertrud         ###   ########.fr       */
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

/*
#################################
#	    Parser		#
#################################
*/
//signals
void	ft_handle_sigint(int sig);
void	ft_setup_signals(void);
//tokens
t_token	*ft_tokenizer(char *line, char **env);
t_token	*ft_init_token(char *line);
t_type	ft_get_type(char *value);
char	*ft_get_value(const char *s, int *i);
int		ft_is_delimiter(char c);
//utils
void	ft_free_tokens(t_token *token);
void	ft_error(t_token *token, char *message, int code);
//call_builtins
int		call_builtins(t_token *token, char **env);
char	**ft_array_struct(t_token *token);
int		ft_lstsize(t_token *token);
void	ft_free_split(char **arr);


// ====== Exection ======

// built in:
int	ft_echo(char **args);
int	ft_pwd(char **args);
int	ft_unset(char **args, char **env);
int	ft_env(char **args, char **env);
int	env_size(char **env);


#endif
