/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:57:13 by lgertrud          #+#    #+#             */
/*   Updated: 2025/05/10 18:29:35 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_puthex(unsigned long n);
int		ft_hex_len(unsigned long n);

int	ft_print_pointer(void *ptr)
	{
	unsigned long	addr;
	int				count;

	addr = (unsigned long)ptr;
	if (!addr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	count = 0;
	count += write(1, "0x", 2);
	ft_puthex(addr);
	count += ft_hex_len(addr);
	return (count);
}

void	ft_puthex(unsigned long n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
		ft_puthex(n / 16);
	write(1, &hex[n % 16], 1);
}

int	ft_hex_len(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}
