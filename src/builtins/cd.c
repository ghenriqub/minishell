/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:17:22 by ghenriqu          #+#    #+#             */
/*   Updated: 2025/07/13 12:32:39 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>

static void	print_cd_error(char path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

char	*get_curr_pwd(void)
{
	
}

char	*get_target_pwd(args, shell->env)
{
	
}




static int	handle_many_args(char **args)
{
	ft_putstr_fd("cd: too many arguments", STDERR_FILENO);
	return (1);
}


int	ft_builtin(char **args, t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*target_pwd;
	int		result;

	if (!args || !args[0])
		return (1);
	if (args[1])
		return (handle_many_args(args));
	old_pwd = get_curr_pwd();
	target_pwd = get_target_pwd(args, shell->env);
	if (!target_pwd)
	{
		free(old_pwd);
		return (1);
	}
	result = chdir(target_pwd);
	if (result == -1)
	{
		print_cd_error(target_pwd);
		free(old_pwd);
		free(target_pwd);
		return (1);
	}
	new_pwd = get_curr_pwd();
	update_pwd_env(old_pwd, new_pwd, shell->env);
	free(old_pwd);
	free(new_pwd);
	free(target_pwd);
	return (0);
}
