/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:23:02 by abolea            #+#    #+#             */
/*   Updated: 2024/05/29 15:23:57 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_words_and_temp_args(char **temp_args, char **words)
{
	int	i;
	int	num_w;

	i = -1;
	while (temp_args[++i] != NULL)
		free(temp_args[i]);
	free(temp_args);
	temp_args = NULL;
	num_w = -1;
	while (words[++num_w] != NULL)
		free(words[num_w]);
	free(words);
	words = NULL;
}

void	free_words(char **words)
{
	int	j;

	j = 0;
	while (words[j])
	{
		free (words[j]);
		j++;
	}
	free (words);
	words = NULL;
}

void	free_temp_args(char **temp_args)
{
	int	j;

	j = 0;
	if (temp_args[j])
	{
		while (temp_args[j])
		{
			free (temp_args[j]);
			j++;
		}
		free (temp_args);
		temp_args = NULL;
	}
}
