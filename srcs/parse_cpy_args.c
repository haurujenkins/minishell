/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cpy_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:14:05 by abolea            #+#    #+#             */
/*   Updated: 2024/06/03 18:57:17 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*if_args_after_ok(t_data *da, char **words, char *args)
{
	if (da->i_args > 2)
	{
		args = args_after(da, words, args);
		if (args)
			return (args);
	}
	args = else_args_after(da, words, args);
	if (args)
		return (args);
	return (NULL);
}
