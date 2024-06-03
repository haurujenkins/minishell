/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fillin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:55:13 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/03 14:23:43 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*if_quotes_args_in(char *temp_args, t_data *da, char *args)
{
	args = cpy_until_char(temp_args, ' ', da->io_nb);
	if (!args)
		return (NULL);
	while ((temp_args[da->io_nb] != 34 \
	&& temp_args[da->io_nb] != 39) && temp_args[da->io_nb])
		da->io_nb++;
	if (if_quotes(args, 0) == 1)
		da->q_heredoc = -1;
	args = cpy_args_without_quotes(args);
	if (!args)
		return (NULL);
	return (args);
}

char	*if_not_quotes_args_in(char *temp_args, t_data *da, char *args)
{
	args = cpy_until_char(temp_args, ' ', da->io_nb);
	if (!args)
		return (NULL);
	while (temp_args[da->io_nb] != ' ' && temp_args[da->io_nb])
		da->io_nb++;
	if (if_quotes(args, 0) == 1)
		da->q_heredoc = -1;
	args = cpy_args_without_quotes(args);
	if (!args)
		return (NULL);
	return (args);
}

char	*recup_args_in(char *temp_args, t_data *da, char *args)
{
	da->io_nb++;
	while (temp_args[da->io_nb] == ' ')
		da->io_nb++;
	if (temp_args[da->io_nb] == 34 || temp_args[da->io_nb] == 39)
	{
		args = if_quotes_args_in(temp_args, da, args);
		if (!args)
			return (NULL);
		return (args);
	}
	else
	{
		args = if_not_quotes_args_in(temp_args, da, args);
		if (!args)
			return (NULL);
		return (args);
	}
}

char	*fill_input(char *temp_args, t_data *da)
{
	char	*args;

	args = NULL;
	while (temp_args[da->io_nb])
	{
		if (temp_args[da->io_nb] == '<' && temp_args[da->io_nb + 2])
		{
			args = recup_args_in(temp_args, da, args);
			if (!args)
				return (NULL);
			else
				return (args);
		}
		else
			da->io_nb++;
	}
	return (NULL);
}

int	fill_intab(t_data *da, char *temp_args, int i)
{
	int	j;

	j = 0;
	da->nb_redir_in = ft_nb_redir(temp_args, '<');
	da->in_tab[i] = malloc((da->nb_redir_in + 1) * sizeof(char *));
	if (da->in_tab[i] == NULL)
		return (1);
	if (da->nb_redir_in == 0)
		da->in_tab[i][j] = NULL;
	else
	{
		while (j < da->nb_redir_in)
		{
			da->in_tab[i][j] = fill_input(temp_args, da);
			if (!da->in_tab[i][j])
				return (1);
			if (da->in_tab[i][j])
				j++;
		}
		da->in_tab[i][j] = NULL;
	}
	return (0);
}
