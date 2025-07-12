/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:35 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/12 18:04:48 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


static void	print_all(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}


int	ft_export(char **args, char **env)
{
	int		i;
	int		status;

	status = 0;
	i = 0;
	if (!args[i])
	{
		print_all(env);
		return(0);
	}
	while (args[i])
	{
		if (!is_valid(args[i]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			status = 1;
		}
		else
			set_var(args[i], &env);
		i++;
	}
	return (status);
}
