/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:36:38 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/12 16:30:37 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		if (char_print('-') == -1 || char_print('2') == -1)
			return (-1);
		n = 147483648;
	}
	if (n < 0)
	{
		if (char_print('-') == -1)
			return (-1);
		n *= -1;
	}
	if (n >= 10)
	{
		if (ft_putnbr(n / 10) == -1)
			return (-1);
		if (ft_putnbr(n % 10) == -1)
			return (-1);
	}
	else
	{
		return (char_print(n + '0'));
	}
	return (1);
}

int	int_print(int n)
{
	int	nb;
	int	i;

	i = 1;
	nb = n;
	if (n < 0 || n == -2147483648)
	{
		nb = -n;
		i++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	if (ft_putnbr(n) == -1)
		return (-1);
	if (n == -2147483648)
		return (11);
	return (i);
}
