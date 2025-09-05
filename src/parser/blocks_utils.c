/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:29:10 by lgertrud          #+#    #+#             */
/*   Updated: 2025/09/05 11:22:06 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_args(t_token *tmp)
{
	int	argc;

	argc = 0;
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type == T_WORD)
			argc++;
		tmp = tmp->next;
	}
	return (argc);
}

t_block	*ft_new_block(int argc)
{
	t_block	*block;

	block = ft_calloc(1, sizeof(t_block));
	if (!block)
		return (NULL);
	block->args = ft_calloc(sizeof(char *), argc + 1);
	block->limits = ft_calloc(sizeof(char *), argc + 1);
	block->input = ft_calloc(sizeof(char *), argc + 1);
	block->output = ft_calloc(sizeof(char *), argc + 1);
	return (block);
}

int	ft_redir_error(t_block *head, t_block *blk, t_shell *shell, t_token *token)
{
	write(2, REDIREC_ERROR, ft_strlen(REDIREC_ERROR));
	if (!token)
		ft_putendl_fd("`newline'", 2);
	else if (token->type == T_REDIRECT_IN)
		ft_putendl_fd("`<'", 2);
	else if (token->type == T_REDIRECT_OUT)
		ft_putendl_fd("`>'", 2);
	else if (token->type == T_APPEND)
		ft_putendl_fd("`>>'", 2);
	else if (token->type == T_PIPE)
		ft_putendl_fd("`|'", 2);
	else if (token->type == T_HEREDOC)
		ft_putendl_fd("`<<'", 2);
	ft_free_blocks(head);
	ft_free_blocks(blk);
	shell->exit_status = 2;
	return (-1);
}

int	ft_handle_redirect(t_block *block, t_token **token, int type)
{
	(*token) = (*token)->next;
	if (!(*token) || (*token)->type == T_PIPE || (*token)->type == T_REDIRECT_IN
		|| (*token)->type == T_REDIRECT_OUT
		|| (*token)->type == T_APPEND || (*token)->type == T_HEREDOC)
		return (-1);
	if (type == T_REDIRECT_IN)
		block->input[block->redirect_in++] = ft_strdup((*token)->value);
	else
	{
		if (type == T_APPEND)
			block->append = 1;
		block->output[block->redirect_out++] = ft_strdup((*token)->value);
	}
	return (0);
}

int	ft_handle_heredoc(t_block *block, t_token **token)
{
	(*token) = (*token)->next;
	if (!(*token) || (*token)->type == T_PIPE || (*token)->type == T_REDIRECT_IN
		|| (*token)->type == T_REDIRECT_OUT
		|| (*token)->type == T_APPEND || (*token)->type == T_HEREDOC)
		return (-1);
	block->limits[block->heredoc++] = ft_strdup((*token)->value);
	return (0);
}
