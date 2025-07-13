/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:22 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/13 15:36:54 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 
/// @param var 
/// @return 
static char	*target_error(char *var)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd(" not set\n", STDERR_FILENO);
	return (NULL);
}

/// @brief 
/// @param shell 
/// @param var 
/// @return 
static char	*get_env_var(t_shell *shell, const char *var)
{
	int		i;
	int		len;
	char	*env_var;

	i = 0;
	len = ft_strlen(var);
	if (!shell->env || !var)
		return (NULL);
	while (shell->env[i])
	{
		env_var = ft_strchr(shell->env[i], '=');
		if (env_var && (env_var - shell->env[i]) == len)
		{
			if (ft_strncmp(shell->env[i], var, len) == 0)
				return (env_var + 1);
		}
		i++;
	}
	return (NULL);
}

/// @brief 
/// @param args 
/// @param shell 
/// @return 
char	*get_target_dir(char **args, t_shell *shell)
{
	char	*target;
	char	*env_value;

	if (!args[0])
	{
		env_value = get_env_var(shell, "HOME");
		if (!env_value)
			return (target_error("HOME"));
		target = ft_strdup(env_value);
	}
	else if (ft_strncmp(args[0], "-", 1) == 0)
	{
		env_value = get_env_var(shell, "OLDPWD");
		if (!env_value)
			return (target_error("OLDPWD"));
		target = ft_strdup(env_value);
		ft_putstr_fd(target, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
		target = ft_strdup(args[0]);
	return (target);
}

/// @brief 
/// @param shell 
/// @param name 
/// @param path 
static void	set_env_var(t_shell *shell, char *name, char *path)
{
	char	*var;
	int		name_len;
	int		path_len;

	if (!name || !path || !shell)
		return ;
	name_len = ft_strlen(name);
	path_len = ft_strlen(path);
	var = malloc(sizeof(char) * (name_len + path_len + 2));
	if (!var)
		return ;
	ft_strlcpy(var, name, name_len + 1);
	ft_strlcat(var, "=", name_len + 2);
	ft_strlcat(var, path, name_len + path_len + 2);
	set_var(var, &(shell->env));
	free(var);
}

/// @brief 
/// @param old_pwd 
/// @param new_pwd 
/// @param shell 
void	update_pwd_env(char *old_pwd, char *new_pwd, t_shell *shell)
{
	if (old_pwd)
		set_env_var(shell, "OLDPWD", old_pwd);
	if (new_pwd)
		set_env_var(shell, "PWD", new_pwd);
	return ;
}
