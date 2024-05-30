/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:07:09 by abolea            #+#    #+#             */
/*   Updated: 2024/05/30 15:22:50 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	s_quotes_dollar(char *s)
{
	int		i;
	int		j;
	int		s_quotes;

	i = 0;
	j = 0;
	s_quotes = 0;
	while (s[i])
	{
		if (s[i] == 39 && s[i + 1] == 39 && s[i + 2] == '$')
		{
			i += 2;
			s_quotes += 2;
		}
		j++;
		i++;
	}
	return (j);
}

char	*sup_s_quotes_before_dollar(char *s)
{
	int		i;
	int		j;
	int		s_quotes;
	char	*res;

	i = 0;
	j = 0;
	s_quotes = 0;
	res = malloc((s_quotes_dollar(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] == 39 && s[i + 1] == 39 && s[i + 2] == '$')
		{
			i += 2;
			s_quotes += 2;
		}
		res[j] = s[i];
		j++;
		i++;
	}
	res[j] = '\0';
	free (s);
	return (res);
}

int	d_quotes_dollar(char *s)
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
		j++;
		i++;
		if (s[i] == 34 && d_quotes > 0 && d_quotes % 2 != 0)
		{
			i++;
			d_quotes++;
		}
	}
	return (j);
}

char	*sup_d_quotes_before_dollar(char *s)
{
	char	*res;

	res = malloc((d_quotes_dollar(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res = cpy_in_res_without_d_quotes(res, s);
	free(s);
	return (res);
}

int	len_without_dollar_before_quotes(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i > 1 && (int)ft_strlen(s) > i)
		{
			if (s[i - 1] > 0 && s[i] < 0 && (s[i + 1] == 34 || s[i + 1] == 39))
				i++;
			else
			{
				i++;
				j++;
			}
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}
