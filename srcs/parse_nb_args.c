/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nb_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:16:36 by abolea            #+#    #+#             */
/*   Updated: 2024/06/03 19:00:35 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_io_args(char **words, int *j, int *res)
{
	if (words[*j - 1][0] == 34 || words[*j - 1][0] == 39)
	{
		while (if_finish_quotes(words[*j - 1]) != 1)
			(*j)++;
	}
	while (words[*j] && (words[*j][0] != '<' && words[*j][0] != '>'))
	{
		(*j)++;
		(*res)++;
	}
}

void	if_args_after(char **words, int *j, int *res)
{
	if ((words[*j - 2][0] == '<' || words[*j - 2][0] == '>') \
	&& (words[*j][0] != '<' && words[*j][0] != '>'))
		if_io_args(words, j, res);
	else if ((words[*j][0] == '<' || words[*j][0] == '>') \
	|| (words[*j - 1][0] == '<' || words[*j - 1][0] == '>'))
		(*j)++;
	else if ((words[*j][0] != '<' && words[*j][0] != '>') \
	&& (words[*j - 1][0] != '<' && words[*j - 1][0] != '>'))
	{
		(*j)++;
		(*res)++;
	}
}

void	if_args_before(char **words, int *j, int *res)
{
	if ((words[*j][0] == '<' || words[*j][0] == '>') \
	|| (words[*j - 1][0] == '<' || words[*j - 1][0] == '>'))
		(*j)++;
	else if ((words[*j][0] != '<' && words[*j][0] != '>') \
	&& (words[*j - 1][0] != '<' && words[*j - 1][0] != '>'))
	{
		if (words[*j][0] == 34 || words[*j][0] == 39)
		{
			(*res)++;
			(*j)++;
		}
		else
		{
			(*j)++;
			(*res)++;
		}
	}
}

int	ft_nb_args(t_data *da, char **words)
{
	int	res;
	int	j;

	res = 0;
	j = pos_args(da, words);
	if (j == -1)
		return (0);
	while (words[j])
	{
		if (j > 2)
			if_args_after(words, &j, &res);
		else
			if_args_before(words, &j, &res);
	}
	return (res);
}

char	*args_after(t_data *da, char **words, char *args)
{
	if ((words[da->i_args - 2][0] == '<' || words[da->i_args - 2][0] == '>') \
	&& (words[da->i_args][0] != '<' && words[da->i_args][0] != '>'))
	{
		if (words[da->i_args - 1][0] == 34 || words[da->i_args - 1][0] == 39)
		{
			while (if_finish_quotes(words[da->i_args - 1]) != 1)
				da->i_args++;
		}
		while (words[da->i_args][0] != '<' && words[da->i_args][0] != '>')
		{
			args = ft_strjoin_ori(args, words[da->i_args]);
			if (!args)
				return (NULL);
			if (da->s_args != 1 && da->if_expand != 1)
				args = cpy_args_without_quotes(args);
			if (!args)
				return (NULL);
			da->i_args++;
			return (args);
		}
	}
	free(args);
	return (NULL);
}
