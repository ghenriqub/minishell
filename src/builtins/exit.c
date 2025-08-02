/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:33 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/02 16:24:31 by ghenriqu         ###   ########.fr       */
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

/// @brief the classic count args
/// @param args the string that will hold the arguments
/// @return the number of arguments
static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args || !args[0])
		return (0);
	while (args[count])
		count++;
	return (count);
}

/// @brief the free clean and error code of the exit call
/// @param args the arguments received at the call
/// @param shell the shell structure with exit status
/// @param exit_code the code we got to exit
/// @param token the tokenized structure with calls
static void	clean_exit(char **args, t_shell *shell,
		int exit_code, t_block *block)
{
	shell->exit_status = exit_code;
	ft_free_split(shell->env);
	free(shell);
	ft_free_blocks(block);
	exit(exit_code & 255);
}

/// @brief verifies the validity of the argument with exit
/// @param arg the argument being analyzed
/// @return 1 = is valid, 0 = not valid
static int	is_valid_arg(char *arg)
{
	unsigned long long	num[2];
	int					i[2];

	i[0] = 0;
	i[1] = 1;
	num[1] = 0;
	num[0] = LLONG_MAX;
	if (arg[i[0]] == '-' || arg[i[0]] == '+')
	{
		if (arg[i[0]] == '-')
			i[1] *= -1;
		i[0]++;
	}
	if (i[1] == -1)
		num[0] = (unsigned long long)LLONG_MAX + 1;
	while (arg[i[0]])
	{
		if (!ft_isdigit(arg[i[0]]))
			return (0);
		if (num[1] > (num[0] - (arg[i[0]] - '0')) / 10)
			return (0);
		num[1] = num[1] * 10 + (arg[i[0]] - '0');
		i[0]++;
	}
	return (1);
}

/// @brief the built-in implementation of exit()
/// @param args the arguments that we will receive
/// @param shell the structure that hold some functionalities (exit status)
/// @param block 
/// @return 0 = success, 1 = error
int	ft_exit(char **args, t_shell *shell, t_block *block)
{
	long	exit_code;
	int		arg_count;

	ft_putstr_fd("exit\n", 1);
	arg_count = count_args(args);
	if (arg_count == 1)
	{
		if (!is_valid_arg(args[0]) || (!ft_strncmp(args[0], "--", 2)))
		{
			if (!ft_strncmp(args[0], "--", 2))
				exit (0);
			print_exit_error(args[0], 1, shell);
			clean_exit(args, shell, 2, block);
		}
		exit_code = ft_atoi(args[0]);
	}
	else
	{
		if (arg_count == 0 || !is_valid_arg(args[0]))
			clean_exit(args, shell, 1, block);
		print_exit_error(NULL, 2, shell);
		return (1);
	}
	clean_exit(args, shell, exit_code, block);
	return (0);
}
