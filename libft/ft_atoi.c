/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:45:16 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/24 17:30:10 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

int	ft_atoi(const char *nptr)
{
	long long	sign;
	long long	number;

	sign = 1;
	number = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		sign *= -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (number > (LONG_MAX - (*nptr - '0')) / 10)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		number = number * 10 + *nptr - '0';
		nptr++;
	}
	return (number * sign);
}
