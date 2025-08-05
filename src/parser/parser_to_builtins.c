/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_to_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:13:19 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/05 13:45:34 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief this function call ant builtin according to input
/// @param token tokens of the input
/// @param env variable ambient
/// @return return 1 if succed, or 0 if is fail
int	ft_call_builtins(t_block *block, t_shell *shell)
{
	if (!block->args || !block->args[0])
		return (0);
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
	else if (ft_strchr(block->args[0], 47))
	{
		if(!is_directory(block->args[0], shell))
			return (0);
	}
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

int	is_directory(char *path, t_shell *shell)
{
	struct stat sb;

	if (stat(path, &sb) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		shell->exit_status = 127;
		return (1);
	}

	else if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
		shell->exit_status = 126;
		return (1);
	}

	else if (S_ISREG(sb.st_mode))
	{
		if (access(path, X_OK) == 0)
		{
			return (0);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": Permission denied", 2);
			shell->exit_status = 126;
		}
		return (1);
	}

	// Se não é dir nem arquivo comum
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": Not a directory", 2);
	shell->exit_status = 127;
	return (1);
}