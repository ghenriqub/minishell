/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/21 11:52:39 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/// @brief we just get the current directory with getcwd
/// @return the updated current working directory
char	*get_current_dir(void)
{
	char	*cwd;
	char	*temp;
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
		size *= 2;
		temp = realloc(cwd, size);
		if (!temp)
		{
			free (cwd);
			return (NULL);
		}
		cwd = temp;
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
