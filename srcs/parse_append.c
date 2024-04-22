/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:28:18 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/22 14:42:24 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_without_append(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '>' && s[i + 1] == '>')
			i++;
		else if (s[i])
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*sup_append(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	len = len_without_append(s);
	tmp = malloc((len + 1) * sizeof(char));
	while (s[i])
	{
		if (s[i] == '>' && s[i + 1] == '>')
		{
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
	free (s);
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
				return (printf("Error: malloc failed\n"), NULL);
			da->o_append++;
			return (args);
		}
		else if (temp_args[da->o_append] \
		== '>' && temp_args[da->o_append + 1] == '>')
		{
			args = ft_strdup("1");
			if (args == NULL)
				return (printf("Error: malloc failed\n"), NULL);
			da->o_append += 2;
			return (args);
		}
		da->o_append++;
	}
	return (NULL);
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

int	fill_append_tab(t_data *da, char **temp_args)
{
	int	i;
	int	j;

	i = 0;
	da->append_tab = malloc(da->pnum * sizeof(char **));
	if (da->append_tab == NULL)
		return (printf("Error: malloc failed\n"), 1);
	while (i < da->pnum)
	{
		j = 0;
		da->o_append = i;
		da->nb_append = ft_nb_append(temp_args[i]);
		da->append_tab[i] = malloc((da->nb_append + 1) * sizeof(char *));
		if (da->append_tab[i] == NULL)
			return (printf("Error: malloc failed\n"), 1);
		if (da->nb_append == 0)
			da->append_tab[i][j] = NULL;
		else
		{
			while (j < ft_nb_redir(temp_args[i], '>') - da->nb_append)
			{
				da->append_tab[i][j] = fill_append(temp_args[i], da);
				if (da->append_tab[i][j] == NULL)
					return (1);
				j++;
			}
			da->append_tab[i][j] = NULL;
		}
		i++;
	}
	return (0);
}
