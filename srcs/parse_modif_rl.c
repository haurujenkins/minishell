/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_modif_rl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:54:40 by abolea            #+#    #+#             */
/*   Updated: 2024/05/29 13:27:29 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_in_s_quotes(char *s, int *i)
{
	(*i)++;
	while (s[*i] && s[*i] != 39)
	{
		if (s[*i] == ' ' || s[*i] == '|')
			s[*i] *= -1;
		(*i)++;
	}
}

char	*negative_in_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			i++;
			while (s[i] && s[i] != 34)
			{
				if (s[i] == ' ' || s[i] == '|')
					s[i] *= -1;
				i++;
			}
		}
		else if (s[i] == 39)
			if_in_s_quotes(s, &i);
		i++;
	}
	return (s);
}

char	*all_positive(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < 0)
			s[i] *= -1;
		i++;
	}
	return (s);
}

char	*dollar_negative_in_s_quote(char *s)
{
	int	i;
	int	d_quotes;

	i = 0;
	d_quotes = 1;
	while (s[i])
	{
		if (s[i] == 34)
			d_quotes *= -1;
		if (s[i] == 39 && d_quotes > 0)
		{
			i++;
			while (s[i] != 39)
			{
				if (s[i] == '$')
					s[i] *= -1;
				i++;
			}
		}
		i++;
	}
	s[i] = '\0';
	return (s);
}
