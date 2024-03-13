/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:42:57 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/12 16:30:31 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	putunbr(unsigned int number)
{
	if (number >= 10)
		if (putunbr(number / 10) == -1)
			return (-1);
	return (char_print(number % 10 + '0'));
}

int	uint_print(unsigned int n)
{
	int				i;
	unsigned int	temp;

	i = 0;
	temp = n;
	if (n == 0)
	{
		return (char_print('0'));
	}
	while (temp > 0)
	{
		temp /= 10;
		i++;
	}
	if (putunbr(n) == -1)
		return (-1);
	return (i);
}
