/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fillout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:53:14 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/03 14:24:03 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*if_quotes_args_out(char *temp_args, t_data *da, char *args)
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

char	*if_not_quotes_args_out(char *temp_args, t_data *da, char *args)
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

char	*recup_args_out(char *temp_args, t_data *da, char *args)
{
	da->io_nb++;
	while (temp_args[da->io_nb] == ' ')
		da->io_nb++;
	if (temp_args[da->io_nb] == 34 || temp_args[da->io_nb] == 39)
	{
		args = if_quotes_args_out(temp_args, da, args);
		if (!args)
			return (NULL);
		return (args);
	}
	else
	{
		args = if_not_quotes_args_out(temp_args, da, args);
		if (!args)
			return (NULL);
		return (args);
	}
}

char	*fill_output(char *temp_args, t_data *da)
{
	char	*args;

	args = NULL;
	while (temp_args[da->io_nb])
	{
		if (temp_args[da->io_nb] == '>' && temp_args[da->io_nb + 2])
			return (recup_args_out(temp_args, da, args));
		else
			da->io_nb++;
	}
	return (NULL);
}

int	fill_outab(t_data *da, char *temp_args, int i)
{
	int	j;

	j = 0;
	da->io_nb = 0;
	da->nb_redir_out = ft_nb_redir(temp_args, '>');
	da->out_tab[i] = malloc((da->nb_redir_out + 1) * sizeof(char *));
	if (da->out_tab[i] == NULL)
		return (1);
	if (da->nb_redir_out == 0)
		da->out_tab[i][j] = NULL;
	else
	{
		while (j < da->nb_redir_out)
		{
			da->out_tab[i][j] = fill_output(temp_args, da);
			if (!da->out_tab[i][j])
				return (1);
			if (da->out_tab[i][j])
				j++;
		}
		da->out_tab[i][j] = NULL;
	}
	return (0);
}
