/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:31:37 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/09 19:58:11 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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
#			Parser				#
#################################
*/
//signals
void	ft_handle_sigint(int sig);
void	ft_setup_signals(void);
//tokens
t_token	*ft_tokenizer(char *line);
t_token	*ft_init_token(char *line);
t_type	ft_get_type(char *value);
char	*ft_get_value(const char *s, int *i);
int		ft_is_delimiter(char c);
//utils
void	ft_free_tokens(t_token *token);

#endif