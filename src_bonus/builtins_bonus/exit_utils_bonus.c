/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:33 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/16 12:18:00 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/// @brief the classic count args
/// @param args the string that will hold the arguments
/// @return the number of arguments
int	count_args(char **args)
{
	int	count;

	count = 0;
	if (!args || !args[0])
		return (0);
	while (args[count])
		count++;
	return (count);
}

/// @brief verifies the validity of the argument with exit
/// @param arg the argument being analyzed
/// @return 1 = is valid, 0 = not valid
int	is_valid_arg(char *arg)
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
