/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:33 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/12 11:26:51 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	print_exit_error(char *arg, int type)
{
	if (type == 0)
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (type == 1)
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": too many arguments", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);		
	}
	return ;
}


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


static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}


static void	cleanup_exit(char **args, t_shell *shell, int exit_code, int is_mult)
{
	if (!is_mult)
		print_exit_error(args, 0);
	free_env(shell->env);
	free_history(shell->history);
	exit(exit_code & 255);
}


int	ft_exit(char **args, t_shell *shell)
{
	long	exit_code;
	int		arg_count;

	ft_putchar_fd("exit\n", 2);
	arg_count = count_args(args);
	if (arg_count == 1)
		exit_code = shell->exit_status;
	else if (arg_count = 2)
	{
		if (!is_valid_number(args[1]))
			cleanup_exit(args, shell, 2, 0);
		exit_code = ft_atoi(args[1]);
	}
	else
	{
		if (!is_valid_number(args[1]))
			cleanup_exit(args, shell, 2, 0);
		print_exit_error(NULL, 1);
		return (1);
	}
	cleanup_exit(args, shell, exit_code, 1);
	return (0);
}
