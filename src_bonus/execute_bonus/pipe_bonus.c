/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:00:50 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/16 18:04:06 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	ft_pipe_command(t_block *blocks, t_shell *shell)
{
	int		pipefd[2];
	int		in_fd;
	pid_t	pids[256];
	int		i;
	int		wstatus;

	i = 0;
	wstatus = 0;
	in_fd = STDIN_FILENO;
	while (blocks)
	{
		if (blocks->next && pipe(pipefd) < 0)
			return (perror("pipe"));
		pids[i] = fork();
		if (pids[i] < 0)
			return (perror("fork"));
		else if (pids[i] == 0)
			ft_son(blocks, shell, in_fd, pipefd);
		else
			ft_father(blocks, &in_fd, pipefd);
		blocks = blocks->next;
		i++;
	}
	ft_get_status(shell, i, pids, wstatus);
}
