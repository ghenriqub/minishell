/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:35 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/22 10:27:30 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 
/// @param env 
/// @param variable 
/// @return 
int	find_index(char **env, char *variable)
{
	int	i;
	int	len;

	len = ft_strlen(variable);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], variable, len) == 0
			&& (env[i][len] == '=' || !env[i][len]))
			return (i);
		i++;
	}
	return (-1);
}

/// @brief 
/// @param variable 
/// @return 
static char	*get_var(char *variable)
{
	int		i;
	char	*name;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, variable, i + 1);
	return (name);
}

/// @brief 
/// @param variable 
/// @param env 
static void	set_env(char *variable, char ***env)
{
	char	**new_env;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while ((*env)[size])
		size++;
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return ;
	while (i < size)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ft_strdup(variable);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
}

int	is_valid(char *str)
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
/// @param variable 
/// @param env 
void	set_var(char *variable, char ***env)
{
	char	*name;
	int		i;

	name = get_var(variable);
	i = find_index(*env, name);
	if (i != -1)
	{
		free((*env)[i]);
		(*env)[i] = ft_strdup(variable);
	}
	else
		set_env(variable, env);
	free(name);
}
