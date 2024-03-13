/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_lower_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:23:04 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/12 16:30:44 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	putnbr_hex_lower(unsigned int n)
{
	static char	*hex_digits = "0123456789abcdef";

	if (n >= 16)
		if (putnbr_hex_lower(n / 16) == -1)
			return (-1);
	if (char_print(hex_digits[n % 16]) == -1)
		return (-1);
	return (1);
}

int	hex_lower_print(long num)
{
	int				i;

	i = 0;
	if (num == 0)
		i = 1;
	if (putnbr_hex_lower(num) != -1)
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
