/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:53:29 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/29 14:05:14 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//cuidado com o leak, sempre chamar o ft_free com o primeiro node.
void	ft_redirections(t_block *block)
{
	if(block->heredoc)
	{
		ft_heredoc(block, block->limit);
		dup2(block->heredoc_fd,0);
		close(block->heredoc_fd);
	}
	if(block->redirect_in)
	{
		block->redirect_in = open(block->input, O_RDONLY);
		if (block->redirect_in < 0)
		{
			perror("open outfile");
			ft_free_blocks(block);
		}
		dup2(block->redirect_in, STDIN_FILENO);
		close(block->redirect_in);
	}
	if(block->redirect_out)
	{
		if(block->append)
			block->redirect_out = open(block->output, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			block->redirect_out = open(block->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (block->redirect_out < 0)
		{
			perror("open outfile");
		}
		dup2(block->redirect_out , STDOUT_FILENO);
		close(block->redirect_out);
	}
}
