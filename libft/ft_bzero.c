/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:22:17 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/18 14:23:36 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = (char *) s;
	i = 0;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
}
