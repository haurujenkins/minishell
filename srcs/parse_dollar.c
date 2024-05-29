/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:22 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/29 15:05:45 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nb_dollars(char *s)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (s[i])
	{
		if (s[i] == '$' && (ft_isalnum(s[i + 1]) == 1 || s[i + 1] == '?' || s[i + 1] == 39 || s[i + 1] == 34))
			d++;
		i++;
	}
	return (d);
}

int	len_after_dollar(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '$')
		i++;
	if (i > 1)
	{
		if (s[i - 1] != 39)
			j++;
	}
	i++;
	while (ft_isalnum(s[i]) == 1 || s[i] == '?')
	{
		i++;
		j++;
	}
	return (j);
}

int	nb_after_dollar(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[0]) == 1)
		return (1);
	while (s[i])
	{
		if (s[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

int	len_after_digit(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_isdigit(s[0]) == 1)
	{
		i++;
		while (s[i])
		{
			j++;
			i++;
		}
		return (j);	
	}
	while (s[i] != 39)
		i++;
	i++;
	while (s[i])
	{
		j++;
		i++;
	}
	return (j);
}
char	*cpy_after_digit(char *s, char *res)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	i++;
	while (s[i])
	{
		res[j] = s[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);	
}
