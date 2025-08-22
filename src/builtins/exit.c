/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:33 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/22 11:01:01 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief the function that will print the standard exit error message
/// @param arg the arguments received at the call
/// @param type if its non-numeric or if its too many arguments
/// @param shell the shell structure with exit status
static void	print_exit_error(char *arg, int type, t_shell *shell)
{
	if (type == 1)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	else if (type == 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	}
	if (!arg)
		shell->exit_status = 1;
	return ;
}

/// @brief the free clean and error code of the exit call
/// @param args the arguments received at the call
/// @param shell the shell structure with exit status
/// @param exit_code the code we got to exit
/// @param token the tokenized structure with calls
static void	clean_exit(char **args, t_shell *shell,
		int exit_code, t_block *block)
{
	(void)args;
	shell->exit_status = exit_code;
	ft_free_split(shell->env);
	ft_free_split(shell->export);
	free(shell);
	ft_free_blocks(block);
	exit(exit_code & 255);
}

/// @brief the execution of the ft_exit in case of arg_count == 1
static void	ft_exit_one_arg(char **args, t_shell *sh, t_block *blk)
{
	long	exit_code;

	if (!is_valid_arg(args[0]) || (!ft_strncmp(args[0], "--", 2)))
	{
		if (!ft_strncmp(args[0], "--", 2))
			exit (0);
		print_exit_error(args[0], 1, sh);
		clean_exit(args, sh, 2, blk);
	}
	exit_code = ft_atoi(args[0]);
	clean_exit(args, sh, exit_code, blk);
}

/// @brief the built-in implementation of exit()
/// @param args the arguments that we will receive
/// @param shell the structure that hold some functionalities (exit status)
/// @param block 
/// @return 0 = success, 1 = error
int	ft_exit(char **args, t_shell *shell, t_block *block)
{
	int		arg_count;

	ft_putstr_fd("exit\n", 1);
	arg_count = count_args(args);
	if (arg_count == 0)
		clean_exit(args, shell, shell->exit_status, block);
	else if (arg_count == 1)
		ft_exit_one_arg(args, shell, block);
	else
	{
		if (!is_valid_arg(args[0]))
		{
			print_exit_error(args[0], 1, shell);
			clean_exit(args, shell, 2, block);
		}
		print_exit_error(NULL, 2, shell);
		return (1);
	}
	return (0);
}
