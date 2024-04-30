/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fillin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:55:13 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/30 16:54:01 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_input(char *temp_args, t_data *da)
{
	char	*args;

	args = NULL;
	while (temp_args[da->io_nb])
	{
		if (temp_args[da->io_nb] == '<')
		{
			da->io_nb++;
			if (temp_args[da->io_nb] == ' ')
			{
				da->io_nb++;
				while (temp_args[da->io_nb] == ' ')
					da->io_nb++;
				if (temp_args[da->io_nb] == 34)
				{
					da->io_nb++;
					args = cpy_until_char(temp_args, 34, da->io_nb);
					while (temp_args[da->io_nb] != 34 && temp_args[da->io_nb])
						da->io_nb++;
					return (args);
				}
				else
				{
					args = cpy_until_char(temp_args, ' ', da->io_nb);
					return (args);
				}
			}
			else if (temp_args[da->io_nb] == 34)
			{
				da->io_nb++;
				args = cpy_until_char(temp_args, 34, da->io_nb);
				while (temp_args[da->io_nb] != 34 && temp_args[da->io_nb])
					da->io_nb++;
				return (args);
			}
			else if (ft_isprint(temp_args[da->io_nb]) == 1)
			{
				args = cpy_until_char(temp_args, ' ', da->io_nb);
				return (args);
			}
		}
		da->io_nb++;
	}
	return (NULL);
}

void	fill_intab(t_data *da, char *temp_args)
{
	int	i;
	int	j;

	i = 0;
	da->nb_redir_in = 0;
	da->in_tab = malloc(da->pnum * sizeof(char **));
	j = 0;
	da->io_nb = 0;
	da->nb_redir_in = ft_nb_redir(temp_args, '<');
	da->in_tab[i] = malloc((da->nb_redir_in + 1) * sizeof(char *));
	if (da->nb_redir_in == 0)
		da->in_tab[i][j] = NULL;
	else
	{
		while (j < da->nb_redir_in)
		{
			da->in_tab[i][j] = fill_input(temp_args, da);
			if (da->in_tab[i][j])
				j++;
		}
		da->in_tab[i][j] = NULL;
	}
}
