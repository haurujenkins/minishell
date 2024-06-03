/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:37:45 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/03 14:27:07 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pos_args(t_data *da, char **words)
{
	int	j;

	j = da->pos_cmd + 1;
	if (j == 0)
		return (-1);
	while (words[j])
	{
		if ((words[j - 1][0] != '<' && words[j - 1][0] != '>') \
		&& (words[j][0] != '>' && words[j][0] != '<'))
			return (j);
		j++;
	}
	return (-1);
}

void	if_dollar_ok(t_data *da, char **temp_args, int i)
{
	int	tmp_d;

	da->nb_d = nb_dollars(temp_args[i]);
	tmp_d = da->nb_d;
	temp_args[i] = dollar_negative_in_s_quote(temp_args[i]);
	while (tmp_d > 0)
	{
		temp_args[i] = dollar_after_heredoc(temp_args[i], da);
		tmp_d--;
	}
}

int	new_temp_args(t_data *da, char **temp_args)
{
	int	i;

	i = 0;
	da->if_heredoc = 0;
	while (i < da->pnum)
	{
		if_dollar_ok(da, temp_args, i);
		heredoc_double_quotes(temp_args[i], da);
		if (da->if_heredoc == 0)
		{
			if (if_not_heredoc(da, temp_args, i) == 1)
				return (1);
		}
		if (nb_dollars(temp_args[i]) != 0)
		{
			if (if_nb_dollar(temp_args, i) == 1)
				return (1);
		}
		if (sup_append_and_delim(temp_args, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	*fill_args(t_data *da, char **words, int i)
{
	char	*args;

	args = ft_strdup("");
	if (!args)
		return (NULL);
	while (words[da->i_args])
	{
		if (da->i_args > 2)
		{
			args = if_args_after_ok(da, words, args);
			if (args)
				return (args);
		}
		else
		{
			args = if_args_before_ok(da, words, args, i);
			if (args)
				return (args);
		}
	}
	return (NULL);
}

int	fill_args_tab(t_data *da, char **words, int i)
{
	int	j;

	j = 0;
	da->i_args = pos_args(da, words);
	da->nb_args = ft_nb_args(da, words);
	da->args_tab[i] = malloc((da->nb_args + 1) * sizeof(char *));
	if (!da->args_tab[i])
		return (1);
	if (da->nb_args == 0)
		da->args_tab[i][j] = NULL;
	else
	{
		while (j < da->nb_args)
		{
			da->args_tab[i][j] = fill_args(da, words, i);
			if (!da->args_tab[i][j])
				return (1);
			if (da->args_tab[i][j])
				j++;
		}
		da->args_tab[i][j] = NULL;
	}
	return (0);
}
