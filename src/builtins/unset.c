/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:40 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/13 15:53:38 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp);

/// @brief 
/// @param  
static void	print_unset_error(char *arg)
{
	ft_putstr_fd("unset: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": invalid parameter name\n", STDERR_FILENO);
}

/// @brief 
/// @param env 
/// @param command 
/// @return 
static int	find_command(char **env, char *command)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], command, ft_strlen(command)) == 0
			&& env[i][ft_strlen(command)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/// @brief 
/// @param command 
/// @param env 
static void	update_env(char *command, char ***env)
{
	int		i;
	int		j;
	char	**new_env;

	i = find_command(*env, command);
	if (i == -1)
		return ;
	new_env = malloc(sizeof(char *) * (env_size(*env) + 1));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], command, ft_strlen(command)))
			new_env[j++] = ft_strdup((*env)[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_free_split(*env);
	*env = copy_env(new_env);
	ft_free_split(new_env);
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
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/// @brief 
/// @param args 
/// @param env 
/// @return 
int	ft_unset(char **args, t_shell *shell)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!shell->env)
		return (1);
	if (!args[0])
		return (0);
	while (args[i])
	{
		if (!is_valid(args[i]))
		{
			print_unset_error(args[i]);
			status = 1;
		}
		else
			update_env(args[i], &shell->env);
		i++;
	}
	return (status);
}
