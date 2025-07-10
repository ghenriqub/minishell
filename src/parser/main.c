/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:33:12 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/10 16:22:00 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Read line, create history, check signal ctrl-C and call tokenizer
/// @param nothing
/// @return value exit
int	main(void)
{
	char	*line;
	t_token	*tokens;

	ft_setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = ft_tokenizer(line);
		free(line);
		ft_free_tokens(tokens);
	}
	rl_clear_history();
	return (0);
}

/// @brief Handles the SIGINT signal (Ctrl-C) by clearing the current input line
///        and redisplaying the prompt without exiting the shell.
/// @param sig The signal number (unused in this function).
void	ft_handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

/// @brief Sets up custom signal handlers for interactive shell behavior.
///        Specifically, handles SIGINT and ignores SIGQUIT.
/// @param void This function takes no parameters.
void	ft_setup_signals(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
