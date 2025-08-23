/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:54:58 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/21 14:15:39 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

/// @brief this function counts how many nodes there are in a struct
/// @param env ambient variable
/// @return the count
int	ft_lstsize(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/// @brief this function create a copy of env whit memory alloc
/// @param envp envp
/// @return copy
char	**ft_copy_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_shell	*ft_init_shell(t_shell *shell, char **env)
{
	shell = malloc(sizeof(t_shell));
	shell->exit_status = 0;
	shell->env = ft_copy_env(env);
	shell->export = ft_copy_env(env);
	return (shell);
}
/*
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
*/