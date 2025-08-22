/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:40 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/22 11:40:55 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief the standard error message of the unset command
/// @param arg the argument to be displayed 
static void	print_unset_error(char *arg)
{
	ft_putstr_fd("unset: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": invalid parameter name\n", STDERR_FILENO);
}

/// @brief the command finders, a ft_strcmp of the selected command
/// @param env the local variables
/// @param command the selected command
/// @return the index of the command, -1 in error
int	find_command(char **env, char *command)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], command, ft_strlen(command)) == 0
			&& (env[i][ft_strlen(command)] == '=' || !env[i][ft_strlen(command)]))
			return (i);
		i++;
	}
	return (-1);
}

/// @brief the split and update of the old variables into the updated
/// @param command the command that will be removed
/// @param env the local variables
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
		if (!(ft_strncmp((*env)[i], command, ft_strlen(command)) == 0
			&& ((*env)[i][ft_strlen(command)] == '=' || !(*env)[i][ft_strlen(command)])))
			new_env[j++] = ft_strdup((*env)[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_free_split(*env);
	*env = ft_copy_env(new_env);
	ft_free_split(new_env);
}

/// @brief we just verify the validity of the arguments
/// @param str the string that will be analyzed
/// @return 1 = is valid, 0 = not valid
static int	is_valid_unset(char *str)
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

/// @brief the built-in implementation of bash unset function 
/// @param args the arguments we received in the call
/// @param shell the shell structure with the env variables
/// @return the status of the update
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
		if (!is_valid_unset(args[i]))
		{
			print_unset_error(args[i]);
			status = 1;
		}
		else
		{
			update_env(args[i], &shell->env);
			update_env(args[i], &shell->export);
		}
		i++;
	}
	shell->exit_status = status;
	return (status);
}
