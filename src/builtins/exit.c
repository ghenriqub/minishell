/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:33 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/23 09:06:52 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 
/// @param arg 
/// @param type 
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
static void	clean_exit(char **args, t_shell *shell,
		int exit_code, t_token *token)
{
	shell->exit_status = exit_code;
	ft_free_split(shell->env);
	free(shell);
	ft_free_split(args);
	ft_free_tokens(token);
	exit(exit_code & 255);
}

/// @brief 
/// @param arg 
/// @return 
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

/// @brief 
/// @param args 
/// @param shell 
/// @return 
int	ft_exit(char **args, t_shell *shell, t_token *token)
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
			clean_exit(args, shell, 2, token);
		}
		exit_code = ft_atoi(args[0]);
	}
	else
	{
		if (arg_count == 0 || !is_valid_arg(args[0]))
			clean_exit(args, shell, 1, token);
		print_exit_error(NULL, 2, shell);
		return (1);
	}
	clean_exit(args, shell, exit_code, token);
	return (0);
}
