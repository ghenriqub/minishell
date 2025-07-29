/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:29:10 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/29 14:34:43 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_block *ft_parse_blocks(t_token *tokens)
{
	t_block *head = NULL;
	t_block *current = NULL;

	while (tokens)
	{
		t_block *new_block = calloc(1, sizeof(t_block));

		// Contar args
		t_token *tmp = tokens;
		int argc = 0;
		while (tmp && tmp->type != T_PIPE)
		{
			if (tmp->type == T_WORD)
				argc++;
			tmp = tmp->next;
		}

		// Alocar args
		new_block->args = malloc(sizeof(char *) * (argc + 1));
		int i = 0;

		// Preencher infos
		while (tokens && tokens->type != T_PIPE)
		{
			if (tokens->type == T_WORD)
				new_block->args[i++] = strdup(tokens->value);
			else if (tokens->type == T_REDIRECT_IN)
			{
				new_block->redirect_in = 1;
				tokens = tokens->next;
				if (tokens)
					new_block->input = strdup(tokens->value);
			}
			else if (tokens->type == T_REDIRECT_OUT)
			{
				new_block->redirect_out = 1;
				new_block->append = 0;
				tokens = tokens->next;
				if (tokens)
					new_block->output = strdup(tokens->value);
			}
			else if (tokens->type == T_APPEND)
			{
				new_block->redirect_out = 1;
				new_block->append = 1;
				tokens = tokens->next;
				if (tokens)
					new_block->output = strdup(tokens->value);
			}
			else if (tokens->type == T_HEREDOC)
			{
				new_block->heredoc = 1;
				tokens = tokens->next;
				if (tokens)
					new_block->limit = strdup(tokens->value); // ou outro campo para delim
			}
			tokens = tokens->next;
		}
		new_block->args[i] = NULL;

		// Adiciona na lista encadeada
		if (!head)
			head = new_block;
		else
			current->next = new_block;
		current = new_block;

		// Pula o pipe
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}

	return head;
}


void	print_block_info(t_block *block)
{
	int	i = 0;
	int	block_num = 1;

	while (block)
	{
		printf("=== Bloco %d ===\n", block_num);

		// Args
		printf("Args: ");
		if (block->args && block->args[0])
		{
			while (block->args[i])
			{
				printf("\"%s\" ", block->args[i]);
				i++;
			}
			printf("\n");
		}
		else
			printf("(nenhum)\n");

		// Redirect IN
		printf("Redirect IN: %s", block->redirect_in ? "sim" : "não");
		if (block->redirect_in)
			printf(" (%s)", block->input ? block->input : "(null)");
		printf("\n");

		// Heredoc
		printf("Heredoc: %s", block->heredoc ? "sim" : "não");
		if (block->heredoc)
			printf(" (%s)", block->input ? block->input : "(null)");
		printf("\n");

		// Redirect OUT
		printf("Redirect OUT: %s", block->redirect_out ? "sim" : "não");
		if (block->redirect_out)
		{
			printf(" (%s)", block->output ? block->output : "(null)");
			printf(" [%s]", block->append ? "APPEND" : "TRUNC");
		}
		printf("\n");

		printf("\n");
		block = block->next;
		block_num++;
		i = 0;
	}
}

void	ft_free_blocks(t_block *head)
{
	t_block	*tmp;

	while (head)
	{
		tmp = head->next;

		// Libera args
		if (head->args)
			ft_free_split(head->args);
		// Libera input/output
		if (head->input)
			free(head->input);
		if (head->limit)
			free(head->limit);
		if (head->output)
			free(head->output);
		// Libera o próprio bloco
		free(head);
		head = tmp;
	}
}