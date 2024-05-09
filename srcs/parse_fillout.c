/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fillout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:53:14 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/09 14:32:16 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_output(char *temp_args, t_data *da)
{
	char	*args;

	while (temp_args[da->io_nb])
	{
		if (temp_args[da->io_nb] == '>' && temp_args[da->io_nb + 2])
		{
			da->io_nb++;
			while (temp_args[da->io_nb] == ' ')
				da->io_nb++;
			if (temp_args[da->io_nb] == 34 || temp_args[da->io_nb] == 39)
			{
				da->io_nb++;
				args = cpy_until_char(temp_args, 34, da->io_nb);
				while ((temp_args[da->io_nb] != 34 && temp_args[da->io_nb] != 39) && temp_args[da->io_nb])
					da->io_nb++;
				return (args);
			}
			else
			{
				args = cpy_until_char(temp_args, ' ', da->io_nb);
				while (temp_args[da->io_nb] != ' ' && temp_args[da->io_nb])
					da->io_nb++;
				return (args);
			}
		}
		else
			da->io_nb++;
	}
	return (NULL);
}

void	fill_outab(t_data *da, char *temp_args, int i)
{
	int	j;

	j = 0;
	da->io_nb = 0;
	da->nb_redir_out = ft_nb_redir(temp_args, '>');
	da->out_tab[i] = malloc((da->nb_redir_out + 1) * sizeof(char *));
	if (da->nb_redir_out == 0)
		da->out_tab[i][j] = NULL;
	else
	{
		while (j < da->nb_redir_out)
		{
			da->out_tab[i][j] = fill_output(temp_args, da);
			if (da->out_tab[i][j])
				j++;
		}
		da->out_tab[i][j] = NULL;
	}
}
