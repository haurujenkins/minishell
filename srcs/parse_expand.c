/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:00:55 by abolea            #+#    #+#             */
/*   Updated: 2024/05/29 14:02:44 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_chars_after_dollar(char *temp_args, int *i)
{
	while (temp_args[*i] != ' ' && temp_args[*i] != '$' && isalnum(temp_args[*i]) && temp_args[*i])
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
	int i;
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

char	*temp_without_dollar(t_data *da, char *temp_args)
{
	int		s_quote;
	int		len;
	char	*new_args;
	char	*before_args;
	char	*res;

	new_args = NULL;
	s_quote = 0;
	before_args = after_dollar(temp_args);
	if (before_args == NULL)
		return (temp_args);
	new_args = return_new_args(new_args, before_args, da);
	if (s_quote != 0)
		return (cpy_args_without_s_quotes(temp_args));
	len = (ft_strlen(temp_args) - ft_strlen(before_args) + ft_strlen(new_args) + s_quote + 1);
	res = malloc((len) * sizeof(char));
	if (res == NULL)
		if_res_is_null(before_args, temp_args, new_args);
	res = cpy_in_res(res, temp_args, new_args);
	res = cpy_args_without_quotes(res);
	free(before_args);
	free(temp_args);
	free(new_args);
	return (res);
}
