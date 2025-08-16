/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:54:15 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/15 16:02:28 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char		**ft_split_array(const char *str, const char *delim);
static void	ft_exec(t_block *blocks, t_shell *shell, char **env, char *and);

void	and_or(t_shell *shell, char *line, char **env)
{
	t_block	*blocks;
	char	**and;
	char	**or;
	int		y;
	int		i;

	or = ft_split_array(line, "||");
	y = 0;
	while (or[y])
	{
		i = 0;
		and = ft_split_array(or[y], "&&");
		while (and[i])
		{
			ft_exec(blocks, shell, env, and[i]);
			if (shell->exit_status != 0)
				break ;
			i++;
		}
		ft_free_split(and);
		if (shell->exit_status == 0)
			break ;
		y++;
	}
	ft_free_split(or);
}

static void	ft_exec(t_block *blocks, t_shell *shell, char **env, char *and)
{
	if (ft_strnstr(and, "||", ft_strlen(and)))
		and_or(shell, and, env);
	else
	{
		blocks = ft_tokenizer(shell, and, env);
		if (blocks)
			ft_minishell(blocks, shell);
		ft_free_blocks(blocks);
	}
}
