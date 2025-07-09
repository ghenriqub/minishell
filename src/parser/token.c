/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:25:51 by lgertrud          #+#    #+#             */
/*   Updated: 2025/07/09 20:41:17 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token);

/// @brief init token and call built functons
/// @param line is the param that user write
/// @return the token created
t_token	*ft_tokenizer(char *line)
{
	t_token	*token;

	token = ft_init_token(line);
	print_token(token);
	return (token);
}

/// @brief 
/// @param token 
/// @return 
t_token	*ft_init_token(char *line)
{
	t_token	*head;
	t_token	*current;
	t_token	*new;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
		{
			new = malloc(sizeof(t_token));
			if (!new)
				return (NULL);
			if ((line[i] == '>' && line[i + 1] == '>')
				|| (line[i] == '<' && line[i + 1] == '<'))
			{
				new->value = ft_substr(line, i, 2);
				i += 2;
			}
			else if (ft_is_delimiter(line[i]))
			{
				new->value = ft_substr(line, i, 1);
				i++;
			}
			else
				new->value = ft_get_value(line, &i);
			new->type = ft_get_type(new->value);
			new->next = NULL;
			if (!head)
			{
				head = new;
				current = new;
			}
			else
			{
				current->next = new;
				current = new;
			}
		}
	}
	return (head);
}

/// @brief Extracts the next token
///			(word or quoted string) from the input string.
/// @param s The input string to parse.
/// @param i A pointer to the current position in the string (will be updated).
/// @return A newly allocated substring containing the extracted token.
char	*ft_get_value(const char *s, int *i)
{
	char	*result;
	char	*part;
	char	quote;
	int		start;
	int		len;
	char	*tmp;

	result = NULL;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && !ft_is_delimiter(s[*i]))
	{
		if (s[*i] == '"' || s[*i] == '\'')
		{
			quote = s[(*i)++];
			start = *i;
			len = 0;
			while (s[*i] && s[*i] != quote)
			{
				(*i)++;
				len++;
			}
			(*i) += (s[*i] == quote);
			part = ft_substr(s, start, len);
		}
		else
		{
			start = *i;
			while (s[*i] && s[*i] != '"' && s[*i] != '\'' && s[*i] != ' '
				&& s[*i] != '\t' && !ft_is_delimiter(s[*i]))
				(*i)++;
			part = ft_substr(s, start, *i - start);
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

/// @brief this functions define the type of the value
/// @param value value of type that we will find
/// @return The type of the argument
t_type	ft_get_type(char *value)
{
	if (!ft_strncmp(">>", value, ft_strlen(value)))
		return (T_APPEND);
	else if (!ft_strncmp(">", value, ft_strlen(value)))
		return (T_REDIRECT_OUT);
	else if (!ft_strncmp("<", value, ft_strlen(value)))
		return (T_REDIRECT_IN);
	else if (!ft_strncmp("|", value, ft_strlen(value)))
		return (T_PIPE);
	else if (!ft_strncmp("<<", value, ft_strlen(value)))
		return (T_HEREDOC);
	else
		return (T_WORD);
}

int	ft_is_delimiter(char c)
{
	return (c == '>' || c == '<' || c == '|');
}
