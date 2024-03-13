/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:20:22 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/18 14:24:15 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = (char *) s;
	i = 0;
	while (i < n)
	{
		tmp[i] = c;
		i++;
	}
	return (s);
}
