/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_to_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:13:19 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/28 11:10:13 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief this function call ant builtin according to input
/// @param token tokens of the input
/// @param env variable ambient
/// @return return 1 if succed, or 0 if is fail
int	ft_call_builtins(t_block *block, t_shell *shell)
{
	if(!block->args || !block->args[0])
		return 0;
	if (!ft_strcmp(block->args[0], "pwd"))
		ft_pwd(block->args + 1);
	else if (!ft_strcmp(block->args[0], "echo"))
		ft_echo(block->args + 1, shell->exit_status);
	else if (!ft_strcmp(block->args[0], "env"))
		ft_env(block->args + 1, shell->env);
	else if (!ft_strcmp(block->args[0], "exit"))
		ft_exit(block->args + 1, shell, block);
	else if (!ft_strcmp(block->args[0], "export"))
		ft_export(block->args + 1, shell);
	else if (!ft_strcmp(block->args[0], "unset"))
		ft_unset(block->args + 1, shell);
	else if (!ft_strcmp(block->args[0], "cd"))
		shell->exit_status = ft_cd(block->args + 1, shell);
	else
		return (0);
	return (1);
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
