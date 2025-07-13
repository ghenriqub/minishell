/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:29 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/12 19:47:58 by lgertrud         ###   ########.fr       */
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
