/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:11:48 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/06 13:52:30 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH=", 5))
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

char	*ft_found_path(char *cmd, char **envp)
{
	char	**path;
	char	*path_cmd;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	path = ft_split(get_path(envp), ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], "/");
		path_cmd = ft_join_free(path_cmd, cmd);
		if (access(path_cmd, X_OK) == 0)
		{
			ft_free_split(path);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	ft_free_split(path);
	return (NULL);
}
