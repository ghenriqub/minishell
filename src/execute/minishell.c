/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:49:12 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/05 15:38:02 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_restore_std(int stdin_copy, int stdout_copy);
static void	ft_error_path(t_shell *shell, char *command);

void	ft_minishell(t_block *blocks, t_shell *shell)
{
	if (!blocks->next)
		ft_simple_command(blocks, shell);
	else
		ft_pipe_command(blocks, shell);
}

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
	if (!strcmp(blocks->args[0], "exit"))
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
	int status;

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
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	if (path)
		free(path);
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
