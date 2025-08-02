/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:00:50 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/02 13:11:32 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

s//tatic void ft_middle_command(int infile_fd, blocks, int outfile);

void	ft_pipe_command(t_block *blocks, t_shell *shell)
{
	int infile;
	int status;
	int pid;
	int pip[2];

	pipe(pid);
	if(!ft_redirections(blocks, shell))
		return ;
	infile = blocks->redirect_in;
	while(blocks)
	{
		// pid = fork();
		// if(pid == 0)
		// {
		// 	if(blocks->next)
		// 		ft_middle_command()
		// }
	}
}
