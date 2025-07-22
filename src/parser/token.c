/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:25:51 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/22 14:46:33 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_init_token_2(t_shell *shell, t_token *head,
					char *line, int *i);
static void		ft_init_token_3(t_token **new, t_token **head,
					t_token **current);

/// @brief init token and call built functons
/// @param line is the param that user write
/// @param env ambient variable
/// @return the token created
t_token	*ft_tokenizer(t_shell *shell, char *line, char **env)
{
	t_token	*token;

	if (!line[0])
		return (NULL);
	token = ft_init_token(shell, line);
	if (!token)
	{
		printf(INPUT_ERROR);
	}
	else
	{
		if (!call_builtins(token, shell, env))
		{
			ft_putendl_fd(" command not found", STDERR_FILENO);
			shell->exit_status = 127;
		}
	}
	return (token);
}

/// @brief tokenization, alloc the memory and call functions for value and type
/// @param line is the user input
/// @return return token created or NULL if input is invalid
t_token	*ft_init_token(t_shell *shell, char *line)
{
	t_token	*head;
	t_token	*current;
	t_token	*new;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
		{
			new = ft_init_token_2(shell, head, line, &i);
			if (!new)
				return (NULL);
			ft_init_token_3(&new, &head, &current);
		}
	}
	return (head);
}

/// @brief if the atual character is a delimiter, created a token
/// 		else, call function get value.
/// @param new is a new node
/// @param head head to linked list
/// @param line input user
/// @param i interator that we used to walk string
/// @return return 0 for error or 1 if was been succeed
static t_token	*ft_init_token_2(t_shell *shell, t_token *head,
					char *line, int *i)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		ft_error(head, MALLOC_ERROR, 1);
	if ((line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '<' && line[*i + 1] == '<'))
	{
		new->value = ft_substr(line, *i, 2);
		(*i) += 2;
	}
	else if (ft_is_delimiter(line[*i]))
	{
		new->value = ft_substr(line, (*i), 1);
		(*i)++;
	}
	else
		new->value = ft_get_value(shell, line, i);
	if (!new->value)
	{
		ft_free_tokens(head);
		free(new);
		return (NULL);
	}
	return (new);
}

/// @brief call the get type and update current
/// @param new new node
/// @param head declare head, if it has not been declared
/// @param current variable used to walk inside list
static void	ft_init_token_3(t_token **new, t_token **head, t_token **current)
{
	(*new)->type = ft_get_type((*new)->value);
	(*new)->next = NULL;
	if (!*head)
	{
		*head = *new;
		*current = *new;
	}
	else
	{
		(*current)->next = *new;
		*current = *new;
	}
}
