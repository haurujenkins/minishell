/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:41:49 by lle-pier          #+#    #+#             */
/*   Updated: 2023/11/14 15:47:05 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*myspace;
	size_t	i;

	i = 0;
	if (nmemb == 0 || size == 0)
	{
		myspace = malloc(0);
		if (myspace == NULL)
			return (NULL);
		myspace[0] = 0;
		return (myspace);
	}
	if ((nmemb * size) > (size_t) - 1)
		return (NULL);
	myspace = malloc(nmemb * size);
	if (myspace == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		myspace[i] = 0;
		i++;
	}
	return (myspace);
}
