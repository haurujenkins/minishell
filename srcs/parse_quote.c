/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:58:08 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/28 13:59:53 by abolea           ###   ########.fr       */
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

char	*cpy_args_without_quotes(char *s)
{
	int		i;
	int		j;
	char	*tmp;
	int		d_quotes;
	int		s_quotes;
	int		len;
	
	i = 0;
	j = 0;
	len = ft_strlen(s);
	d_quotes = 0;
	s_quotes = 0;
	tmp = malloc(1 + ((int)ft_strlen(s) - nb_quotes_in_quotes(s)) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (i < len)
	{
		while ((s[i] == 34 && s_quotes % 2 == 0) || (s[i] == 39 && d_quotes % 2 == 0))
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
	free(s);
	return (tmp);
}

char	*cpy_args_without_s_quotes(char *s)
{
	int		i;
	int		j;
	char	*tmp;
	
	i = 0;
	j = 0;
	tmp = malloc((ft_strlen(s) - nb_quotes(s) + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		if (s[i] == 39)
			i++;
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free (s);
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
	while(s[start])
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

int	simple_quote_close(char *temp_args)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (temp_args[i])
	{
		if (temp_args[i] == 34 && s_quote % 2 == 0)
			d_quote++;
		if (temp_args[i] == 39 && d_quote % 2 == 0)
		{
			i++;
			s_quote++;
			while (temp_args[i])
			{
				if (temp_args[i] == 39)
				{
					s_quote++;
				}
				i++;
			}
		}
		i++;
	}
	if (s_quote % 2 != 0)
		return (0);
	return (1);
}

int	double_quotes_close(char *temp_args)
{
	int	i;
	int s_quote;
	int d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (temp_args[i])
	{
		if (temp_args[i] == 39 && d_quote % 2 == 0)
			s_quote++;
		if (temp_args[i] == 34 && s_quote % 2 == 0)
		{
			i++;
			d_quote++;
			while (temp_args[i])
			{
				if (temp_args[i] == 34)
				{
					d_quote++;
				}
				i++;
			}
		}
		i++;
	}
	if (d_quote % 2 != 0)
		return (0);
	return (1);
}
