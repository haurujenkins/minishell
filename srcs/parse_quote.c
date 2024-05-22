/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:58:08 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/21 14:11:40 by abolea           ###   ########.fr       */
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
	
	i = 0;
	j = 0;
	d_quotes = 0;
	s_quotes = 0;
	tmp = malloc((ft_strlen(s) - nb_quotes(s)- if_double_space(s) + 1) * sizeof(char));
	while (s[i])
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
	while (s[i])
	{
		if (s[i] == 39)
			i++;
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	if_quotes(char *s, int start)
{
	while (s[start] != ' ' && s[start])
	{
		if (s[start] == 34)
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

void	if_quotes_not_close(char **temp_args, int i)
{
	int	j;
	int k;
	int	d_quote;
	int s_quote;

	j = 0;
	d_quote = 0;
	s_quote = 0;
	while (temp_args[i][j])
	{
		if (temp_args[i][j] == 39 || temp_args[i][j] == 34)
		{
			k = j + k;
			if (temp_args[i][j] == 39 && d_quote % 2 == 0)
			{
				s_quote++;
				while (temp_args[i][k])
				{
					if (temp_args[i][k] == 39)
					{
						s_quote++;
						break ;
					}
					else if (temp_args[i][k] == 0)
						exit(write(2, "Error : simple quote not close\n", 31));
					k++;
				}
			}
			else if (temp_args[i][j] == 34 && s_quote % 2 == 0)
			{
				d_quote++;
				while (temp_args[i][k])
				{
					if (temp_args[i][k] == 34)
					{
						d_quote++;
						break ;
					}
					else if (temp_args[i][k] == 0)
						exit(write(2, "Error : double quote not close\n", 31));
					k++;
				}
			}
		}
		j++;
	}
	return ;
}
