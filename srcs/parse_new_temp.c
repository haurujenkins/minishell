/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_temp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:34:31 by abolea            #+#    #+#             */
/*   Updated: 2024/05/30 15:55:33 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nb_tab(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == '\t')
		{
			i++;
			j++;
		}
		i++;
	}
	return (j);
}

char	*sup_tab(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	len = ft_strlen(s) - nb_tab(s) + 1;
	res = malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		while (s[i] == '\t')
			i++;
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	free (s);
	return (res);
}

char	*new_temp(char *s)
{
	s = temp_with_space(s);
	if (!s)
		return (NULL);
	s = sup_double_space(s);
	if (!s)
		return (NULL);
	return (s);
}

char	*else_args_after(t_data *da, char **words, char *args)
{
	if ((words[da->i_args][0] == '<' || words[da->i_args][0] == '>') \
	|| (words[da->i_args - 1][0] == '<' || words[da->i_args - 1][0] == '>'))
		da->i_args++;
	else if ((words[da->i_args][0] != '<' && words[da->i_args][0] != '>') \
	&& (words[da->i_args - 1][0] != '<' && words[da->i_args - 1][0] != '>'))
	{
		args = ft_strjoin_ori(args, words[da->i_args]);
		if (!args)
			return (NULL);
		if (da->s_args != 1)
			args = cpy_args_without_quotes(args);
		if (!args)
			return (NULL);
		da->i_args++;
		return (args);
	}
	return (NULL);
}
