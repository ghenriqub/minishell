/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:35 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/22 12:31:31 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	ft_print_line(char *line)
{
	int	i;

	i = 0;
	write(1, &line[i], 1);
	i++;
	while (line[i] && line[i - 1] != '=')
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

/// @brief the loop insife the export function
/// @param str[0] = equal sign
/// @param str[1] = command name
static void	ft_export_loop(char *arg, t_shell *shell, int *status)
{
	char	*str[2];

	str[0] = ft_strchr(arg, '=');
	if (str[0])
	{
		if (!is_valid(arg))
		{
			print_export_error(arg);
			*status = 1;
		}
		else if (*(str[0] + 1) == '\0')
		{
			str[1] = ft_substr(arg, 0, str[0] - arg);
			if (find_command(shell->env, str[1]) > 0)
				set_var(arg, &shell->env);
			free(str[1]);
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
