/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:54:43 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/23 16:06:24 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	ft_simple_else(t_block *blks, t_shell *sh, int stdinc, int stdoutc)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_simple_command_2(blks, sh, stdinc, stdoutc);
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static void	ft_simple_else_2(t_block *blocks, t_shell *shell, char *path)
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

void	ft_simple_command(t_block *blocks, t_shell *shell)
{
	int		stdin_copy;
	int		stdout_copy;
	char	*path;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (!ft_redirections(blocks, shell))
	{
		ft_restore_std(stdin_copy, stdout_copy);
		return ;
	}
	if (!ft_strcmp(blocks->args[0], "exit"))
		ft_restore_std(stdin_copy, stdout_copy);
	if (!ft_call_builtins(blocks, shell))
	{
		path = ft_found_path(blocks->args[0], shell->env);
		if (!path)
			ft_error_path(shell, blocks->args[0]);
		else
		{
			free(path);
			ft_simple_else(blocks, shell, stdin_copy, stdout_copy);
		}
	}
	ft_restore_std(stdin_copy, stdout_copy);
}

void	ft_simple_command_2(t_block *blocks,
		t_shell *shell, int fd_in, int fd_out)
{
	int		pid;
	char	*path;
	int		status;

	status = 0;
	path = ft_found_path(blocks->args[0], shell->env);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd_in);
		close(fd_out);
		if (execve(path, blocks->args, shell->env) == -1)
			ft_simple_else_2(blocks, shell, path);
	}
	ft_wait(shell, status, pid);
	if (path)
		free(path);
}
