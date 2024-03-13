/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:44:36 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/18 14:24:52 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((unsigned char)s1[i] && (unsigned char)s1[i] \
	== (unsigned char)s2[i] && i < n)
	{
		i++;
	}
	if (n == i)
		i--;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
