/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fill_all_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:32:42 by abolea            #+#    #+#             */
/*   Updated: 2024/06/05 14:48:13 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_all_tab(t_data *da, char **words, char **temp_args, int i)
{
	int	num_w;

	num_w = 0;
	while (words[num_w] != NULL)
		num_w++;
	da->args[i] = malloc((num_w + 1) * sizeof(char *));
	if (da->args[i] == NULL)
		return (1);
	da->args[i][0] = fill_cmd(words, da);
	if (da->args[i][0])
		da->args[i][1] = NULL;
	da->pos_cmd = pos_cmd(words);
	da->io_nb = 0;
	if (fill_args_tab(da, words, i) == 1)
		return (1);
	if (fill_intab(da, temp_args[i], i) == 1)
		return (1);
	if (fill_outab(da, temp_args[i], i) == 1)
		return (1);
	return (0);
}

int	parse_is_ok(t_data *da, char **temp_args, char **words)
{
	int	i;

	i = 0;
	while (i < da->pnum)
	{
		temp_args[i] = sup_tab(temp_args[i]);
		if (!temp_args[i])
			return (1);
		words = init_words(temp_args, i);
		if (!words)
			return (1);
		if (fill_all_tab(da, words, temp_args, i) == 1)
			return (printf("Error: malloc failed\n"), 1);
		free_words(words);
		i++;
	}
	return (0);
}

int	parsing(char *rl, t_data *da)
{
	char	**temp_args;
	char	**words;
	int		i;	

	i = 0;
	temp_args = NULL;
	words = NULL;
	temp_args = init_temp_args(rl, da);
	if (temp_args == NULL)
		return (printf ("Error: malloc failed\n"), 1);
	if (init_malloc(temp_args, da) == 1)
	{
		free_words_and_temp_args(temp_args, words);
		return (1);
	}
	if (parse_is_ok(da, temp_args, words) == 1)
		return (1);
	free_temp_args(temp_args);
	return (0);
}

void	if_rl(char *rl, t_data *da, char **envp)
{
	if (parsing(rl, da) == 1)
	{
		da->exit_status = 134;
		free_struct(da);
	}
	else
	{
		if (!(heredoc_replace(da, 0, 0) == -1))
		{
			if (da->pnum > 0)
			{
				if (main_exec(da, envp) == -1)
					da->exit_status = 134;
			}
		}
	}
	free_pipe(da);
	free_struct(da);
}
