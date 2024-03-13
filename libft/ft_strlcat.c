/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:20:49 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/18 14:24:39 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = ft_strlen((char *)dst);
	len_src = ft_strlen((char *)src);
	i = 0;
	if (!size)
		return (len_src);
	while (src[i] && (len_dst + i) < (size - 1))
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	if (size - 1 < len_dst)
		return (len_src + size);
	return (len_src + len_dst);
}
