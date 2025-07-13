/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:48:31 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/13 19:37:08 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_value_2(t_shell *shell, const char *s, int *i);
static char	*ft_expand_variables(char *part, t_shell *shell, char quote);

/// @brief Extracts the next token
///			(word or quoted string) from the input string.
/// @param s The input string to parse.
/// @param i A pointer to the current position in the string (will be updated).
/// @return A newly allocated substring containing the extracted token.
char	*ft_get_value(t_shell *shell, const char *s, int *i)
{
	char	*result;
	char	*part;
	char	*tmp;

	result = NULL;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && !ft_is_delimiter(s[*i]))
	{
		part = ft_get_value_2(shell, s, i);
		if (!part)
		{
			free(result);
			return (NULL);
		}
		tmp = result;
		if (result)
			result = ft_strjoin(result, part);
		else
			result = ft_strdup(part);
		free(tmp);
		free(part);
	}
	return (result);
}

/// @brief Extracts a single token part:
///			either a quoted string or a plain word fragment.
///       	 Handles opening/closing quotes and
///				advances the parsing index accordingly.
/// @param s The input string being parsed.
/// @param i A pointer to the current index in the string. Will be updated.
/// @return A newly allocated substring for this part
///				or NULL if unterminated quote or malloc fails.
static char	*ft_get_value_2(t_shell *shell, const char *s, int *i)
{
	int		start;
	char	quote;
	char	*part;
	char	*pointer;

	if (s[*i] == '"' || s[*i] == '\'')
	{
		quote = s[(*i)++];
		start = *i;
		while (s[*i] && s[*i] != quote)
			(*i)++;
		if (s[*i] != quote)
			return (NULL);
		part = ft_substr(s, start, (*i)++ - start);
	}
	else
	{
		start = *i;
		while (s[*i] && s[*i] != '"' && s[*i] != '\''
			&& s[*i] != ' ' && s[*i] != '\t' && !ft_is_delimiter(s[*i]))
			(*i)++;
		part = ft_substr(s, start, *i - start);
	}
	part = ft_expand_variables(part, shell, quote);
	return (part);
}

static char	*ft_expand_variables(char *part, t_shell *shell, char quote)
{
	char	*pointer;

	while (quote != '\'' && ft_strchr(part, '$'))
	{
		pointer = ft_strchr(part, '$');
		if (!pointer[1] || pointer[1] == ' ' || ft_is_delimiter(pointer[1]))
			break ;
		part = ft_get_variable(shell->env, part, shell->exit_status);
	}
	return (part);
}

/// @brief this functions define the type of the value
/// @param value value of type that we will find
/// @return The type of the argument
t_type	ft_get_type(char *value)
{
	if (!ft_strncmp(">", value, ft_strlen(value)) && value[0])
		return (T_REDIRECT_OUT);
	else if (!ft_strncmp(">>", value, ft_strlen(value)) && value[0])
		return (T_APPEND);
	else if (!ft_strncmp("<", value, ft_strlen(value)) && value[0])
		return (T_REDIRECT_IN);
	else if (!ft_strncmp("|", value, ft_strlen(value)) && value[0])
		return (T_PIPE);
	else if (!ft_strncmp("<<", value, ft_strlen(value)) && value[0])
		return (T_HEREDOC);
	else
		return (T_WORD);
}

/// @brief if the param is a delimiter, return 1 else 0
int	ft_is_delimiter(char c)
{
	return (c == '>' || c == '<' || c == '|');
}
