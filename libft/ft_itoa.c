/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:25:04 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/18 14:23:52 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_number(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	size;
	long	number;

	size = count_number(n);
	number = n;
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	if (n < 0)
		number *= -1;
	if (n == 0)
		result[size - 1] = '0';
	else
	{
		while (size-- && number != 0)
		{
			result[size] = (number % 10) + '0';
			number = ((number - (number % 10)) / 10);
		}
		if (n < 0)
			result[size] = '-';
	}
	return (result);
}
