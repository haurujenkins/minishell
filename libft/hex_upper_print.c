/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_upper_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:18:48 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/12 16:30:40 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	putnbr_hex_upper(unsigned int n)
{
	static char	*hex_digits = "0123456789ABCDEF";

	if (n >= 16)
		if (putnbr_hex_upper(n / 16) == -1)
			return (-1);
	if (char_print(hex_digits[n % 16]) == -1)
		return (-1);
	return (1);
}

int	hex_upper_print(long num)
{
	int				i;

	i = 0;
	if (num == 0)
		i = 1;
	if (putnbr_hex_upper(num) != -1)
	{
		if (num < 0)
			num *= -1;
		while (num > 0)
		{
			num /= 16;
			i++;
		}
		return (i);
	}
	return (-1);
}
