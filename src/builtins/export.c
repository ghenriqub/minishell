/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:35 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/16 17:17:40 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_line(char *line)
{
	int	i;

	i = 0;
	while (line[i - 1] != '=')
	{
		write(1, &line[i], 1);
		i++;
	}
	write(1, "\"", 1);
	while (line[i])
	{
		write(1, &line[i], 1);
		i++;
	}
	write(1, "\"\n", 2);
}

static void	print_export_error(char *arg)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}

static void	print_all(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_print_line(env[i]);
		i++;
	}
}

static void	ft_export_loop(char *arg, t_shell *shell, int *status)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		if (!is_valid(arg))
		{
			print_export_error(arg);
			*status = 1;
		}
		else if (*(equal + 1) == '\0')
		{
			if (find_command(shell->env, arg))
				set_var(arg, &shell->env);
		}
		else
			set_var(arg, &shell->env);
	}
	else if (!is_valid(arg))
	{
		print_export_error(arg);
		*status = 1;
	}
}

/// @param i[0] = iterator
/// @param i[1] = status
/// @return the status of the exit
int	ft_export(char **args, t_shell *shell)
{
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	if (!args[i[0]])
	{
		print_all(shell->env);
		return (0);
	}
	while (args[i[0]])
	{
		ft_export_loop(args[i[0]], shell, &i[1]);
		i[0]++;
	}
	shell->exit_status = i[1];
	return (i[1]);
}
