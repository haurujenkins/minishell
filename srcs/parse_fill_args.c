/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:37:45 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/26 17:52:57 by lle-pier         ###   ########.fr       */
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
			printf("Error: malloc failed\n");
			return (NULL);
		}
		temp_args[i] = sup_delim(temp_args[i]);
		if (temp_args[i] == NULL)
		{
			printf("Error: malloc failed\n");
			return (NULL);
		}
		temp_args[i] = sup_append(temp_args[i]);
		if (temp_args[i] == NULL)
		{
			printf("Error: malloc failed\n");
			return (NULL);
		}
		i++;
	}
	return (temp_args);
}

int	ft_nb_args(t_data *da, char **words)
{
	int		j;
	int		num_w;
	int		res;

	num_w = 0;
	res = 0;
	while (words[num_w])
		num_w++;
	j = da->pos_cmd + 1;
	if (j == 0)
		return (0);
	else
	{
		while (words[j] != NULL && (words[j][0] != '<' && words[j][0] != '>'))
		{
			if (words[j][0] == 34)
			{
				res++;
				j++;
			}
			else if ((words[j][0] != '>' && words[j][0] != '<'))
			{
				res++;
				j++;
			}
			else
				j++;
		}
		while (words[j])
		{
			if ((words[j - 2][0] == '<' || words[j - 2][0] == '>') && !words[j - 2][1])
			{
				if (words[j - 1][0] == 34)
				{
					while (if_finish_quotes(words[j - 1]) != 1)
						j++;
				}
				while (j < num_w && (words[j][0] != '<' && words[j][0] != '>'))
				{
					res++;
					j++;
				}
			}
			else if ((words[j - 1][0] == '<' || words[j - 1][0] == '>') && words[j - 1][1])
			{
				if (words[j - 1][1] == 34)
				{
					while (if_finish_quotes(words[j - 1]) != 1)
						j++;
				}
				while (j < num_w && (words[j][0] != '<' && words[j][0] != '>'))
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
	int		num_w;

	num_w = 0;
	while (words[num_w])
		num_w++;
	if (da->nb_args == 0)
		return (NULL);
	else
	{
		args = ft_strdup("");
		while (words[da->i_args] != NULL && words[da->i_args][0] != '<' && words[da->i_args][0] != '>')
		{
			if (words[da->i_args][0] == 34)
			{
				args = ft_strjoin_ori(args, words[da->i_args]);
				da->i_args++;
				args = cpy_args_without_quotes(args);
				return (args);
			}
			else if ((words[da->i_args][0] != '>' && words[da->i_args][0] != '<'))
			{
				args = ft_strjoin_ori(args, words[da->i_args]);
				da->i_args++;
				args = cpy_args_without_quotes(args);
				return (args);
			}
			else
				da->i_args++;
		}
		while (words[da->i_args])
		{
			if ((words[da->i_args - 2][0] == '<' || words[da->i_args - 2][0] == '>') && !words[da->i_args - 2][1])
			{
				if (words[da->i_args - 1][0] == 34)
				{
					while (if_finish_quotes(words[da->i_args - 1]) != 1)
						da->i_args++;
				}
				while (da->i_args < num_w && (words[da->i_args][0] != '<' && words[da->i_args][0] != '>'))
				{
					args = ft_strjoin_ori(args, words[da->i_args]);
					da->i_args++;
					args = cpy_args_without_quotes(args);
					return (args);
				}
			}
			else if ((words[da->i_args - 1][0] == '<' || words[da->i_args - 1][0] == '>') && words[da->i_args - 1][1])
			{
				if (words[da->i_args - 1][1] == 34)
				{
					while (if_finish_quotes(words[da->i_args - 1]) != 1)
						da->i_args++;
				}
				while (da->i_args < num_w && (words[da->i_args][0] != '<' && words[da->i_args][0] != '>'))
				{
					args = ft_strjoin_ori(args, words[da->i_args]);
					da->i_args++;
					args = cpy_args_without_quotes(args);
					return (args);
				}
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

	i = -1;
	da->nb_args = 0;
	da->i_args = 0;
	da->args_tab = malloc(da->pnum * sizeof(char **));
	while (++i < da->pnum)
	{
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
				// printf("j = %d\n", j);
				// printf("n = %d\n", da->nb_args);
			}
			da->args_tab[i][j] = NULL;
		}
	}
}
