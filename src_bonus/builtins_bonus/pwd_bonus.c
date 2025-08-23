/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/23 14:50:27 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*ft_grow_buffer(char *old, size_t old_size, size_t new_size)
{
	char	*new;

	new = malloc(new_size);
	if (!new)
	{
		free(old);
		return (NULL);
	}
	ft_memcpy(new, old, old_size);
	free(old);
	return (new);
}

/// @brief we just get the current directory with getcwd
/// @return the updated current working directory
char	*get_current_dir(void)
{
	char	*cwd;
	size_t	size;

	size = 1024;
	cwd = malloc(size);
	if (!cwd)
		return (NULL);
	while (getcwd(cwd, size) == NULL)
	{
		if (errno != ERANGE)
		{
			free (cwd);
			return (NULL);
		}
		if (size > 2147483647 / 2)
		{
			free (cwd);
			return (NULL);
		}
		cwd = ft_grow_buffer(cwd, size, size * 2);
		if (!cwd)
			return (NULL);
		size *= 2;
	}
	return (cwd);
}

static char	*get_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PWD=", 4))
			return (ft_strdup(envp[i] + 4));
		i++;
	}
	return (NULL);
}

/// @brief the built-in of the print working directory function
/// @param args the arguments received in the call
/// @return 0 = success, 1 = error
int	ft_pwd(char **args, char **envp)
{
	char	*cwd;

	(void)args;
	cwd = get_current_dir();
	if (!cwd)
	{
		cwd = get_pwd(envp);
		if (!cwd || ft_strlen(cwd) == 0)
		{
			ft_putendl_fd("pwd: error retrieving directory", STDERR_FILENO);
			return (1);
		}
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(cwd);
	return (0);
}
