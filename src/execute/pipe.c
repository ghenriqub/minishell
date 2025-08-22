/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:00:50 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/22 12:25:07 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipe_loop(t_block *blocks, t_shell *shell, pid_t *pids, int *i);

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

static void	ft_pipe_loop(t_block *blocks, t_shell *shell, pid_t *pids, int *i)
{
	int		pipefd[2];
	int		in_fd;
	t_block	*head;

	head = blocks;
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
			ft_dup_stdin(in_fd);
			ft_son(blocks, shell, pipefd, head);
		}
		else
			ft_father(blocks, &in_fd, pipefd);
		blocks = blocks->next;
		(*i)++;
	}
}

void	ft_son(t_block *block, t_shell *shell, int *pipefd, t_block *head)
{
	if (block->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (!ft_redirections(block, shell))
		exit(1);
	ft_cmd(block, shell, head);
	ft_free_blocks(block);
	ft_free_split(shell->env);
	ft_free_split(shell->export);
	free(shell);
	exit(0);
}

void	ft_father(t_block *blocks, int *in_fd, int *pipefd)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (blocks->next)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
}
