/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:45:03 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/18 14:24:58 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (little == NULL && big == NULL)
		return (NULL);
	little_len = ft_strlen((char *)little);
	if (little_len == 0)
		return ((char *)big);
	while (*big && len >= little_len)
	{
		if (*big == *little && ft_strncmp(big, little, little_len) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
