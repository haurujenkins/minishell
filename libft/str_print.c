/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:32:19 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/12 16:30:29 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_print(char *s)
{
	if (!s)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		else
			return (6);
	}
	if (write(1, s, ft_strlen(s)) < 0)
		return (-1);
	return (ft_strlen(s));
}
