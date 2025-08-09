/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:00:50 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/09 17:35:08 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmd(t_block *blocks, t_shell *shell, int infile, int outfile);
static void	ft_get_status(t_shell *shell, int i, int *pids, int wstatus);
static void	ft_father(t_block *blocks, int *in_fd, int *pipefd);
static void	ft_son(t_block *blocks, t_shell *shell, int in_fd, int *pipefd);

void	ft_pipe_command(t_block *blocks, t_shell *shell)
{
	int		pipefd[2];
	int		in_fd;
	pid_t	pids[256];
	int		i;
	int		wstatus;

	i = 0;
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

static void	ft_cmd(t_block *blocks, t_shell *shell, int infile, int outfile)
{
	int		pid;
	char	*path;

	path = NULL;
	if (!ft_call_builtins(blocks, shell))
	{
		path = ft_found_path(blocks->args[0], shell->env);
		if (execve(path, blocks->args, shell->env) == -1)
		{
			ft_putstr_fd(blocks->args[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			ft_free_blocks(blocks);
			free(path);
			ft_free_split(shell->env);
			free(shell);
			shell->exit_status = 127;
			exit(127);
		}
	}
	if (path)
		free(path);
}

static void	ft_son(t_block *blocks, t_shell *shell, int in_fd, int *pipefd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (blocks->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (!ft_redirections(blocks, shell))
		exit(1);
	ft_cmd(blocks, shell, STDIN_FILENO, STDOUT_FILENO);
	exit(0);
}

static void	ft_father(t_block *blocks, int *in_fd, int *pipefd)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (blocks->next)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
}

static void	ft_get_status(t_shell *shell, int i, int *pids, int wstatus)
{
	int	j;

	j = 0;
	while (j < i)
	{
		waitpid(pids[j], &wstatus, 0);
		if (j == i - 1)
		{
			if (WIFEXITED(wstatus))
				shell->exit_status = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				shell->exit_status = 128 + WTERMSIG(wstatus);
			else
				shell->exit_status = 1;
		}
		j++;
	}
}
