/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iputstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:33:38 by lgertrud          #+#    #+#             */
/*   Updated: 2025/05/10 18:29:32 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_iputstr_fd(char *s, int fd)
{
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write (fd, s, ft_strlen(s));
	return (ft_strlen(s));
}
