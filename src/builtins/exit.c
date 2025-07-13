/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:33 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/13 18:42:23 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 
/// @param arg 
/// @param type 
static void	print_exit_error(char *arg, int type)
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
	return ;
}

/// @brief 
/// @param nbr 
/// @return 
static int	is_valid_number(char *nbr)
{
	int	i;

	i = 0;
	if (!nbr || !*nbr)
		return (0);
	if (nbr[i] == '+' || nbr[i] == '-')
		i++;
	if (!nbr[i])
		return (0);
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (0);
		i++;
	}
	return (1);
}

/// @brief 
/// @param args 
/// @return 
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

/// @brief 
/// @param args 
/// @param shell 
/// @param exit_code 
/// @param is_mult 
static void	clean_exit(char **args, t_shell *shell, int exit_code, int is_mult)
{
	if (is_mult)
		shell->exit_status = 1;
	exit(exit_code & 255);
}

/// @brief 
/// @param args 
/// @param shell 
/// @return 
int	ft_exit(char **args, t_shell *shell)
{
	long	exit_code;
	int		arg_count;

	ft_putstr_fd("exit\n", 1);
	arg_count = count_args(args);
	if (arg_count == 0)
		exit_code = (long)shell->exit_status;
	else if (arg_count == 1)
	{
		if (!is_valid_number(args[0]) || (!ft_strncmp(args[0], "--", 2)))
		{
			if(!ft_strncmp(args[0], "--", 2))
				exit(0);
			print_exit_error(args[0], 1);
			clean_exit(args, shell, 2, 1);
		}
		exit_code = ft_atoi(args[0]);
	}
	else
	{
		if (!is_valid_number(args[0]))
			clean_exit(args, shell, 1, 1);
		print_exit_error(NULL, 2);
		shell->exit_status = 1;
		return (1);
	}
	clean_exit(args, shell, exit_code, 0);
	return (0);
}
