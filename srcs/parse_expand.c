/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:00:55 by abolea            #+#    #+#             */
/*   Updated: 2024/06/04 14:32:02 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_chars_after_dollar(char *temp_args, int *i)
{
	while (temp_args[*i] != ' ' && temp_args[*i] != '$' \
	&& isalnum(temp_args[*i]) && temp_args[*i])
		(*i)++;
}

void	copy_remaining(char *res, char *temp_args, int *i, int *j)
{
	while (temp_args[*i])
	{
		res[*j] = temp_args[*i];
		(*i)++;
		(*j)++;
	}
}

char	*cpy_in_res(char *res, char *temp_args, char *new_args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	copy_until_dollar(res, temp_args, &i, &j);
	copy_new_args(res, new_args, &j);
	cpy_interrogation(res, temp_args, &i, &j);
	skip_chars_after_dollar(temp_args, &i);
	copy_remaining(res, temp_args, &i, &j);
	res[j] = '\0';
	return (res);
}

char	*if_res_is_null(char *before_args, char *temp_args, char *new_args)
{
	write(2, "Malloc failed\n", 14);
	free(before_args);
	free(temp_args);
	free(new_args);
	return (NULL);
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

char	*temp_without_dollar(t_data *da, char *temp_args)
{
	int		len;
	char	*new_args;
	char	*before_args;
	char	*res;

	new_args = NULL;
	if_export(temp_args, da);
	before_args = after_dollar(temp_args);
	if (before_args == NULL)
		return (temp_args);
	new_args = return_new_args(new_args, before_args, da);
	if (!new_args)
		if_not_new_args(before_args);
	len = (ft_strlen(temp_args) - ft_strlen(before_args) + \
	ft_strlen(new_args) + 1);
	res = malloc((len) * sizeof(char));
	if (res == NULL)
		if_res_is_null(before_args, temp_args, new_args);
	res = cpy_in_res(res, temp_args, new_args);
	if (new_args[0] == 39 && new_args[1] != '$' && new_args )
		da->s_args = 1;
	else if (new_args && da->if_export == 0)
	{
		res = cpy_args_without_quotes(res);
		da->if_expand = 1;
	}
	free_all(new_args, temp_args, before_args);
	return (res);
}
