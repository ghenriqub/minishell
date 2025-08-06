/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:49:12 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/06 13:55:56 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minishell(t_block *blocks, t_shell *shell)
{
	if (!blocks->next)
		ft_simple_command(blocks, shell);
	else
		ft_pipe_command(blocks, shell);
}
