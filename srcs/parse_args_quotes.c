/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:18:58 by abolea            #+#    #+#             */
/*   Updated: 2024/05/29 15:19:41 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cpy_in_res_without_d_quotes(char *res, char *s)
{
	int		i;
	int		j;
	int		d_quotes;

	i = 0;
	j = 0;
	d_quotes = 0;
	while (s[i])
	{
		if (s[i] == 34 && s[i + 1] == '$')
		{
			i++;
			d_quotes++;
		}
		res[j] = s[i];
		j++;
		i++;
		if (s[i] == 34 && d_quotes > 0 && d_quotes % 2 != 0)
		{
			i++;
			d_quotes++;
		}
	}
	res[j] = '\0';
	return (res);
}

char	*cpy_res_with_s_quotes(char *tmp, char *s, int i, int j)
{
	int	len;

	i = 0;
	while (ft_isalnum(s[i]) != 1)
		i++;
	len = i;
	i = 0;
	while (s[i])
	{
		if (i > len && s[i] == 34)
		{
			tmp[j] = 39;
			j++;
		}
		tmp[j] = s[i];
		j++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*add_s_quote(char *s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (i > 1)
	{
		if (s[i - 1] != 39)
			return (s);
	}
	i = 0;
	tmp = malloc((ft_strlen(s) + 2) * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = cpy_res_with_s_quotes(tmp, s, i, j);
	free (s);
	return (tmp);
}

int	if_nb_dollar(char **temp_args, int i)
{
	temp_args[i] = sup_d_quotes_before_dollar(temp_args[i]);
	if (!temp_args)
		return (1);
	temp_args[i] = sup_dollar_before_quotes(temp_args[i]);
	if (!temp_args)
		return (1);
	return (0);
}

int	sup_append_and_delim(char **temp_args, int i)
{
	temp_args[i] = sup_delim(temp_args[i]);
	if (temp_args[i] == NULL)
		return (1);
	temp_args[i] = sup_append(temp_args[i]);
	if (temp_args[i] == NULL)
		return (1);
	return (0);
}
