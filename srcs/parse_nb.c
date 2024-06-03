/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:03:17 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/03 14:51:04 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nb_pipe(char *rl)
{
	int	pnum;
	int	i;

	i = 0;
	pnum = 1;
	while (rl[i])
	{
		if (rl[i] == 34 || rl[i] == 39)
		{
			i++;
			while ((rl[i] != 34 && rl[i] != 39) && rl[i])
				i++;
		}
		if (rl[i] == '|')
			pnum++;
		i++;
	}
	return (pnum);
}

int	nb_io(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if ((s[i] == '<' || s[i] == '>') && (s[i + 1] == '<' \
		|| s[i + 1] == '>'))
			j++;
		i++;
	}
	return (j);
}

int	ft_nb_redir(char *temp_args, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (temp_args[i])
	{
		if (temp_args[i] == 34 || temp_args[i] == 39)
		{
			i++;
			while ((temp_args[i] != 34 && temp_args[i] != 39) && temp_args[i])
				i++;
		}
		if (temp_args[i] == c && temp_args[i + 2])
			nb++;
		i++;
	}
	return (nb);
}

int	nb_quotes_in_quotes(char *s)
{
	int	count;
	int	in_squote;
	int	in_dquote;

	count = 0;
	in_squote = 0;
	in_dquote = 0;
	while (*s)
	{
		if (*s == 39 && !in_dquote)
			in_squote = !in_squote;
		else if (*s == 34 && !in_squote)
			in_dquote = !in_dquote;
		else if ((*s == 39 || *s == 34) && !in_squote && !in_dquote)
			count++;
		s++;
	}
	return (count);
}

int	nb_quotes(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] == 34)
			res++;
		i++;
	}
	return (res);
}
