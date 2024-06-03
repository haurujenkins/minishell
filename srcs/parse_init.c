/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:50:45 by abolea            #+#    #+#             */
/*   Updated: 2024/06/03 14:24:09 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**init_words(char **temp_args, int i)
{
	int		j;
	char	**words;

	temp_args[i] = new_temp(temp_args[i]);
	if (!temp_args[i])
		return (NULL);
	temp_args[i] = negative_in_quotes(temp_args[i]);
	words = ft_split(temp_args[i], ' ');
	if (!words)
		return (NULL);
	j = 0;
	while (words[j])
	{
		words[j] = all_positive(words[j]);
		j++;
	}
	temp_args[i] = all_positive(temp_args[i]);
	return (words);
}

char	**init_temp_args(char *rl, t_data *da)
{
	char	**temp_args;
	int		i;

	i = 0;
	temp_args = NULL;
	da->pnum = nb_pipe(rl);
	rl = negative_in_quotes(rl);
	temp_args = ft_split(rl, '|');
	if (temp_args == NULL)
		return (NULL);
	while (temp_args[i])
	{
		temp_args[i] = all_positive(temp_args[i]);
		i++;
	}
	return (temp_args);
}

int	init_malloc(char **temp_args, t_data *da)
{
	da->args = malloc(da->pnum * sizeof(char **));
	if (da->args == NULL)
		return (printf("Error: malloc failed\n"), 1);
	if (fill_delim_tab(da, temp_args) == 1)
		return (1);
	if (fill_append_tab(da, temp_args) == 1)
		return (1);
	if (new_temp_args(da, temp_args) == 1)
		return (1);
	da->args_tab = malloc((da->pnum + 1) * sizeof(char **));
	if (!da->args_tab)
		return (1);
	da->in_tab = malloc((da->pnum + 1) * sizeof(char **));
	if (!da->in_tab)
		return (1);
	da->out_tab = malloc((da->pnum + 1) * sizeof(char **));
	if (!da->out_tab)
		return (1);
	return (0);
}
