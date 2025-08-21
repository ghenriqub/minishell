/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:54:43 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/21 11:34:57 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_restore_std(int stdin_copy, int stdout_copy);
static void	ft_error_path(t_shell *shell, char *command);
static void	ft_wait(t_shell *shell, int status, int pid);

void	ft_simple_command(t_block *blocks, t_shell *shell)
{
	int		stdin_copy;
	int		stdout_copy;
	char	*path;

	stdin_copy = dup(STDOUT_FILENO);
	stdout_copy = dup(STDIN_FILENO);
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
			ft_simple_command_2(blocks, shell, stdin_copy, stdout_copy);
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
		close(fd_in);
		close(fd_out);
		if (execve(path, blocks->args, shell->env) == -1)
		{
			ft_putstr_fd(blocks->args[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			ft_free_blocks(blocks);
			free(path);
			ft_free_split(shell->env);
			free(shell);
			exit(127);
		}
	}
	ft_wait(shell, status, pid);
	if (path)
		free(path);
}

static void	ft_wait(t_shell *shell, int status, int pid)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

static void	ft_error_path(t_shell *shell, char *command)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	shell->exit_status = 127;
}

static void	ft_restore_std(int stdin_copy, int stdout_copy)
{
	dup2(stdin_copy, STDOUT_FILENO);
	dup2(stdout_copy, STDIN_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}
