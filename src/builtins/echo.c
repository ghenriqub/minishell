/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:26 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/12 15:09:43 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief we iterate until is a valid flag, 
/// @param arg the argument that should be verified 
/// @return 1 = valid flag || 0 = invalid flag
static int	n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	if (arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/// @brief the verification if the args are -n (-nnnn or -n -n too)
/// @param args the arguments we got from the STDIN_FILENO
/// @param new_line the variable that will tell if we'll have a nl or not
/// @return returns how many iterations we made until we got a valid string
static int	process_flags(char **args, int *new_line)
{
	int	i;

	i = 0;
	*new_line = 1;
	while (args[i] && n_flag(args[i]))
	{
		*new_line = 0;
		i++;
	}
	return (i);
}

/// @brief built-in echo implementation, with -n flag, whole string with write
/// @param args the arguments we got from the STDIN_FILENO
/// @return returns 0 on success (and it always succeeds)
int	ft_echo(char **args, int exit_status)
{
	int	new_line;
	int	i;

	if (!args || !args[0])
		return (0);
	if(!ft_strncmp(args[0], "$?", 2))
	{
		ft_putnbr_fd(exit_status, 1);
		return (0);
	}
	i = process_flags(args, &new_line);
	while (args[i])
	{
		write (STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
