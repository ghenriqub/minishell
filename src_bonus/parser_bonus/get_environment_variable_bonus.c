/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_environment_variable_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:47:03 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/21 11:52:33 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

/// @brief this funcion take a environment variable and
///			set in one string 
/// @param env envinornment
/// @param part string where are the variable
/// @param code_exit exit code, if viariable is '?'
/// @return return new string, whit variable.
char	*ft_get_variable(char **env, char *part, int code_exit)
{
	char	*start;
	char	*var_name;
	char	*var_value;
	int		i;

	start = ft_strchr(part, '$');
	i = 1;
	if (!start[1])
		return (part);
	if (start[1] == '?')
		return (ft_concat(start, part, ft_itoa(code_exit), i + 1));
	if (start[1] == '{')
		return (ft_get_brace(env, part, start));
	while (start[i] && (ft_isalnum(start[i]) || start[i] == '_'))
		i++;
	var_name = ft_substr(start, 1, i - 1);
	var_value = get_env_value(env, var_name);
	free(var_name);
	return (ft_concat(start, part, var_value, i));
}

char	*get_env_value(char **env, const char *var_name)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, var_len) && env[i][var_len] == '=')
			return (ft_strdup(env[i] + var_len + 1));
		i++;
	}
	return (ft_strdup(""));
}

char	*ft_concat(char *start, char *part, char *var_value, int i)
{
	int		prefix_len;
	char	*prefix;
	char	*suffix;
	char	*tmp;
	char	*result;

	prefix_len = start - part;
	prefix = ft_substr(part, 0, prefix_len);
	suffix = ft_strdup(start + i);
	tmp = ft_strjoin(prefix, var_value);
	result = ft_strjoin(tmp, suffix);
	free(prefix);
	free(suffix);
	free(var_value);
	free(tmp);
	free(part);
	return (result);
}

/// @brief 
/// @param env 
/// @param part 
/// @param start 
/// @return 
char	*ft_get_brace(char **env, char *part, char *start)
{
	char	*end_brace;
	char	*var_name;
	char	*var_value;
	int		len;

	end_brace = ft_strchr(start + 2, '}');
	if (!end_brace)
	{
		free(part);
		return (ft_strdup(""));
	}
	len = end_brace - (start + 2);
	if (len == 0)
	{
		free(part);
		return (ft_strdup(""));
	}
	var_name = ft_substr(start + 2, 0, len);
	var_value = get_env_value(env, var_name);
	free(var_name);
	return (ft_concat(start, part, var_value, len + 3));
}
