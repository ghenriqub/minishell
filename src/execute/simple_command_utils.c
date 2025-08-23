/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:54:43 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/23 12:49:15 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait(t_shell *shell, int status, int pid)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

void	ft_error_path(t_shell *shell, char *command)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	shell->exit_status = 127;
}

void	ft_restore_std(int stdin_copy, int stdout_copy)
{
	dup2(stdin_copy, STDOUT_FILENO);
	dup2(stdout_copy, STDIN_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}
