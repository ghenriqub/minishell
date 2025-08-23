/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:41:08 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/23 15:48:17 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/// @brief the last part of the heredoc function executed by parent and child
/// @param pid the pid of that process, the parent or child process
/// @param fd the list of pipes that were created in the main part
/// @param token the structure that holds the token that were submited
/// @return if ok, return 0
static int	else_heredoc(pid_t pid, int *fd, t_block *block)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
	{
		close(fd[0]);
		return (WTERMSIG(status));
	}
	block->heredoc_fd = fd[0];
	return (0);
}

/// @brief the function that holds the heredoc loop itself
/// @param fd the list of pipes that were created in the main part
/// @param limiter the EOF of the heredoc
/// @return if ok, return 0
static void	if_heredoc(int *fd, char *limiter, t_block *block, t_shell *shell)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd[1]);
			ft_free_all(block, shell);
			exit (0);
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	exit(0);
}

/// @brief the function that orchestrates the heredoc call in our minishell
/// @param token the structure that holds the token that were submited
/// @return if ok, return 0
int	ft_heredoc(t_block *block, char *limiter, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (!block || !limiter)
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		if_heredoc(fd, limiter, block, shell);
	else_heredoc(pid, fd, block);
	return (0);
}
