/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:49:12 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/28 11:38:07 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minishell(t_block *blocks, t_shell *shell)
{
	char	*path;
	int		pid;
	
	path = NULL;
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
					perror("execve cmd");
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
	if(path)
		free(path);
}
