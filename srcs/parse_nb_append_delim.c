/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nb_append_delim.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:58:23 by abolea            #+#    #+#             */
/*   Updated: 2024/05/29 13:59:20 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_without_append(char *s)
{
	int		i;
	int		j;
	int		in_quotes;

	i = 0;
	j = 0;
	in_quotes = 1;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			in_quotes *= -1;
		if ((s[i] == '>' && s[i + 1] == '>') && in_quotes > 0)
			i++;
		else if (s[i])
		{
			i++;
			j++;
		}
	}
	return (j);
}

int	ft_nb_append(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			i++;
			while (s[i] != 34 && s[i])
				i++;
		}
		if (s[i] == '>' && s[i + 1] == '>')
			j++;
		i++;
	}
	return (j);
}

int	len_without_delim(char *s)
{
	int		i;
	int		j;
	int		in_quotes;

	i = 0;
	j = 0;
	in_quotes = 1;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			in_quotes *= -1;
		if ((s[i] == '<' && s[i + 1] == '<') && in_quotes > 0)
			i++;
		else if (s[i])
		{
			i++;
			j++;
		}
	}
	return (j);
}

int	ft_nb_delim(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == 34)
		{
			i++;
			while (s[i] != 34 && s[i])
				i++;
		}
		if (s[i] == '<' && s[i + 1] == '<')
			j++;
		i++;
	}
	return (j);
}
