/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cpy_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:03:06 by abolea            #+#    #+#             */
/*   Updated: 2024/05/29 15:04:17 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*if_not_new_args(char *before_args)
{
	free(before_args);
	return (NULL);
}

char	*return_new_args(char *new_args, char *before_args, t_data *da)
{
	if (nb_after_dollar(before_args) == 1)
	{
		new_args = recup_after_digit(before_args);
		if (!new_args)
			if_not_new_args(before_args);
	}
	else if (before_args[0] == '?')
	{
		new_args = ft_itoa(da->exit_status);
		if (!new_args)
			if_not_new_args(before_args);
	}
	else
	{
		new_args = find_in_env(da, before_args);
		if (!new_args)
			if_not_new_args(before_args);
	}
	if (new_args[0] == 39)
	{
		new_args = add_d_quotes_newargs(new_args);
		if (!new_args)
			if_not_new_args(before_args);
	}
	return (new_args);
}

void	copy_until_dollar(char *res, char *temp_args, int *i, int *j)
{
	while (temp_args[*i] != '$')
	{
		res[*j] = temp_args[*i];
		(*i)++;
		(*j)++;
	}
}

void	copy_new_args(char *res, char *new_args, int *j)
{
	int k;

	k = 0;
	while (new_args[k])
	{
		res[*j] = new_args[k];
		(*j)++;
		k++;
	}
}

void	cpy_interrogation(char *res, char *temp_args, int *i, int *j)
{
	(*i)++;
	if (temp_args[*i] == '?')
	{
		(*i)++;
		while (temp_args[*i]) {
			res[*j] = temp_args[*i];
			(*i)++;
			(*j)++;
		}
	}
}
