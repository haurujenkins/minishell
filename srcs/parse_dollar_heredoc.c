/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:10:25 by abolea            #+#    #+#             */
/*   Updated: 2024/06/07 12:50:41 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dollar_after_heredoc(char *s, t_data *da)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	while (i > 1)
	{
		if (s[i] == '$')
		{
			j = i;
			while (j > 1 && !(s[j - 1] == '<' && s[j - 2] == '<'))
				j--;
			if (s[j - 1] == '<' && s[j - 2] == '<')
			{
				da->if_heredoc = 1;
				s[i] *= -1;
				break ;
			}
		}
		i--;
	}
	return (s);
}

void	heredoc_double_quotes(char *s, t_data *da)
{
	int	i;

	i = 1;
	da->q_heredoc = 1;
	while (s[i])
	{
		if (s[i] < 0)
		{
			if (s[i - 1] == 34 || s[i - 1] == 39)
				da->q_heredoc = -1;
		}
		i++;
	}
}

int	if_not_heredoc(t_data *da, char **temp_args, int i)
{
	while (da->nb_d > 0)
	{
		temp_args[i] = sup_s_quotes_before_dollar(temp_args[i]);
		if (!temp_args)
			return (1);
		temp_args[i] = temp_without_dollar(da, temp_args[i]);
		if (!temp_args)
			return (1);
		da->nb_d--;
	}
	return (0);
}

char	*cpy_in_res_without_dollar_quotes(char *res, char *s, int i, int j)
{
	while (s[i])
	{
		if (i > 1 && (int)ft_strlen(s) > i)
		{
			if (s[i - 1] > 0 && s[i] < 0 && (s[i + 1] == 34 || s[i + 1] == 39))
				i++;
			else
			{
				res[j] = s[i];
				i++;
				j++;
			}
		}
		else
		{
			res[j] = s[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	return (res);
}

char	*sup_dollar_before_quotes(char *s)
{
	char	*res;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = len_without_dollar_before_quotes(s);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res = cpy_in_res_without_dollar_quotes(res, s, i, j);
	free (s);
	return (res);
}
