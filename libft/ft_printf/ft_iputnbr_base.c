/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iputnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgertrud <lgertrud@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:39:59 by lgertrud          #+#    #+#             */
/*   Updated: 2025/05/10 18:29:28 by lgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnum(long n, int base);
int		ft_dec_len(long n, int base);

int	ft_iputnbr_base(int nbr, int base)
{
	int		count;
	long	nb;

	nb = nbr;
	if (nbr < 0 && base != 0)
		nb = 4294967296 + nbr;
	if (base == 3)
		base = 0;
	count = 0;
	ft_putnum(nb, base);
	count += ft_dec_len(nb, base);
	return (count);
}

void	ft_putnum(long n, int base)
{
	char	*bas[3];
	int		bas_num;

	bas[0] = "0123456789";
	bas[1] = "0123456789ABCDEF";
	bas[2] = "0123456789abcdef";
	if (base == 0)
		bas_num = 10;
	else
		bas_num = 16;
	if (n < 0)
	{
		write(1, "-", 1);
		n = n * -1;
	}
	if ((long)n >= bas_num)
	{
		ft_putnum((n / bas_num), base);
		ft_putnum((n % bas_num), base);
	}
	if ((long)n < bas_num)
		write (1, &bas[base][n % bas_num], 1);
}

int	ft_dec_len(long n, int base)
{
	int	len;
	int	bas;

	len = 0;
	bas = 0;
	if (base == 0)
		bas = 10;
	else
		bas = 16;
	if (n < 0)
	{
		len ++;
		n *= -1;
	}
	if (n == 0)
		return (1);
	while (n)
	{
		n /= bas;
		len++;
	}
	return (len);
}
