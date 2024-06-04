/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:03:54 by abolea            #+#    #+#             */
/*   Updated: 2024/06/03 17:18:05 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pos_cmd(char **words)
{
	int	j;

	j = 1;
	if (!words[0])
		return (-1);
	if (words[0] && (words[0][0] != '<' && words[0][0] != '>'))
		return (0);
	while (words[j])
	{
		if (j > 1)
		{
			if ((words[j - 1][0] != '<' && words[j - 1][0] != '>') && \
			(words[j][0] != '>' && words[j][0] != '<'))
				return (j);
		}
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

char	*fill_cmd(char **words, t_data *da)
{
	char	*args;
	int		i;

	i = pos_cmd(words);
	if (i == -1)
		args = NULL;
	else
	{
		args = get_cmd(words[i]);
		if (!args)
			return (NULL);
	}
	if (args && (int)ft_strlen(args) > 2)
	{
		if (((args[0] != '"' && args[1] != '"' && args[2] != '\0') || \
		(args[0] != '\'' && args[1] != '\'' && args[2] != '\0')) \
		&& da->if_expand != 1)
		{
			args = cpy_args_without_quotes(args);
			if (!args)
				return (NULL);
		}
	}
	return (args);
}
