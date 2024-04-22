/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:38:28 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/19 15:11:06 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_without_delim(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
		{
			i += 3;
			while (s[i] != ' ' && s[i])
				i++;
			while (s[i] == ' ')
				i++;
		}
		else if (s[i])
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*sup_delim(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = len_without_delim(s);
	tmp = malloc((len + 1) * sizeof(char));
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
		{
			i += 3;
			while (s[i] != ' ' && s[i])
				i++;
			while (s[i] == ' ')
				i++;
		}
		else if (s[i])
		{
			tmp[j] = s[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	free(s);
	return (tmp);
}

char	*fill_delimiter(char *temp_args, t_data *da)
{
	char	*args;

	while (temp_args[da->in_delim])
	{
		if (temp_args[da->in_delim] == '<' && temp_args[da->in_delim + 1] == '<')
		{
			da->in_delim += 2;
			if (temp_args[da->in_delim] == ' ')
			{
				da->in_delim++;
				while (temp_args[da->in_delim] == ' ')
					da->in_delim++;
				if (temp_args[da->in_delim] == 34)
				{
					da->in_delim++;
					args = cpy_until_char(temp_args, 34, da->in_delim);
					while (temp_args[da->in_delim] != 34 && temp_args[da->in_delim])
						da->in_delim++;
					return (args);
				}
				else
				{
					args = cpy_until_char(temp_args, ' ', da->in_delim);
					return (args);
				}
			}
			else if (temp_args[da->in_delim] == 34)
			{
				da->in_delim++;
				args = cpy_until_char(temp_args, 34, da->in_delim);
				while (temp_args[da->in_delim] != 34 && temp_args[da->in_delim])
					da->in_delim++;
				return (args);
			}
			else if (ft_isprint(temp_args[da->in_delim]) == 1)
			{
				args = cpy_until_char(temp_args, ' ', da->in_delim);
				if (if_finish_quotes(args) == 1)
					return (NULL);
				return (args);
			}
		}
		da->in_delim++;
	}
	return (NULL);
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

void	fill_delim_tab(t_data *da, char **temp_args)
{
	int	i;
	int	j;

	i = 0;
	da->in_delim = 0;
	da->delim_tab = malloc(da->pnum * sizeof(char **));
	while (i < da->pnum)
	{
		j = 0;
		da->nb_delim = ft_nb_delim(temp_args[i]);
		da->delim_tab[i] = malloc((da->nb_delim + 1) * sizeof(char *));
		if (da->nb_delim == 0)
			da->delim_tab[i][j] = NULL;
		else
		{
			while (j < da->nb_delim)
			{
				da->delim_tab[i][j] = fill_delimiter(temp_args[i], da);
				if (da->delim_tab[i][j])
					j++;
			}
			da->delim_tab[i][j] = NULL;
		}
		i++;
	}
}
