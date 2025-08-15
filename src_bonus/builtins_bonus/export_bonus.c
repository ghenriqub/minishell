/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:35 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/05 15:46:56 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

/// @brief 
/// @param arg 
static void	print_export_error(char *arg)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
}

/// @brief 
/// @param str 
/// @return 
static int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/// @brief 
/// @param env 
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

/// @brief 
/// @param args 
/// @param shell 
/// @return 
int	ft_export(char **args, t_shell *shell)
{
	int		i;
	int		status;

	status = 0;
	i = 0;
	if (!args[i])
	{
		print_all(shell->env);
		return (0);
	}
	while (args[i])
	{
		if (!is_valid(args[i]))
		{
			print_export_error(args[i]);
			status = 1;
		}
		else
			set_var(args[i], &shell->env);
		i++;
	}
	shell->exit_status = status;
	return (status);
}
