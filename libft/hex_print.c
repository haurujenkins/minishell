/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:00:22 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/12 16:30:42 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	putnbr_hex(size_t n)
{
	static char	*hex_digits = "0123456789abcdef";

	if (n >= 16)
		if (putnbr_hex(n / 16) == -1)
			return (-1);
	if (char_print(hex_digits[n % 16]) == -1)
		return (-1);
	return (1);
}

int	hex_print(size_t ptr)
{
	int		i;

	if (ptr == 0)
	{
		return (write(1, "(nil)", 5));
	}
	if (write(1, "0x", 2) == -1)
		return (-1);
	i = 2;
	if (putnbr_hex(ptr) != -1)
	{
		while (ptr > 0)
		{
			ptr /= 16;
			i++;
		}
		return (i);
	}
	return (-1);
}
