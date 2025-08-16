/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:35 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/16 15:05:32 by ghenriqu         ###   ########.fr       */
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
		if (ft_strnstr(args[i[0]], "=", ft_strlen(args[i[0]])))
		{
			if (!is_valid(args[i[0]]))
			{
				print_export_error(args[i[0]]);
				i[1] = 1;
			}
			else
				set_var(args[i[0]], &shell->env);
		}
		i[0]++;
	}
	shell->exit_status = i[1];
	return (i[1]);
}
