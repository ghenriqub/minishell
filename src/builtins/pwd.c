/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/15 20:05:05 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/// @brief the standard error message of pwd function
static void	print_pwd_error(void)
{
	ft_putstr_fd("pwd: ", STDERR_FILENO);
	ft_putendl_fd("too many arguments", STDERR_FILENO);
}

/// @brief the built-in of the print working directory function
/// @param  the arguments received in the call
/// @return 0 = success, 1 = error
int	ft_pwd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = get_current_dir();
	if (ft_strlen(cwd) != ft_strlen(getenv("PWD")))
	{
		cwd = getenv("PWD");
		if (!cwd || ft_strlen(cwd) == 0)
		{
			ft_putendl_fd("pwd: error retrieving directory", STDERR_FILENO);
			return (1);
		}
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (cwd != getenv("PWD"))
		free(cwd);
	return (0);
}
