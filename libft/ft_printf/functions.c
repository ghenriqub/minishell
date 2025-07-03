/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:11:25 by lgertrud          #+#    #+#             */
/*   Updated: 2025/05/10 18:29:44 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_sign(char c, va_list args)
{
	int		count;
	void	*ptr;

	count = 0;
	if (c == '%')
		count += ft_iputchar_fd('%', 1);
	if (c == 'c')
		count += ft_iputchar_fd(va_arg(args, int), 1);
	if (c == 's')
		count += ft_iputstr_fd(va_arg(args, char *), 1);
	if (c == 'd' || c == 'i')
		count += ft_iputnbr_base(va_arg(args, int), 0);
	if (c == 'u')
		count += ft_iputnbr_base(va_arg(args, unsigned int), 3);
	if (c == 'X')
		count += ft_iputnbr_base(va_arg(args, int), 1);
	if (c == 'x')
		count += ft_iputnbr_base(va_arg(args, int), 2);
	if (c == 'p')
	{
		ptr = va_arg(args, void *);
		count = ft_print_pointer(ptr);
	}
	return (count);
}
