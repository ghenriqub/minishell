/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:29:10 by lgertrud          #+#    #+#             */
/*   Updated: 2025/09/05 11:35:05 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_fill_blk(t_block *blk, t_token **tk, t_shell *sh, t_block *head)
{
	int	i;

	i = 0;
	while (*tk && (*tk)->type != T_PIPE)
	{
		if ((*tk)->type == T_WORD)
			blk->args[i++] = ft_strdup((*tk)->value);
		else if ((*tk)->type == T_REDIRECT_IN
			|| (*tk)->type == T_REDIRECT_OUT || (*tk)->type == T_APPEND)
		{
			if (ft_handle_redirect(blk, tk, (*tk)->type) < 0)
				return (ft_redir_error(head, blk, sh, *tk));
		}
		else if ((*tk)->type == T_HEREDOC)
		{
			if (ft_handle_heredoc(blk, tk) < 0)
				return (ft_redir_error(head, blk, sh, *tk));
		}
		(*tk) = (*tk)->next;
	}
	blk->args[i] = NULL;
	return (0);
}

static int	ft_pipe_error(t_block *head, t_shell *shell)
{
	ft_free_blocks(head);
	ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
	shell->exit_status = 1;
	return (-1);
}

void	ft_free_blocks(t_block *head)
{
	t_block	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		if (head->args)
			ft_free_split(head->args);
		if (head->input)
			ft_free_split(head->input);
		if (head->limits)
			ft_free_split(head->limits);
		if (head->output)
			ft_free_split(head->output);
		free(head);
		head = tmp;
	}
}

/// @brief 
/// @param token 
/// @param shell 
///	block [0] == head
///	block [1] == current
///	block [2] == new block
/// @return 
t_block	*ft_parse_blocks(t_token *token, t_shell *shell)
{
	t_block	*block[3];
	int		argc;

	block[0] = NULL;
	block[1] = NULL;
	while (token)
	{
		argc = ft_count_args(token);
		block[2] = ft_new_block(argc);
		if (!block[2] || ft_fill_blk(block[2], &token, shell, block[0]) < 0)
			return (NULL);
		if (!block[0])
			block[0] = block[2];
		else
			block[1]->next = block[2];
		block[1] = block[2];
		if (token && token->type == T_PIPE)
		{
			token = token->next;
			if (!token || token->type == T_PIPE)
				return (ft_pipe_error(block[0], shell), NULL);
		}
	}
	return (block[0]);
}
