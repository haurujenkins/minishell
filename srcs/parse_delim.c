/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:38:28 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/29 13:59:14 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cpy_without_delim(char *s, char *tmp)
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
			tmp[j] = s[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	free(s);
	return (tmp);
}

char	*sup_delim(char *s)
{
	int		len;
	char	*tmp;

	len = len_without_delim(s);
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = cpy_without_delim(s, tmp);
	return (tmp);
}

char	*fill_delim(char *temp_args, t_data *da)
{
	char	*args;

	while (temp_args[da->in_delim])
	{
		if (temp_args[da->in_delim] \
		== '<' && temp_args[da->in_delim + 1] != '<')
		{
			args = ft_strdup("0");
			if (args == NULL)
				return (write(2, "Error: malloc failed\n", 21), NULL);
			da->in_delim++;
			return (args);
		}
		else if (temp_args[da->in_delim] \
		== '<' && temp_args[da->in_delim + 1] == '<')
		{
			args = ft_strdup("1");
			if (args == NULL)
				return (write(2, "Error: malloc failed\n", 21), NULL);
			da->in_delim += 2;
			return (args);
		}
		da->in_delim++;
	}
	return (NULL);
}

int	fill_delim_tab(t_data *da, char **temp_args)
{
	int	i;
	int	j;

	i = 0;
	da->delim_tab = malloc((da->pnum + 1) * sizeof(char **));
	if (da->delim_tab == NULL)
		return (write(2, "Error: malloc failed\n", 21), 1);
	while (i < da->pnum)
	{
		j = 0;
		da->in_delim = i;
		da->nb_delim = ft_nb_delim(temp_args[i]);
		da->delim_tab[i] = malloc((ft_nb_redir(temp_args[i], '<') - da->nb_delim + 1) * sizeof(char *));
		if (da->delim_tab[i] == NULL)
			return (write(2, "Error: malloc failed\n", 21), 1);
		if (da->nb_delim == 0)
			da->delim_tab[i][j] = NULL;
		else
		{
			while (j < ft_nb_redir(temp_args[i], '<') - da->nb_delim)
			{
				da->delim_tab[i][j] = fill_delim(temp_args[i], da);
				if (da->delim_tab[i][j] == NULL)
					return (1);
				j++;
			}
			da->delim_tab[i][j] = NULL;
		}
		i++;
	}
	return (0);
}
