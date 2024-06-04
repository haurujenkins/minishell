/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:58:08 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/04 16:08:18 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_double_space(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ' ' && s[i + 1] == ' ')
			j++;
		i++;
	}
	return (j);
}

char	*cpy_tmp_without_quotes(char *s, char *tmp, int s_quotes, int d_quotes)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = (int)ft_strlen(s);
	while (i < len)
	{
		while ((s[i] == 34 && s_quotes % 2 == 0) \
		|| (s[i] == 39 && d_quotes % 2 == 0))
		{
			if (s[i] == 34 && s_quotes % 2 == 0)
				d_quotes++;
			if (s[i] == 39 && d_quotes % 2 == 0)
				s_quotes++;
			i++;
		}
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*cpy_args_without_quotes(char *s)
{
	char	*tmp;
	int		d_quotes;
	int		s_quotes;

	d_quotes = 0;
	s_quotes = 0;
	tmp = malloc(((int)ft_strlen(s) - \
	nb_quotes_in_quotes(s)) * sizeof(char) + 1);
	if (!tmp)
		return (NULL);
	tmp = cpy_tmp_without_quotes(s, tmp, s_quotes, d_quotes);
	free(s);
	return (tmp);
}

int	if_quotes(char *s, int start)
{
	while (s[start] != ' ' && s[start])
	{
		if (s[start] == 34 || s[start] == 39)
			return (1);
		start++;
	}
	return (0);
}

int	if_io_before_last_quotes(char *s, char c, int start)
{
	while (s[start])
	{
		if (s[start] == 34)
		{
			start++;
			while (s[start] != 34 && s[start])
				start++;
			if (s[start] == 34 && s[start - 1] == c)
				return (1);
		}
		start++;
	}
	return (0);
}
