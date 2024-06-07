/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cpy_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:14:05 by abolea            #+#    #+#             */
/*   Updated: 2024/06/07 12:49:14 by abolea           ###   ########.fr       */
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

char	*if_not_export(char *res, t_data *da)
{
	res = cpy_args_without_quotes(res);
	if (!res)
		return (NULL);
	da->if_expand = 1;
	return (res);
}

char	*if_export_or_not(char *res, char *new_args, t_data *da)
{
	if ((new_args[0] == 39 || new_args[0] == 34) \
	&& new_args[1] != '$' && new_args)
		da->s_args = 1;
	else if (new_args && da->if_export == 0)
		res = if_not_export(res, da);
	return (res);
}

void	if_export(char *s, t_data *da)
{
	int	i;

	i = 0;
	if (s[i] == 'e')
		i++;
	if (s[i] == 'x')
		i++;
	if (s[i] == 'p')
		i++;
	if (s[i] == 'o')
		i++;
	if (s[i] == 'r')
		i++;
	if (s[i] == 't')
		i++;
	if (s[i] == ' ')
		i++;
	if (i == 7)
		da->if_export = 1;
	else
		da->if_export = 0;
	return ;
}
