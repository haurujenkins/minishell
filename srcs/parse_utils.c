/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:31:09 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/30 16:59:30 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '\0')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_strlen_char(char *s, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[len + i])
	{
		if (s[len + i] == c)
			break ;
		else
			len++;
	}
	return (len);
}

int	if_finish_quotes(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	if ((s[i - 1] == 34 || s[i - 1] == 39) && i > 0)
		return (1);
	return (0);
}

void	set_parse(t_data *da)
{
	da->parse_error = 0;
	da->i_args = 0;
	da->s_args = 0;
	da->delim_tab = NULL;
	da->append_tab = NULL;
	da->nb_redir_in = 0;
	da->nb_redir_out = 0;
	da->io_nb = 0;
	da->i_in_quotes = 0;
	da->o_in_quotes = 0;
	da->nb_delim = 0;
	da->in_delim = 0;
	da->o_append = 0;
	da->nb_append = 0;
	da->args_tab = NULL;
	da->nb_args = 0;
	da->i_args = 0;
	da->pos_cmd = 0;
	da->words = NULL;
	da->nb_d = 0;
	da->q_heredoc = 0;
}

void	free_all(char *new_args, char *temp_args, char *before_args)
{
	free(before_args);
	free(temp_args);
	free(new_args);
}
