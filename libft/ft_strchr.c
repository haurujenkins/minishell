/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:46:20 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/18 14:53:45 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_strchr(char *str, char *cmp)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (str == NULL || cmp == NULL)
		return (0);
	if (cmp[y] == '\0' && str[i] == '\0')
		return (1);
	while (str[i])
	{
		while (str[i + y] == cmp[y] && str[i + y] && cmp[y])
			y++;
		if (cmp[y] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}
