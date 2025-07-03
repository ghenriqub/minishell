/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:50:52 by lgertrud          #+#    #+#             */
/*   Updated: 2025/05/21 15:32:54 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	shift_container(char *container, char *after_newline)
{
	size_t	i;

	i = 0;
	if (!container || !after_newline)
		return ;
	while (after_newline[i])
	{
		container[i] = after_newline[i];
		i++;
	}
	container[i] = '\0';
}

static char	*gett_line(char *container, char *line)
{
	char	*nl;
	size_t	len;
	char	*dup;
	char	*joined;

	if (!container)
		return (NULL);
	nl = ft_strchr(container, '\n');
	if (!nl)
		return (NULL);
	len = nl - container + 1;
	dup = ft_strndup(container, len);
	if (!dup)
	{
		if (line)
			free(line);
		return (NULL);
	}
	joined = ft_join_free(line, dup);
	free(dup);
	if (!joined)
		return (NULL);
	shift_container(container, nl + 1);
	return (joined);
}

static char	*ft_read(int fd, char *container, char *line)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, container, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		container[bytes_read] = '\0';
		if (ft_strchr(container, '\n'))
		{
			line = gett_line(container, line);
			return (line);
		}
		line = ft_join_free(line, container);
		if (!line)
			return (NULL);
		*container = '\0';
		bytes_read = read(fd, container, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	container[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (*container)
	{
		line = gett_line(container, NULL);
		if (line)
			return (line);
		line = ft_strndup(container, ft_strlen(container));
		if (!line)
			return (NULL);
		*container = '\0';
	}
	line = ft_read(fd, container, line);
	if (!line)
		return (NULL);
	if (*line)
		return (line);
	free(line);
	return (NULL);
}
