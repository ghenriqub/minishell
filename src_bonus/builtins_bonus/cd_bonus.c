/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:22 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/08/02 16:22:54 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <string.h>
#include <errno.h>

/// @brief the standard cd error message
/// @param path the path that were sent
static void	print_cd_error(char *path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

/// @brief the error message in case of too many args
/// @param args the arguments are passed as a returnable function
/// @return 1 after the message sent
static int	handle_many_args(char **args)
{
	ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
	return (1);
}

/// @brief free the variables in the main cd function
/// @param old the old pwd
/// @param new the new pwd
/// @param target and the targeted pwd
static void	free_cd(char *old, char *new, char *target)
{
	if (old)
		free(old);
	if (new)
		free(new);
	if (target)
		free(target);
	else
		return ;
}

/// @brief the function that emulates the cd function
/// @var pwd[0] = old_pwd, pwd[1] = new_pwd, pwd[2] = target_pwd
/// @param args the arguments we got from the readline input
/// @param shell the struct that holds our env variables
/// @return 0 = success and 1 = error
int	ft_cd(char **args, t_shell *shell)
{
	char	*pwd[3];
	int		result;

	if (!args)
		return (1);
	if (args[1])
		return (handle_many_args(args));
	pwd[0] = get_current_dir();
	pwd[2] = get_target_dir(args, shell);
	if (!pwd[2])
	{
		free(pwd[0]);
		return (1);
	}
	result = chdir(pwd[2]);
	if (result == -1)
	{
		print_cd_error(pwd[2]);
		free_cd(pwd[0], NULL, pwd[2]);
		return (1);
	}
	pwd[1] = get_current_dir();
	update_pwd_env(pwd[0], pwd[1], shell);
	free_cd (pwd[0], pwd[1], pwd[2]);
	return (0);
}
