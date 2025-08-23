/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:53:29 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/23 15:31:09 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_red_here(t_block *block, t_shell *shell);
static int	ft_red_in(t_block *block, t_shell *shell);
static int	ft_red_out(t_block *block, t_shell *shell);
//cuidado com o leak, sempre chamar o ft_free com o primeiro node.

int	ft_redirections(t_block *block, t_shell *shell)
{
	int	ret;

	ret = 1;
	if (block->heredoc > 0)
		ret = ft_red_here(block, shell);
	if (block->redirect_in > 0 && ret == 1)
		ret = ft_red_in(block, shell);
	if (block->redirect_out > 0 && ret == 1)
		ret = ft_red_out(block, shell);
	return (ret);
}

static int	ft_red_here(t_block *block, t_shell *shell)
{
	int	i;

	i = 0;
	while (block->limits[i])
	{
		ft_heredoc(block, block->limits[i], shell);
		i++;
	}
	dup2(block->heredoc_fd, 0);
	close(block->heredoc_fd);
	return (1);
}

static int	ft_red_in(t_block *block, t_shell *shell)
{
	int	i;

	i = 0;
	while (block->input[i])
	{
		block->redirect_in = open(block->input[i], O_RDONLY);
		if (block->redirect_in < 0)
		{
			perror(block->input[i]);
			shell->exit_status = 1;
			return (0);
		}
		i++;
		if (block->input[i])
			close(block->redirect_in);
	}
	dup2(block->redirect_in, STDIN_FILENO);
	close(block->redirect_in);
	return (1);
}

static int	ft_red_out(t_block *block, t_shell *shell)
{
	int	i;

	i = 0;
	while (block->output[i])
	{
		if (block->append)
			block->redirect_out = open(block->output[i], O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		else
			block->redirect_out = open(block->output[i], O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		if (block->redirect_out < 0)
		{
			perror("open outfile");
			shell->exit_status = 1;
			return (0);
		}
		i++;
		if (block->output[i])
			close(block->redirect_out);
	}
	dup2(block->redirect_out, STDOUT_FILENO);
	close(block->redirect_out);
	return (1);
}
