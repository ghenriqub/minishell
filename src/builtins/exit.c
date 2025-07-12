/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:33 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/12 20:03:55 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	print_exit_error(char *arg, int type)
{
	if (type == 1)
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (type == 2)
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
	if(!args || !args[0])
		return (0);
	while (args[count])
		count++;
	return (count);
}


static void	cleanup_exit(char **args, t_shell *shell, int exit_code, int is_mult)
{
	if (is_mult)
		print_exit_error(args[0], is_mult);
	//free_env(shell->env);
	//free_history(shell->history);
	exit(exit_code & 255);
}


int	ft_exit(char **args, t_shell *shell)
{
	long	exit_code;
	int		arg_count;

	ft_putstr_fd("exit\n", 1);
	arg_count = count_args(args);
	if (arg_count == 0)
	{
		exit_code = (long)shell->exit_status;
	}
	else if (arg_count == 1)
	{
		if (!is_valid_number(args[0]))
			cleanup_exit(args, shell, 2, 1);
		exit_code = ft_atoi(args[0]);
	}
	else
	{
		if (!is_valid_number(args[0]))
			cleanup_exit(args, shell, 2, 1);
		print_exit_error(NULL, 2);
		return (1);
	}
	cleanup_exit(args, shell, exit_code, 0);
	return (0);
}
