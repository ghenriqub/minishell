/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:00:50 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/17 13:19:29 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	ft_pipe_loop(t_block *blocks, t_shell *shell, pid_t *pids, int *i)
{
	int		pipefd[2];
	int		in_fd;

	in_fd = STDIN_FILENO;
	while (blocks)
	{
		if (blocks->next && pipe(pipefd) < 0)
			return (perror("pipe"));
		pids[*i] = fork();
		if (pids[*i] < 0)
			return (perror("fork"));
		else if (pids[*i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			ft_son(blocks, shell, in_fd, pipefd);
		}
		else
			ft_father(blocks, &in_fd, pipefd);
		blocks = blocks->next;
		(*i)++;
	}
}

void	ft_pipe_command(t_block *blocks, t_shell *shell)
{
	pid_t	pids[256];
	int		i;
	int		wstatus;

	i = 0;
	wstatus = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_pipe_loop(blocks, shell, pids, &i);
	ft_get_status(shell, i, pids, wstatus);
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
