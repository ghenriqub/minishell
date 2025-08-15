/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:29 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/02 16:23:44 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/// @brief the standard error message of the wrong env call
/// @param arg the worng argument
static void	print_env_error(char *arg)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": too many arguments", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/// @brief calculates the size of env 
/// @param env the local variables of the system
/// @return i = size of env
int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/// @brief the built-in implementation of the env function
/// @param args the arguments we got in the readline
/// @param env the local variables of the system
/// @return 0 = success, 1 = error
int	ft_env(char **args, char **env)
{
	int	i;

	i = 0;
	if (args && args[0])
	{
		print_env_error(args[0]);
		return (1);
	}
	if (!env)
		return (0);
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
