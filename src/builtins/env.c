/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:29 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/10 21:16:20 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 
/// @param  
static void	print_env_error(char *arg)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": too many arguments", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/// @brief 
/// @param env 
/// @return 
int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/// @brief 
/// @param args 
/// @param env 
/// @return 
int	ft_env(char **args, char **env)
{
	int	i;

	i = 0;
	if (args[1])
	{
		print_env_error(args[1]);
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
