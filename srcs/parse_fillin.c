/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fillin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:55:13 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/14 15:19:46 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*fill_input(char *temp_args, t_data *da)
{
	char	*args;

	while (temp_args[da->io_nb])
	{
		if (temp_args[da->io_nb] == '<' && temp_args[da->io_nb + 2])
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

void	fill_intab(t_data *da, char *temp_args, int i)
{
	int	j;

	j = 0;
	da->nb_redir_in = ft_nb_redir(temp_args, '<');
	da->in_tab[i] = malloc((da->nb_redir_in + 1) * sizeof(char *));
	// if (da->in_tab[i] == NULL)
	// 	return (write(2, "Error: malloc failed\n", 21), 1);
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
