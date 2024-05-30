/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sup_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:25:21 by abolea            #+#    #+#             */
/*   Updated: 2024/05/30 15:12:56 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_without_double_space(char *s)
{
	int		i;
	int		j;
	int		d_quotes;
	int		s_quotes;

	i = 0;
	j = 0;
	s_quotes = 1;
	d_quotes = 1;
	while (s[i])
	{
		if (s[i] == 34 && s_quotes > 0)
			d_quotes *= -1;
		if (s[i] == 39 && d_quotes > 0)
			s_quotes *= -1;
		if (s[i] == ' ' && s[i + 1] == ' ' && d_quotes > 0 && s_quotes > 0)
			i++;
		else if (s[i])
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*cpy_without_double_spaces(char *s, char *tmp, int i)
{
	int		j;
	int		d_quotes;
	int		s_quotes;

	j = 0;
	d_quotes = 1;
	s_quotes = 1;
	while (s[i])
	{
		if (s[i] == 34 && s_quotes > 0)
			d_quotes *= -1;
		if (s[i] == 39 && d_quotes > 0)
			s_quotes *= -1;
		if (s[i] == ' ' && s[i + 1] == ' ' && d_quotes > 0 && s_quotes > 0)
			i++;
		else if (s[i])
		{
			tmp[j] = s[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*sup_double_space(char *s)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = len_without_double_space(s);
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = cpy_without_double_spaces(s, tmp, i);
	free (s);
	return (tmp);
}

char	*cpy_tmp_with_space(char *s, char *tmp, int in_quotes, int i)
{
	int		j;

	j = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			in_quotes *= -1;
		if (s[i] == '<' && in_quotes == 1)
		{
			tmp[j++] = ' ';
			tmp[j++] = '<';
			tmp[j++] = ' ';
		}
		else if (s[i] == '>' && in_quotes == 1)
		{
			tmp[j++] = ' ';
			tmp[j++] = '>';
			tmp[j++] = ' ';
		}
		else
			tmp[j++] = s[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*temp_with_space(char *s)
{
	int		len;
	char	*tmp;
	int		in_quotes;
	int		i;

	len = ft_strlen(s);
	tmp = (char *)malloc((2 * len + 1) * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	in_quotes = 1;
	tmp = cpy_tmp_with_space(s, tmp, in_quotes, i);
	free (s);
	return (tmp);
}
