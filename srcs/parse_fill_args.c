/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:37:45 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/22 14:19:37 by lle-pier         ###   ########.fr       */
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

char	*fill_cmd(char **words)
{
	char	*args;
	int		i;

	i = pos_cmd(words);
	if (i == -1)
		args = NULL;
	else
		args = ft_strdup(words[i]);
	return (args);
}

int	pos_args(char **words)
{
	int	j;

	j = pos_cmd(words) + 1;
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

char	*fill_args(char **words)
{
	char	*args;
	int		j;
	int		num_words;

	num_words = 0;
	while (words[num_words])
		num_words++;
	j = pos_args(words);
	if (j == -1)
		args = NULL;
	else
	{
		args = ft_strdup("");
		while (j < num_words && words[j][0] != '<' && words[j][0] != '>')
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
				args = ft_strjoin_ori(args, words[j]);
				args = ft_strjoin_ori(args, " ");
				j++;
			}
		}
		while (j < num_words)
		{
			if ((words[j - 2][0] == '<' || words[j - 2][0] == '>') && !words[j - 2][1])
			{
				if (words[j - 1][0] == 34)
				{
					while (if_finish_quotes(words[j - 1]) != 1)
						j++;
				}
				while (j < num_words && (words[j][0] != '<' && words[j][0] != '>'))
				{
					args = ft_strjoin_ori(args, words[j]);
					args = ft_strjoin_ori(args, " ");
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
				while (j < num_words && (words[j][0] != '<' && words[j][0] != '>'))
				{
					args = ft_strjoin_ori(args, words[j]);
					args = ft_strjoin_ori(args, " ");
					j++;
				}
			}
			j++;
		}
	}
	if (args != NULL)
		args = cpy_args_without_quotes(args);
	return (args);
}
