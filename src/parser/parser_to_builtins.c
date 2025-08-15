/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_to_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:13:19 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/15 15:16:37 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_print_error(t_shell *shell, char *path, char *str, int code);

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
		shell->exit_status = (block->args + 1, shell->exit_status);
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
		if (!is_directory(block->args[0], shell))
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
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (ft_print_error(shell,
				path, ": No such file or directory", 127));
	else if (S_ISDIR(sb.st_mode))
		return (ft_print_error(shell, path, ": Is a directory", 126));
	else if (S_ISREG(sb.st_mode))
	{
		if (access(path, X_OK) == 0)
			return (0);
		else
			ft_print_error(shell, path, ": Permission denied", 126);
		return (1);
	}
	ft_print_error(shell, path, ": Not a directory", 127);
	return (1);
}

static int	ft_print_error(t_shell *shell, char *path, char *str, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(str, 2);
	shell->exit_status = code;
	return (1);
}
