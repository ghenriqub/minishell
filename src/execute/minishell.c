/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:49:12 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/29 13:54:33 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minishell(t_block *blocks, t_shell *shell)
{
	char	*path;
	int		pid;
	int		stdin_copy;
	int		stdin_copy2;

	path = NULL;

	stdin_copy = dup(STDOUT_FILENO);
	stdin_copy2 = dup(STDIN_FILENO);
	ft_redirections(blocks);
	if(!ft_call_builtins(blocks, shell))
	{
		path = ft_found_path(blocks->args[0], shell->env);
		shell->exit_status = 127;
		if(path)
		{
			pid = fork();
			if(pid == 0)
				if(execve(path, blocks->args, shell->env) == -1)
				{
					ft_putstr_fd(blocks->args[0], STDERR_FILENO);
					ft_putendl_fd(": command not found", STDERR_FILENO);
					shell->exit_status = 127;
					exit(127);
				}
			waitpid(pid, NULL, 0);
		}
		else
		{
			ft_putstr_fd(blocks->args[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
	}
	dup2(stdin_copy, STDOUT_FILENO);
	dup2(stdin_copy2, STDIN_FILENO);
	close(stdin_copy);
	close(stdin_copy2);
	if(path)
		free(path);
}
