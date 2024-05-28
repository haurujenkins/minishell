/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:31:09 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/28 11:17:32 by abolea           ###   ########.fr       */
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

char	*cpy_until_char(char *s, char c, int start)
{
	char	*tmp;
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(s);
	tmp = malloc((len - start + 1) * sizeof(char));
	if (!tmp)
		return (write(2, "Malloc failed\n", 14), NULL);
	while (s[start] != c && start < len)
	{
		tmp[j] = s[start];
		start++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	len_for_args(char *s, int start)
{
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(s);
	while ((s[start] != '<' && s[start] != '>' && s[start] != ' ') && start < len)
	{
		j++;
		start++;
	}
	return (j);
}

char	*cpy_for_args(char *s, int start)
{
	char	*tmp;
	int		j;
	int		len;

	j = 0;
	len = len_for_args(s, start);
	tmp = malloc((len - start + 1) * sizeof(char));
	if (!tmp)
		return (write(2, "Malloc failed\n", 14), NULL);
	while ((s[start] != '<' && s[start] != '>' && s[start] != ' ') && start < len)
	{
		tmp[j] = s[start];
		start++;
		j++;
	}
	tmp[j] = '\0';
	free (s);
	return (tmp);
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
