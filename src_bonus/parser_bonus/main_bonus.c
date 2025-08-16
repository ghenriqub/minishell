/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:33:12 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/15 12:03:15 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_shell	*g_shell;

/// @brief Handles the SIGINT signal (Ctrl-C) by clearing the current input line
///        and redisplaying the prompt without exiting the shell.
/// @param sig The signal number (unused in this function).
static void	ft_handle_sigint(int sig)
{
	(void)sig;
	if (g_shell)
		g_shell->exit_status = 130;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

/// @brief Sets up custom signal handlers for interactive shell behavior.
///        Specifically, handles SIGINT and ignores SIGQUIT.
/// @param void This function takes no parameters.
static void	ft_setup_signals(t_shell *shell)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/// @brief in this function we determine if is a terminal or not
/// @return 1 = is a tty, 0 = it isn't a terminal
static int	check_interactive(void)
{
	if (isatty(STDIN_FILENO))
		return (1);
	return (0);
}

/// @brief 
/// @param shell 
/// @param env 
static void	minishell_loop(t_shell *shell, char **env)
{
	char	*line;
	t_block	*blocks;

	while (1)
	{
		if (check_interactive())
			line = readline(MINI);
		else
			line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			if (check_interactive())
				ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (*line)
			add_history(line);
		and_or(shell, line, env);
		free(line);
	}
}

/// @brief Read line, create history, check signal ctrl-C and call tokenizer
/// @return value exit
int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_block	*blocks;
	t_shell	*shell;

	shell = ft_init_shell(shell, env);
	(void)argc;
	(void)argv;
	g_shell = shell;
	ft_setup_signals(shell);
	minishell_loop(shell, env);
	ft_free_split(shell->env);
	free(shell);
	rl_clear_history();
	return (0);
}
