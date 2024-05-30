/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:28:18 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/29 13:58:50 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cpy_without_append(char *s, char *tmp)
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
			tmp[j] = s[i];
			i++;
			j++;
		}
	}
	tmp[j] = '\0';
	free(s);
	return (tmp);
}

char	*sup_append(char *s)
{
	int		len;
	char	*tmp;

	len = len_without_append(s);
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = cpy_without_append(s, tmp);
	return (tmp);
}

char	*fill_append(char *temp_args, t_data *da)
{
	char	*args;

	while (temp_args[da->o_append])
	{
		if (temp_args[da->o_append] \
		== '>' && temp_args[da->o_append + 1] != '>')
		{
			args = ft_strdup("0");
			if (args == NULL)
				return (write(2, "Error: malloc failed\n", 21), NULL);
			da->o_append++;
			return (args);
		}
		else if (temp_args[da->o_append] \
		== '>' && temp_args[da->o_append + 1] == '>')
		{
			args = ft_strdup("1");
			if (args == NULL)
				return (write(2, "Error: malloc failed\n", 21), NULL);
			da->o_append += 2;
			return (args);
		}
		da->o_append++;
	}
	return (NULL);
}

int	fill_append_tab(t_data *da, char **temp_args)
{
	int	i;
	int	j;

	i = 0;
	da->append_tab = malloc((da->pnum + 1) * sizeof(char **));
	if (da->append_tab == NULL)
		return (write(2, "Error: malloc failed\n", 21), 1);
	while (i < da->pnum)
	{
		j = 0;
		da->o_append = i;
		da->nb_append = ft_nb_append(temp_args[i]);
		da->append_tab[i] = malloc((ft_nb_redir(temp_args[i], '>') - da->nb_append + 1) * sizeof(char *));
		if (da->append_tab[i] == NULL)
			return (write(2, "Error: malloc failed\n", 21), 1);
		while (j < ft_nb_redir(temp_args[i], '>') - da->nb_append)
		{
			da->append_tab[i][j] = fill_append(temp_args[i], da);
			if (da->append_tab[i][j] == NULL)
				return (1);
			j++;
		}
		da->append_tab[i][j] = NULL;
		i++;
	}
	return (0);
}
