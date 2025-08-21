/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:00:50 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/21 16:20:21 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error_path(t_block *blocks, t_shell *shell);

void	ft_cmd(t_block *blocks, t_shell *shell)
{
	char	*path;

	path = NULL;
	if (!ft_call_builtins(blocks, shell))
	{
		path = ft_found_path(blocks->args[0], shell->env);
		if (!path)
			ft_error_path(blocks, shell);
		if (execve(path, blocks->args, shell->env) == -1)
		{
			ft_putstr_fd(blocks->args[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			ft_free_blocks(blocks);
			free(path);
			ft_free_split(shell->env);
			ft_free_split(shell->export);
			free(shell);
			exit(127);
		}
	}
	if (path)
		free(path);
}

void	ft_son(t_block *blocks, t_shell *shell, int in_fd, int *pipefd)
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
	{
		ft_free_blocks(blocks);
		ft_free_split(shell->env);
		ft_free_split(shell->export);
		free(shell);
		exit(1);
	}
	ft_cmd(blocks, shell);
	ft_free_blocks(blocks);
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

void	ft_get_status(t_shell *shell, int i, int *pids, int wstatus)
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
static void	ft_error_path(t_block *blocks, t_shell *shell)
{
	ft_putstr_fd(blocks->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free_blocks(blocks);
	ft_free_split(shell->env);
	ft_free_split(shell->export);
	free(shell);
	exit(127);
}