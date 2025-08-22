/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:00:50 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/22 12:25:33 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_all(t_block *block, t_shell *shell);

void	ft_cmd(t_block *blocks, t_shell *shell, t_block *head)
{
	char	*path;

	path = NULL;
	if (!ft_call_builtins(blocks, shell))
	{
		path = ft_found_path(blocks->args[0], shell->env);
		if (!path)
		{
			ft_free_all(head, shell);
			exit(127);
		}
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

void	ft_dup_stdin(int in_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
}

static void	ft_free_all(t_block *block, t_shell *shell)
{
	ft_free_blocks(block);
	ft_free_split(shell->env);
	ft_free_split(shell->export);
	free(shell);
}
