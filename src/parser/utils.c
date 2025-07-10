/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:54:58 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/10 20:57:42 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief free struct
void	ft_free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = tmp;
	}
}

/// @brief function for errors
/// @param token token for free
/// @param message message error
/// @param code exit code
void	ft_error(t_token *token, char *message, int code)
{
	if (token)
		ft_free_tokens(token);
	ft_putendl_fd(message, 2);
	exit (code);
}

// provisorie function, we will delete it latter
char	*name_type(int type)
{
	if (type == 0)
		return ("WORD");
	if (type == 1)
		return ("PIPE");
	if (type == 2)
		return ("REDIRECT_IN");
	if (type == 3)
		return ("REDIRECT_OUT");
	if (type == 4)
		return ("APPEND");
	return ("HEREDOC");
}

// provisorie function, we will delete it latter
void	print_token(t_token *token)
{
	t_token	*current;
	int		i;

	current = token;
	i = 0;
	printf("------------------------\n");
	printf("-------TOKENS-----------\n");
	printf("------------------------\n");
	while (current)
	{
		printf("TOKEN[%d]\n", i);
		printf("value -> %s\n", current->value);
		printf("type -> %s\n", name_type(current->type));
		printf("-----------\n");
		i++;
		current = current->next;
	}
}
