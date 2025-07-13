/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_to_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:13:19 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/12 20:51:22 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief this function call ant builtin according to input
/// @param token tokens of the input
/// @param env variable ambient 
/// @return return 1 if succed, or 0 if is fail
int	call_builtins(t_token *token, t_shell *shell, char **env)
{
	char	**args;

	args = ft_array_struct(token);
	if (!ft_strncmp(token->value, "pwd", 3) && ft_strlen(token->value) == 3)
	{
		ft_pwd(args);
		ft_free_split(args);
		return (1);
	}
	if (!ft_strncmp(token->value, "echo", 4) && ft_strlen(token->value) == 4)
	{
		ft_echo(args, shell->exit_status);
		ft_free_split(args);
		return (1);
	}
	if (!ft_strncmp(token->value, "env", 3) && ft_strlen(token->value) == 3)
	{
		ft_env(args, shell->env);
		ft_free_split(args);
		return (1);
	}
	if(!ft_strncmp(token->value, "exit", 4) && ft_strlen(token->value) == 4)
	{
		ft_exit(args, shell);
		ft_free_split(args);
		return (1);
	}
	if(!ft_strncmp(token->value, "export", 6) && ft_strlen(token->value) == 6)
	{
		if (ft_export(args, shell))
			shell->exit_status = 1;
		ft_free_split(args);
		return (1);
	}
	if(!ft_strncmp(token->value, "unset", 5) && ft_strlen(token->value) == 5)
	{
		ft_unset(args, shell);
		ft_free_split(args);
		return (1);
	}
	return (0);
}

/// @brief This function create the array of the args,
/// 		but without the command name
///				exemple: "echo hello", return args[0] = hello
/// @param token struct where is the args.
/// @return array of the args.
char	**ft_array_struct(t_token *token)
{
	char	**args;
	int		i;
	int		len;

	len = ft_lstsize(token);
	i = 0;
	args = malloc(sizeof(char *) * len);
	if (!args)
		return (NULL);
	if (len == 1)
	{
		args[0] = NULL;
		return (args);
	}
	token = token ->next;
	while (token)
	{
		args[i] = ft_strdup(token->value);
		token = token->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

/// @brief free any array of the arrays
/// @param arr array of the arrays
void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
