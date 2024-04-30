/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:37:45 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/30 17:11:36 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pos_cmd(char **words)
{
	int	j;

	j = 1;
	if ((words[0][0] != '<' && words[0][0] != '>'))
		return (0);
	while (words[j])
	{
		if ((words[j - 1][0] != '<' && words[j - 1][0] != '>') && \
		(words[j][0] != '>' && words[j][0] != '<'))
			return (j);
		j++;
	}
	return (-1);
}

int	len_cmd(char *words)
{
	int		i;

	i = 0;
	while ((words[i] != '>' && words[i] != '<') && words[i])
		i++;
	return (i);
}

char	*get_cmd(char *words)
{
	char	*args;
	int		i;
	int		len;

	i = 0;
	len = len_cmd(words);
	args = malloc((len + 1) * sizeof(char));
	if (!args)
		return (NULL);
	while ((words[i] != '>' && words[i] != '<') && words[i])
	{
		args[i] = words[i];
		i++;
	}
	args[i] = '\0';
	return (args);
}

char	*fill_cmd(char **words)
{
	char	*args;
	int		i;

	i = pos_cmd(words);
	if (i == -1)
		args = NULL;
	else
		args = get_cmd(words[i]);
	return (args);
}

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
		else if (((words[j - 1][0] == '<' \
		&& words[j - 1][0] == '>') || words[j - 1][1]) && \
		(words[j][0] != '>' && words[j][0] != '<'))
			return (j);
		j++;
	}
	return (-1);
}

char	**new_temp_args(t_data *da, char **temp_args)
{
	int	i;

	i = 0;
	while (i < da->pnum)
	{
		temp_args[i] = temp_without_dollar(da, temp_args[i]);
		if (temp_args[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 21);
			return (NULL);
		}
		temp_args[i] = sup_delim(temp_args[i]);
		if (temp_args[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 21);
			return (NULL);
		}
		temp_args[i] = sup_append(temp_args[i]);
		if (temp_args[i] == NULL)
		{
			write(2, "Error: malloc failed\n", 21);
			return (NULL);
		}
		i++;
	}
	return (temp_args);
}

int	ft_nb_args(t_data *da, char **words)
{
	int		res;
	int		j;
	int		num_words;

	num_words = 0;
	res = 0;
	while (words[num_words])
		num_words++;
	j = pos_args(da, words);
	if (j == -1)
		return (0);
	else
	{
		while (words[j] && words[j][0] != '<' && words[j][0] != '>')
		{
			if ((words[j - 1][0] == '>' || words[j - 1][0] == '<') && (words[j][0] == 34 || words[j - 1][1] == 34))
			{
				while (if_finish_quotes(words[j - 1]) != 1)
					j++;
			}
			else if (words[j][0] == '<' && words[j][0] == '>')
			{
				if (words[j - 1][0] == 34 || words[j - 1][1] == 34)
				{
					while (if_finish_quotes(words[j - 1]) != 1)
						j++;
				}
				else
					j++;
			}
			else
			{
				res++;
				j++;
			}
		}
		while (words[j])
		{
			if ((words[j - 2][0] == '<' || words[j - 2][0] == '>') && !words[j - 2][1])
			{
				if (words[j - 1][0] == 34)
				{
					while (if_finish_quotes(words[j  - 1]) != 1)
						j ++;
				}
				while (words[j] && (words[j][0] != '<' && words[j][0] != '>'))
				{
					res++;
					j++;
				}
			}
			j++;
		}
	}
	return (res);
}

char	*fill_args(t_data *da, char **words)
{
	char	*args;

	if (da->nb_args == 0)
		return (NULL);
	else
	{
		args = ft_strdup("");
		while (words[da->i_args] && words[da->i_args][0] != '<' && words[da->i_args][0] != '>')
		{
			if ((words[da->i_args - 1][0] == '>' || words[da->i_args - 1][0] == '<') && ((words[da->i_args][0] == 34 || words[da->i_args - 1][1] == 34) || (words[da->i_args][0] == 39 || words[da->i_args - 1][1] == 39)))
			{
				while (if_finish_quotes(words[da->i_args - 1]) != 1)
					da->i_args++;
			}
			else if (words[da->i_args][0] == '<' && words[da->i_args][0] == '>')
			{
				if ((words[da->i_args - 1][0] == 34 || words[da->i_args - 1][1] == 34) || (words[da->i_args - 1][0] == 39 || words[da->i_args - 1][1] == 39))
				{
					while (if_finish_quotes(words[da->i_args - 1]) != 1)
						da->i_args++;
				}
				else
					da->i_args++;
			}
			else
			{
				args = ft_strjoin_ori(args, words[da->i_args]);
				args = cpy_args_without_quotes(args);
				da->i_args++;
				return (args);
			}
		}
		while (words[da->i_args])
		{
			if ((words[da->i_args - 2][0] == '<' || words[da->i_args - 2][0] == '>') && !words[da->i_args - 2][1])
			{
				if (words[da->i_args - 1][0] == 34 || words[da->i_args - 1][0] == 39)
				{
					while (if_finish_quotes(words[da->i_args  - 1]) != 1)
						da->i_args ++;
				}
				while (words[da->i_args] && (words[da->i_args ][0] != '<' && words[da->i_args ][0] != '>'))
				{
					args = ft_strjoin_ori(args, words[da->i_args]);
					args = cpy_args_without_quotes(args);
					da->i_args ++;
				}
				if (args)
					return (args);
			}
			da->i_args++;
		}
	}
	return (NULL);
}

void	fill_args_tab(t_data *da, char **words)
{
	int	i;
	int	j;

	i = 0;
	da->nb_args = 0;
	da->i_args = 0;
	da->args_tab = malloc(da->pnum * sizeof(char **));
	j = 0;
	da->i_args = pos_args(da, words);
	da->nb_args = ft_nb_args(da, words);
	da->args_tab[i] = malloc((da->nb_args + 1) * sizeof(char *));
	if (da->nb_args == 0)
		da->args_tab[i][j] = NULL;
	else
	{
		while (j < da->nb_args)
		{
			da->args_tab[i][j] = fill_args(da, words);
			if (da->args_tab[i][j])
				j++;
		}
		da->args_tab[i][j] = NULL;
	}
}
