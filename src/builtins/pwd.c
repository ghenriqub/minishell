/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:38 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/09 20:11:37 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_current_dir(void)
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

static void	print_pwd_error(void)
{
	write(STDERR_FILENO, "pwd: ", 5);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = get_current_dir();
	if (!cwd)
	{
		print_pwd_error();
		return (1);
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	return (0);
}
